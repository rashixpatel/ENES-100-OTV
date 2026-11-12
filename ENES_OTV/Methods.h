#include "Pins.h"
#include "Drive.h"
#include "Sensors.h"
#include "Vision.h"

// Instantiate duty sensor for copper tape reading
DutyCycle dutySensor(OUTPUT_PIN1);

void alignMission(MecanumDrive &drive) {
  float currentTheta = getCurrentTheta();

  while (abs(currentTheta) > 0.1) {
    if (currentTheta < 0) {
      drive.move(0, 0, 0.3);
    } else {
      drive.move(0, 0, -0.3);
    }
    currentTheta = getCurrentTheta();
    delay(50);
  }
  drive.stop();
}

void reachMission(MecanumDrive &drive, LimitSwitch &limitswitch) {
  while(!limitswitch.pressed()) {
    drive.move(0, 0.5, 0);
  }
  drive.stop();
  delay(5000);
}

Motor winchMotor(ENA_PIN3, IN1_PIN3, IN2_PIN3);

void probeAndSense() {
    winchMotor.motorSetPow(0.5f);  
    unsigned long startTime = millis();
    
    // Fixed subtraction for elapsed time calculation (- startTime)
    while (millis() - startTime < 5000) {
       if (hall.detected()) {
         Serial.println("Magnetism detected");
       } else {
         Serial.println("No magnetism detected");
       }

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

    winchMotor.motorSetPow(0.0);
    winchMotor.motorSetPow(-0.5);
    delay(5000); 
    winchMotor.motorSetPow(0.0);
}