
#ifndef PINS_H
#define PINS_H

// ========================================
// L298N #1 - Drive motors (2 wheels)
// ========================================

const int ENB_PIN1 = 4;
const int IN4_PIN1 = 5;
const int IN3_PIN1 = 6;
const int IN2_PIN1 = 7;
const int IN1_PIN1 = 8;
const int ENA_PIN1 = 9;


// ========================================
// L298N #2 - Drive motors (2 wheels)
// ========================================

const int ENB_PIN2 = 2;
const int IN4_PIN2 = 28;
const int IN3_PIN2 = 26;
const int IN2_PIN2 = 24;
const int IN1_PIN2 = 22;
const int ENA_PIN2 = 3;


// ========================================
// L298N #3 - Winch motor
// ========================================

const int ENA_PIN3 = 12;
const int IN1_PIN3 = 11;
const int IN2_PIN3 = 10;


// ========================================
// Limit switch
// ========================================

const int NO_PIN1 = 48;


// ========================================
// Hall effect sensor
// ========================================

const int OUTPUT_PIN1 = 46;


// ========================================
// Ultrasonic sensors
// ========================================

// Ultrasonic 1
const int TRIG_PIN1 = A9;
const int ECHO_PIN1 = A8;

// Ultrasonic 2
const int TRIG_PIN2 = A7;
const int ECHO_PIN2 = A6;


// ========================================
// Servo
// ========================================

const int PWM_PIN1 = 13;


// ========================================
// Wi-Fi module
// ========================================

const int TX_PIN1 = 50;
const int RX_PIN1 = 52;


// ========================================
// Mecanum drive PWM note
// ========================================

// Arduino Mega PWM pins include 2-13 and 44-46.
// ENB_PIN1 = 4 is NOT PWM-capable.
// If you need variable speed on this channel,
// move its enable wire to an available PWM pin.

#endif
