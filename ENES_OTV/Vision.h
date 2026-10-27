
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

    // Print the X coordinate
    Enes100.print("X Position: ");
    Enes100.println(currentX);

    // Wait half a second
    delay(500);
}
