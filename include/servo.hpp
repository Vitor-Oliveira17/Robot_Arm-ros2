#ifdef SERVO_HPP
#define SERVO_HPP

#include <functional> //Implementa os tipos function<tipo> (ponteiros pra funções genéricas do tipo especificado)

struct ServoConfig
{
    int pin;
    int min;
    int max;
    int minAngle;
    int maxAngle;
};

class Servo
{
    public:
        explicit Servo(const ServoConfig& config); //Construtor. O & 

}