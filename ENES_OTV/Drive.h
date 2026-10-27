
#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>

// ========================================
// Motor class
// ========================================

class Motor {
private:
  int enPin;
  int in1Pin;
  int in2Pin;
  bool reversed;

public:
  // en = enable/PWM pin
  // in1, in2 = direction pins
  // reverse = true if the motor's direction needs flipping
  Motor(int en, int in1, int in2, bool reverse = false)
    : enPin(en), in1Pin(in1), in2Pin(in2), reversed(reverse) {}

  void begin() {
    pinMode(enPin, OUTPUT);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);

    motorSetPow(0);
  }

  // Power range: -1.0 to 1.0
  void motorSetPow(float pow) {
    pow = constrain(pow, -1.0f, 1.0f);

    if (reversed) {
      pow = -pow;
    }

    int pwm = (int)(abs(pow) * 255.0f);

    if (pow > 0) {
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
    } else if (pow < 0) {
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
    } else {
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
    }

    analogWrite(enPin, pwm);
  }
};


// ========================================
// MecanumDrive class
// ========================================

class MecanumDrive {
private:
  Motor& frontLeft;
  Motor& frontRight;
  Motor& backLeft;
  Motor& backRight;

public:
  MecanumDrive(
    Motor& fl,
    Motor& fr,
    Motor& bl,
    Motor& br
  ) : frontLeft(fl),
      frontRight(fr),
      backLeft(bl),
      backRight(br) {}

  void begin() {
    frontLeft.begin();
    frontRight.begin();
    backLeft.begin();
    backRight.begin();
  }

  // x: strafe (right positive)
  // y: forward (positive)
  // rx: counterclockwise rotation positive
  // All inputs range from -1.0 to 1.0
  void move(float x, float y, float rx) {
    x  = constrain(x, -1.0f, 1.0f);
    y  = constrain(y, -1.0f, 1.0f);
    rx = constrain(rx, -1.0f, 1.0f);

    // Calculate each wheel's power
    float fl = y + x + rx;
    float fr = y - x - rx;
    float bl = y - x + rx;
    float br = y + x - rx;

    // Normalize to keep all powers within -1 to 1
    float maxPow = max(
      max(abs(fl), abs(fr)),
      max(abs(bl), abs(br))
    );

    if (maxPow > 1.0f) {
      fl /= maxPow;
      fr /= maxPow;
      bl /= maxPow;
      br /= maxPow;
    }

    frontLeft.motorSetPow(fl);
    frontRight.motorSetPow(fr);
    backLeft.motorSetPow(bl);
    backRight.motorSetPow(br);
  }

  void stop() {
    move(0, 0, 0);
  }
};

#endif
