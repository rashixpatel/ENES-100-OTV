#ifndef VISION_H
#define VISION_H

#include "Arduino.h"
#include "Enes100.h"

// Initialize vision once
void beginVision() {
    Enes100.begin("Simulator", FIRE, 3, 1116, 8, 9);
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
