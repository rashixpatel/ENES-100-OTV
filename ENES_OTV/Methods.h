#include "Pins.h"
#include "Drive.h"
#include "Sensors.h"

void alignMission() {
  //measure theta and turn
  // align no, continue in loop, align yes stop
  int theta = //jahiem
  while(currentTheta != 0) {
    //jahiem

  }

}

void reachMission(MecanumDrive &drive, LimitSwitch &limitswitch) {
  while(!limitSwitch.pressed()) {
    drive.move(0, 0.5, 0);
  }

  drive.stop();
  delay(5000);

}

Motor winchMotor(ENA_PIN3, IN1_PIN3, IN2_PIN3);
void probeAndSense() {
  //measure duty
  //measure mag
  //continue lower for 5 s
  //raise probe
  winchMotor.motorSetPow(0.5);
  if(hall.detected()) {
    Serial.println("Magnetism detected")
  }
  




}