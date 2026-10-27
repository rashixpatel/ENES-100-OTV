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
  //move forward
  //lim switch false -> continue forward, true -> stop and wait 5 sec
  while(!limitSwitch.pressed()) {
    drive.move(0, 0.5, 0);
  }

  drive.stop();
  delay(5000);

}

void probeAndSense() {
  //lower probe w winch
  //measure duty
  //measure mag
  //continue lower for 5 s
  //raise probe
  


}