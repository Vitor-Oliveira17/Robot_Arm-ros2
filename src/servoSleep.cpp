#include "include/servoSleep.hpp"
#include "include/servo.hpp"

ServoSleep::ServoSleep(uint64_t timeout_ms)
  : timeout_ms_(timeout_ms),
    sleeping_(false),
    last_activity_ms_(millis())
{
}

void ServoSleep::addServos(
  const std::vector<Servo*>& servos)
{
  //Appends a list o servos
  for (auto* servo : servos){
  servos_.push_back(servo);
  }
}

void ServoSleep::reset()
{
  last_activity_ms_ = millis();

  if (sleeping_)
  {
      for (auto* servo : servos_)
      {
          servo->wake();
      }

      sleeping_ = false;
  }
}

void ServoSleep::update()
{
  if (sleeping_)
      return;

  if ((millis() - last_activity_ms_) >= timeout_ms_)
  {
      for (auto* servo : servos_)
      {
          servo->sleep();
      }

      sleeping_ = true;
  }
}