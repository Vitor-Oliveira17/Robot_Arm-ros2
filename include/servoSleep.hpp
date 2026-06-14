#ifndef SERVO_HPP
#define SERVO_HPP

#include <vector>
#include <cstdint>

class Servo;

class ServoSleep
{
public:
    explicit ServoSleep(uint64_t timeout_ms);

    void addServos(const std::vector<Servo*>& servos);

    void reset();

    void update();

private:
    uint64_t timeout_ms_;
    uint64_t last_activity_ms_;

    bool sleeping_;

    std::vector<Servo*> servos_;
};
#endif