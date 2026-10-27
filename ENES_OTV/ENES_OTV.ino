
// hbridge constants
// 2 wheel motors
const int ENB_PIN1 = 4; //Arduino pin connected to the EN1 pin L298N
const int IN4_PIN1 = 5; //Arduino pin connected to the IN1 pin L298N
const int IN3_PIN1 = 6; //Arduino pin connected to the IN2 pin L298N
const int IN2_PIN1 = 7; //Arduino pin connected to the IN1 pin L298N
const int IN1_PIN1 = 8; //Arduino pin connected to the IN2 pin L298N
const int ENA_PIN1 = 9; //Arduino pin connected to the EN1 pin L298N

//2 wheel motors
const int ENB_PIN2 = 2; //Arduino pin connected to the EN1 pin L298N
const int IN4_PIN2 = 28; //Arduino pin connected to the IN1 pin L298N
const int IN3_PIN2 = 26; //Arduino pin connected to the IN2 pin L298N
const int IN2_PIN2 = 24; //Arduino pin connected to the IN1 pin L298N
const int IN1_PIN2 = 22; //Arduino pin connected to the IN2 pin L298N
const int ENA_PIN2 = 3; //Arduino pin connected to the EN1 pin L298N


//winch motors
const int ENA_PIN3 = 12; //Arduino pin connected to the EN1 pin L298N
const int IN1_PIN3 = 11; //Arduino pin connected to the IN1 pin L298N
const int IN2_PIN3 = 10; //Arduino pin connected to the IN2 pin L298N

//limit switch
const int NO_PIN1 = 48; //Arduino pin connnected to the NO pin for lim switch

//hall effect sensor
const int OUTPUT_PIN1 = 46; //Arduino pin connnected to the OUTPUT pin for hall effect

//ultrasonic constants
//ultrasonic 1
const int TRIG_PIN1 = A9; 
const int ECHO_PIN1 = A8;

//ultrasonic 2
const int TRIG_PIN2 = A7;
const int ECHO_PIN2 = A6;

//servo
const int PWM_PIN1 = 13;

//wifi module
const int TX_PIN1 = 50;
const int RX_PIN1 = 52;




// the setup function runs once when you press reset or power the board
void setup() {
  Enes100.begin("Data Divers", DATA, 69, 1120, TX_PIN1, TX_PIN1)
  // initialize digital pins as outputs.
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(IN1_PIN, HIGH); // control motor A spins clockwise
  digitalWrite(IN2_PIN, LOW);  // control motor A spins clockwise

  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(ENA_PIN, speed); // control the speed
    delay(10);
  }

  delay(1000); // rotate at maximum speed 1 seconds in in clockwise direction

  // change direction
  digitalWrite(IN1_PIN, LOW);   // control motor A spins anti-clockwise
  digitalWrite(IN2_PIN, HIGH);  // control motor A spins anti-clockwise

  delay(1000); // rotate at maximum speed 1 seconds in in anti-clockwise direction

  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(ENA_PIN, speed); // control the speed
    delay(10);
  }

  delay(1000); // stop motor 1 second
}
