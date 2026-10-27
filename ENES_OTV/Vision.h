#include "Arduino.h"
#include "Enes100.h"
#include "Tank.h"

void setup() {

    // Connect to ENES100 simulator
    Enes100.begin("Simulator", FIRE, 3, 1116, 8, 9);

    // Initialize tank system
    Tank.begin();

    // Print a message to confirm startup
    Enes100.println("Vision system started!");
}



void loop() {

    // Get the OTV's X coordinate
    float currentX = Enes100.getX();
    float currentY = Enes100.getY();
    float currentTheta = Enes100.getTheta();

    // Print the X coordinate
    Enes100.print("X Position: ");
    Enes100.println(currentX);

   // Print the Y coordinate
    Enes100.print("Y Position: ");
    Enes100.println(currentY);

    // Print the OTV's heading
    Enes100.print("Theta: ");
    Enes100.println(currentTheta);

 // Set a practice target angle
    float targetTheta = 0.0;

    // Find difference between target and current angle
    float difference = targetTheta - currentTheta;

    // Check if OTV is facing the target
    
   if (abs(difference) < 0.1) {

    Enes100.println("Facing target!");

} else if (difference > 0) {

    Enes100.println("Turn left!");

} else {

    Enes100.println("Turn right!");

}

    
    // Wait half a second
    delay(500);
}
