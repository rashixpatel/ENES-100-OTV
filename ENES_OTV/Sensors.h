
#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

// ========================================
// Hall Effect Sensor
// ========================================

class HallEffect {
private:
  int outputPin;
  bool activeLow;

public:
  // activeLow = true if the sensor output goes LOW
  // when a magnet is detected
  HallEffect(int pin, bool activeLow = true)
    : outputPin(pin), activeLow(activeLow) {}

  void begin() {
    pinMode(outputPin, INPUT);
  }

  // Returns true when a magnet is detected
  bool detected() {
    int state = digitalRead(outputPin);

    return activeLow ? (state == LOW) : (state == HIGH);
  }

  // Returns the raw digital signal
  int readRaw() {
    return digitalRead(outputPin);
  }
};


// ========================================
// Ultrasonic Distance Sensor
// HC-SR04-style trigger/echo sensor
// ========================================

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

  // Returns distance in centimeters.
  // Returns -1 if no echo is received.
  float getDistanceCm() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Timeout after 30 ms (~5 m maximum range)
    unsigned long duration = pulseIn(echoPin, HIGH, 30000UL);

    if (duration == 0) {
      return -1.0f;
    }

    // Speed of sound: approximately 0.0343 cm/us
    return duration * 0.0343f / 2.0f;
  }

  // Returns distance in inches.
  // Returns -1 if no echo is received.
  float getDistanceIn() {
    float cm = getDistanceCm();

    if (cm < 0) {
      return -1.0f;
    }

    return cm / 2.54f;
  }
};


// ========================================
// Limit Switch
// ========================================

class LimitSwitch {
private:
  int switchPin;
  bool activeLow;

public:
  // activeLow = true when using INPUT_PULLUP
  LimitSwitch(int pin, bool activeLow = true)
    : switchPin(pin), activeLow(activeLow) {}

  void begin() {
    pinMode(
      switchPin,
      activeLow ? INPUT_PULLUP : INPUT
    );
  }

  // Returns true when the switch is pressed
  bool pressed() {
    int state = digitalRead(switchPin);

    return activeLow ? (state == LOW) : (state == HIGH);
  }

  // Returns the raw digital signal
  int readRaw() {
    return digitalRead(switchPin);
  }

public:
  DutyCycle(int pin)
    : signalPin(pin) {}

  void begin() {
    pinMode(signalPin, INPUT); // Fixed colon to comma
  }

  float getDutyCycle() {
    // measure high/low pulse time
    unsigned long highTime = pulseIn(signalPin, HIGH, 30000UL);
    unsigned long lowTime = pulseIn(signalPin, LOW, 30000UL);   
    if (highTime == 0 || lowTime == 0) {
        return -1.0;
    }       
    unsigned long totalCycle = highTime + lowTime;
    return ((float)highTime / totalCycle) * 100.0f; 
  }
};

#endif
