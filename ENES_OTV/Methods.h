#include "Pins.h"
#include "Drive.h"
#include "Sensors.h"
#include "Vision.h"

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

    //Lower probe with winch
    winchMotor.motorSetPow(0.5f);  
    unsigned long startTime = millis();
    
    //Continue lowering for 5 seconds while measuring/sensing
    while (millis() - startTime < 5000) {
     // Check magnet
     if (hall.detected()) {
      Serial.println("Magnetism detected");
      } else {
        Serial.println("No magnetism detected");
      }

    //Measure duty cycle from copper tape
      float duty = dutySensor.getDutyCycle();
      if (duty >= 0) {
          Serial.print("Duty Cycle: ");
          Serial.print(duty);
          Serial.println("%");
      } else {
          Serial.println("No signal detected");
      }
      
      delay(1000);
}

    //Stop lowering after 5 seconds
    winchMotor.motorSetPow(0.0);
    //Raise the probe back up
    winchMotor.motorSetPow(-0.5);
    delay(5000); // Adjust depending on how long it takes
    //Stop the winch completely
    winchMotor.motorSetPow(0.0);

  
}