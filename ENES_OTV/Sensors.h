#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class HallEffect {
private:
  int outputPin;
  bool activeLow;

public:
  HallEffect(int pin, bool activeLow = true)
    : outputPin(pin), activeLow(activeLow) {}

  void begin() {
    pinMode(outputPin, INPUT);
  }

  bool detected() {
    int state = digitalRead(outputPin);
    return activeLow ? (state == LOW) : (state == HIGH);
  }

  int readRaw() {
    return digitalRead(outputPin);
  }
};

class Ultrasonic {
private:
  int trigPin;
  int echoPin;

public:
  Ultrasonic(int trig, int echo)
    : trigPin(trig), echoPin(echo) {}

  void begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
  }

  float getDistanceCm() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH, 30000UL);
    if (duration == 0) {
      return -1.0f;
    }
    return duration * 0.0343f / 2.0f;
  }

  float getDistanceIn() {
    float cm = getDistanceCm();
    if (cm < 0) {
      return -1.0f;
    }
    return cm / 2.54f;
  }
};

class LimitSwitch {
private:
  int switchPin;
  bool activeLow;

public:
  LimitSwitch(int pin, bool activeLow = true)
    : switchPin(pin), activeLow(activeLow) {}

  void begin() {
    pinMode(switchPin, INPUT);
  }

  bool pressed() {
    int state = digitalRead(switchPin);
    return activeLow ? (state == LOW) : (state == HIGH);
  }

  int readRaw() {
    return digitalRead(switchPin);
  }
};

// Added dedicated DutyCycle class to fix undefined dutySensor errors
class DutyCycle {
private:
  int signalPin;

public:
  DutyCycle(int pin) : signalPin(pin) {}

  void begin() {
    pinMode(signalPin, INPUT);
  }

  float getDutyCycle() {
    unsigned long highTime = pulseIn(signalPin, HIGH, 30000UL);
    unsigned long lowTime = pulseIn(signalPin, LOW, 30000UL);   
    if (highTime == 0 || lowTime == 0) {
        return -1.0f;
    }       
    unsigned long totalCycle = highTime + lowTime;
    return ((float)highTime / totalCycle) * 100.0f; 
  }
};

#endif