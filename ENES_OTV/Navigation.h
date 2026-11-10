
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include <math.h>

#include "Drive.h"
#include "Vision.h"

// ========================================
// Navigation Configuration
// ========================================

const unsigned long VISION_DELAY = 250;

const float HEADING_TOLERANCE = 0.06;
const int HEADING_STABLE_COUNT = 3;

const float TURN_POWER = 0.35;

const int MIN_TURN_PULSE = 30;
const int MAX_TURN_PULSE = 250;

const float POSITION_TOLERANCE = 0.08;

const float DRIVE_POWER = 0.35;


// ========================================
// Navigation Class
// ========================================

class Navigation {

private:

    MecanumDrive& drive;

    // Normalize angle to [-PI, PI]
    float angleError(float target, float current) {

        float error = target - current;

        while (error > PI) error -= 2.0 * PI;
        while (error < -PI) error += 2.0 * PI;

        return error;
    }

    void stop() {
        drive.stop();
    }


public:

    Navigation(MecanumDrive& driveSystem)
        : drive(driveSystem) {}


    // ========================================
    // SET HEADING
    // ========================================

    bool setHeading(
        float targetTheta,
        unsigned long timeout = 15000
    ) {

        unsigned long startTime = millis();

        int stableCount = 0;

        while (millis() - startTime < timeout) {

            float currentTheta = getCurrentTheta();

            float error = angleError(
                targetTheta,
                currentTheta
            );

            // Check heading tolerance
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

            // Calculate rotation pulse
              int pulseDuration = constrain(
                  (int)(fabsf(error) * 250.0f),
                  MIN_TURN_PULSE,
                  MAX_TURN_PULSE
              );

            float turn = (error > 0)
                ? TURN_POWER
                : -TURN_POWER;

            // Rotate
            drive.move(0, 0, turn);

            delay(pulseDuration);

            // Stop and wait for vision update
            stop();

            delay(VISION_DELAY);
        }

        stop();
        return false;
    }


    // ========================================
    // GO TO X,Y
    // Mecanum translation, fixed heading
    // ========================================

    bool goToXY(
        float targetX,
        float targetY,
        unsigned long timeout = 30000
    ) {

        unsigned long startTime = millis();

        // Remember starting heading
        float targetTheta = getCurrentTheta();

        while (millis() - startTime < timeout) {

            float currentX = getCurrentX();
            float currentY = getCurrentY();

            // Calculate world-coordinate distance
            float dx = targetX - currentX;
            float dy = targetY - currentY;

            float distance = sqrtf(dx * dx + dy * dy);

            // Check arrival
            if (distance < POSITION_TOLERANCE) {
                stop();
                return true;
            }

            // Normalize target direction
            float worldX = dx / distance;
            float worldY = dy / distance;

            // Current robot heading
            float theta = getCurrentTheta();

            // Convert world direction to robot coordinates
            float robotX =
                worldX * cosf(theta) +
                worldY * sinf(theta);

            float robotY =
                -worldX * sinf(theta) +
                worldY * cosf(theta);

            // Heading correction
            float headingError = angleError(
                targetTheta,
                theta
            );

            float turnPower = constrain(
                headingError * 0.8f,
                -0.20f,
                0.20f
            );

            // Minimum correction to overcome motor deadband
            if (fabsf(headingError) > HEADING_TOLERANCE &&
                fabsf(turnPower) < 0.08f) {

                turnPower = (headingError > 0)
                    ? 0.08f
                    : -0.08f;
            }

            // Translate toward target
            float driveX = robotX * DRIVE_POWER;
            float driveY = robotY * DRIVE_POWER;

            drive.move(
                driveX,
                driveY,
                turnPower
            );

            // Wait for vision update
            delay(VISION_DELAY);
        }

        stop();
        return false;
    }


    // ========================================
    // HALT
    // ========================================

    void halt() {
        stop();
    }

};

#endif
