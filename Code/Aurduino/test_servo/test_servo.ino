#include <ESP32Servo.h>
// https://lastminuteengineers.com/esp32-servo-motor-tutorial/


Servo myservo;

int pos = 0;
int go = 0;

int servoPin = 13;

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 500, 2400);
}

void loop() {
  while (go <= 5) {
    myservo.write(0);
    delay(500);
    myservo.write(180);
    delay(500);
    go += 1;
  }
}