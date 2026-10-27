
#include "Pins.h"
#include "Drive.h"
#include "Sensors.h"

// ========================================
// Mecanum drive motors
// ========================================

Motor frontLeft(ENA_PIN1, IN1_PIN1, IN2_PIN1);
Motor frontRight(ENB_PIN1, IN3_PIN1, IN4_PIN1);
Motor backLeft(ENA_PIN2, IN1_PIN2, IN2_PIN2);
Motor backRight(ENB_PIN2, IN3_PIN2, IN4_PIN2);

MecanumDrive drive(
  frontLeft,
  frontRight,
  backLeft,
  backRight
);


// ========================================
// Sensors
// ========================================

HallEffect hall(OUTPUT_PIN1, true);

Ultrasonic ultrasonic1(TRIG_PIN1, ECHO_PIN1);
Ultrasonic ultrasonic2(TRIG_PIN2, ECHO_PIN2);

LimitSwitch limitSwitch(NO_PIN1, true);


// ========================================
// Setup
// ========================================

void setup() {
  Serial.begin(9600);

  // Initialize drive motors
  drive.begin();

  // Initialize sensors
  hall.begin();
  ultrasonic1.begin();
  ultrasonic2.begin();
  limitSwitch.begin();

  Serial.println("ENES OTV initialized");
}


// ========================================
// Main loop
// ========================================

void loop() {
  // --------------------------------------
  // Hall effect sensor
  // --------------------------------------

  if (hall.detected()) {
    Serial.println("Magnet detected");
  }

  // --------------------------------------
  // Ultrasonic sensor 1
  // --------------------------------------

  float distance1 = ultrasonic1.getDistanceCm();

  Serial.print("Ultrasonic 1: ");

  if (distance1 >= 0) {
    Serial.print(distance1);
    Serial.println(" cm");
  } else {
    Serial.println("No echo");
  }

  // --------------------------------------
  // Ultrasonic sensor 2
  // --------------------------------------

  float distance2 = ultrasonic2.getDistanceCm();

  Serial.print("Ultrasonic 2: ");

  if (distance2 >= 0) {
    Serial.print(distance2);
    Serial.println(" cm");
  } else {
    Serial.println("No echo");
  }

  // --------------------------------------
  // Limit switch
  // --------------------------------------

  if (limitSwitch.pressed()) {
    Serial.println("Limit switch pressed");
  }

  // --------------------------------------
  // Drive control
  // --------------------------------------

  // Keep the robot stopped while testing sensors.
  drive.stop();

  delay(100);
}
