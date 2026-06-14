#ifdef SERVO_HPP
#define SERVO_HPP

struct ServoConfig
{
    int pin;
    int minPulse;
    int maxPulse;
    int minAngle;
    int maxAngle;
};

class Servo
{
public:
    explicit Servo(const ServoConfig& config); //Construtor. O & faz o compilador referenciar config e não copiar seus valores

    void moveToAngle(double angle);
    void moveByDegrees(double angle);
    void moveByPercent(double percent);

    void moveToCenter();

    void sleep();
    void wake();

    double getCurrentAngle(const);

private:
    void updateServo();
    int calculatePulseWidth(double angle) const; //Para usar o PWM

private:
    ServoConfig conf_;

    double currentAngle_;
    int lastPulseWidth_;
    bool sleeping_;
};

#endif