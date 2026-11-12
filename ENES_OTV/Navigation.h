#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include <math.h>
#include "Drive.h"
#include "Vision.h"

const unsigned long VISION_DELAY = 250;
const float HEADING_TOLERANCE = 0.06;
const int HEADING_STABLE_COUNT = 3;
const float TURN_POWER = 0.35;
const int MIN_TURN_PULSE = 30;
const int MAX_TURN_PULSE = 250;
const float POSITION_TOLERANCE = 0.08;
const float DRIVE_POWER = 0.35;

class Navigation {
private:
    MecanumDrive& drive;

    float angleError(float target, float current) {
        float error = target - current;
        // Fixed 2.0PI -> 2.0f * PI
        while (error > PI) error -= 2.0f * PI;
        while (error < -PI) error += 2.0f * PI;
        return error;
    }

    void stop() {
        drive.stop();
    }

public:
    Navigation(MecanumDrive& driveSystem)
        : drive(driveSystem) {}

    bool setHeading(float targetTheta, unsigned long timeout = 15000) {
        unsigned long startTime = millis();
        int stableCount = 0;

        // Fixed millis()startTime -> millis() - startTime
        while ((millis() - startTime) < timeout) {
            float currentTheta = getCurrentTheta();
            float error = angleError(targetTheta, currentTheta);

            if (fabsf(error) < HEADING_TOLERANCE) {
                stop();
                stableCount++;
                if (stableCount >= HEADING_STABLE_COUNT) {
                    return true;
                }
                delay(VISION_DELAY);
                continue;
            }

            stableCount = 0;

            // Fixed missing multiplication operator (*)
            int pulseDuration = constrain(
                (int)(fabsf(error) * 250.0f),
                MIN_TURN_PULSE,
                MAX_TURN_PULSE
            );

            float turn = (error > 0) ? TURN_POWER : -TURN_POWER;

            drive.move(0, 0, turn);
            delay(pulseDuration);
            stop();
            delay(VISION_DELAY);
        }

        stop();
        return false;
    }

    bool goToXY(float targetX, float targetY, unsigned long timeout = 30000) {
        unsigned long startTime = millis();
        float targetTheta = getCurrentTheta();

        // Fixed millis()startTime -> millis() - startTime
        while ((millis() - startTime) < timeout) {
            float currentX = getCurrentX();
            float currentY = getCurrentY();

            float dx = targetX - currentX;
            float dy = targetY - currentY;
            float distance = sqrtf(dx * dx + dy * dy);

            if (distance < POSITION_TOLERANCE) {
                stop();
                return true;
            }

            float worldX = dx / distance;
            float worldY = dy / distance;
            float theta = getCurrentTheta();

            float robotX = worldX * cosf(theta) + worldY * sinf(theta);
            float robotY = -worldX * sinf(theta) + worldY * cosf(theta);

            float headingError = angleError(targetTheta, theta);
            float turnPower = constrain(headingError * 0.8f, -0.20f, 0.20f);

            if (fabsf(headingError) > HEADING_TOLERANCE && fabsf(turnPower) < 0.08f) {
                turnPower = (headingError > 0) ? 0.08f : -0.08f;
            }

            float driveX = robotX * DRIVE_POWER;
            float driveY = robotY * DRIVE_POWER;

            drive.move(driveX, driveY, turnPower);
            delay(VISION_DELAY);
        }

        stop();
        return false;
    }

    void halt() {
        stop();
    }
};

#endif