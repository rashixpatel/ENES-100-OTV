#ifndef VISION_H
#define VISION_H

#include "Arduino.h"
#include "Enes100.h"

// Initialize vision once
void beginVision() {
    Enes100.begin("Data Divers", DATA, 69, 1120, 50, 52);
    Enes100.println("Vision system started!");
}

// Get current OTV heading
float getCurrentTheta() {
    return Enes100.getTheta();
}

// Get current X position
float getCurrentX() {
    return Enes100.getX();
}

// Get current Y position
float getCurrentY() {
    return Enes100.getY();
}

#endif
