#include <ESP32Servo.h>
// https://lastminuteengineers.com/esp32-servo-motor-tutorial/


Servo myservo;

int pos = 0;
int repeats = 10;
int go = 0;
int goes = 0;
int maxMS = 240000;
int minMS = 60000;

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
  while (goes <= repeats) {
    while (go <= 10) {
      myservo.write(0);
      delay(500);
      myservo.write(180);
      delay(500);
      myservo.write(90);
      delay(500);
      myservo.write(180);
      delay(500);
      myservo.write(90);
      delay(500);
      myservo.write(0);
      delay(500);
      myservo.write(90);
      delay(500);
      myservo.write(0);
      delay(500);
      go += 1;
    }
    while (go <= 30) {
      myservo.write(0);
      delay(500);
      myservo.write(180);
      delay(500);
      go += 1;
    }
    delay(random(maxMS, minMS));
    goes += 1;
  }
}