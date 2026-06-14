#include <pigpio.h>
#include <cmath>
#include "include/servo.hpp"

//Declarando o contructor
Servo::Servo(const Servoconfig& config)
    //Valores de inicialização
    conf_ = config;
    currentAngle_ = 0,
    lastPulseWidth_ = 0,
    sleeping_ = false;

    //Corpo do constructor
    {
        gpioSetMode(conf_.pin, PI_OUTPUT);
    }

//Declaração de funções
Servo::moveToAngle(double angle)
{
    if (angle < conf_.minAngle)
    {
        currentAngle_ = conf_.minAngle;
    }

    else if (angle < conf_.maxAngle)
    {
        currentAngle_ = conf_.maxAngle;
    }

    else
    {
        currentAngle_ = angle;
    }

    updateServo(); //Repasse o movimento pro servo
}

void Servo::moveByDegrees(double angle)
{
    moveToAngle(currentAngle_ + angle);
}

void Servo::moveByPercent(double percent) //moveByPercent(50) deixa o servo 50% aberto
{   
    double delta = ((conf_.maxAngle - conf_.minAngle)/100.0) * percent;
    moveToAngle(currentAngle_ + delta);
}

void Servo::moveToCenter()
{
    double center = (conf_.maxAngle + conf_.minAngle)/2.0;
    moveToAngle(center);
}

void Servo::sleep() //Sleep Assíncrono
{
    gpioWrite(conf_.pin, 0);
    sleeping_ = true;
}

void Servo::wake()
{
    if (sleeping_)
    {
        updateServo();
        sleeping_ = false;
    }
}

double Servo::getCurrentAngle() const //const garante que a função não altere atributos da classe
{
    return currentAngle_;
}

void Servo::updateServo() //Atualiza a posição do servo
{

    int PulseWidth = calculatePulseWidth(currentAngle_);
    lastPulseWidth_ = PulseWidth;

    gpioWrite(conf_.pin, PulseWidth);
}

void Servo::calculatePulseWidth(double angle) const //const garante que a função não altere atributos da classe
{
        double fractionAngle = (angle - conf_.minAngle) /
                               (conf_.maxAngle - conf_.minAngle);

        double deltaPulse = conf_.maxPulse - conf_.minPulse;

        double pulse = conf_.minPulse + (fraction_angle * deltaPulse);

    return static_cast<int>(std::floor(pulse));
}
