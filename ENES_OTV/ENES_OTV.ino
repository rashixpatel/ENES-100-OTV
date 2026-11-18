#include "Vision.h"
#include "Pins.h"
#include "Drive.h"
#include "Sensors.h"
#include "Navigation.h"
#include "Methods.h"

//motors and navigation
Motor frontLeft(ENA_PIN1, IN1_PIN1, IN2_PIN1, false);
Motor frontRight(ENB_PIN1, IN3_PIN1, IN4_PIN1, false);
Motor backLeft(ENA_PIN2, IN1_PIN2, IN2_PIN2, false);
Motor backRight(ENB_PIN2, IN3_PIN2, IN4_PIN2, false);

MecanumDrive drive(frontLeft, frontRight, backLeft, backRight);
Navigation nav(drive);

//sensors
HallEffect hall(OUTPUT_PIN1, true);
Ultrasonic ultrasonic1(TRIG_PIN1, ECHO_PIN1);
Ultrasonic ultrasonic2(TRIG_PIN2, ECHO_PIN2);
LimitSwitch limitSwitch(NO_PIN1, true);

void setup() {
  Serial.begin(9600);

  drive.begin();
  hall.begin();
  ultrasonic1.begin();
  ultrasonic2.begin();
  limitSwitch.begin();
  beginVision();

  delay(2000); 

  alignMission(drive);
  reachMission(drive, limitSwitch);

}

void loop() {
  // Keep empty during test
  drive.stop();
}