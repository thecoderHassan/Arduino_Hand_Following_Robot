/*
  Ultrasonic hand/target-following 4-wheel robot
  Board: Arduino Uno
  Motor driver: L298N dual H-bridge (red board in the photo appears to be L298N)
  Sensor: HC-SR04 ultrasonic sensor mounted on a servo

  IMPORTANT:
  The photos do not show readable pin labels or traceable connections, so this
  sketch uses the suggested pin map in README.md. Rewire to match it before
  uploading, or edit the pin constants below to match your actual wiring.
*/

#include <Servo.h>

// L298N motor driver pins
const byte ENA = 5;   // Left motor pair speed (PWM)
const byte IN1 = 8;
const byte IN2 = 9;
const byte IN3 = 10;
const byte IN4 = 11;
const byte ENB = 6;   // Right motor pair speed (PWM)

// HC-SR04 ultrasonic sensor pins
const byte TRIG_PIN = 12;
const byte ECHO_PIN = 13;

// Servo signal pin
const byte SERVO_PIN = 3;

Servo sensorServo;

// Tune these values for your chassis and environment.
const int MOTOR_SPEED = 165;        // 0..255
const int TURN_SPEED = 170;         // 0..255
const int OBSTACLE_CM = 25;
const int TOO_CLOSE_CM = 12;
const int SERVO_CENTER = 90;
const int SERVO_LEFT = 150;
const int SERVO_RIGHT = 30;

long readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Timeout prevents the code hanging if there is no echo.
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 25000UL);
  if (duration == 0) return 400; // no echo = treat as clear/far away
  long cm = (long)(duration * 0.0343 / 2.0);
  if (cm < 2 || cm > 400) return 400;
  return cm;
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setMotorSpeeds(MOTOR_SPEED, MOTOR_SPEED);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  setMotorSpeeds(MOTOR_SPEED, MOTOR_SPEED);
}

void turnLeft() {
  // Differential pivot: left side backward, right side forward.
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setMotorSpeeds(TURN_SPEED, TURN_SPEED);
}

void turnRight() {
  // Differential pivot: left side forward, right side backward.
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  setMotorSpeeds(TURN_SPEED, TURN_SPEED);
}

long scanAt(int angle) {
  sensorServo.write(angle);
  delay(350); // allow servo to reach its position
  delay(80);  // allow the sensor reading to settle
  // Take 3 readings and use the middle/typical result.
  long a = readDistanceCm();
  delay(40);
  long b = readDistanceCm();
  delay(40);
  long c = readDistanceCm();
  // Median of three values
  if (a > b) { long t = a; a = b; b = t; }
  if (b > c) { long t = b; b = c; c = t; }
  if (a > b) { long t = a; a = b; b = t; }
  return b;
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial.begin(9600);
  sensorServo.attach(SERVO_PIN);
  sensorServo.write(SERVO_CENTER);
  stopMotors();
  delay(500);

  Serial.println(F("Robot started: ultrasonic target following"));
}

void loop() {
  // The ultrasonic sensor cannot identify a hand specifically. It follows a
  // nearby object in its range; keep the hand as the closest object in view.
  sensorServo.write(SERVO_CENTER);
  delay(100);
  long front = readDistanceCm();

  Serial.print(F("Front: "));
  Serial.print(front);
  Serial.println(F(" cm"));

  // Maintain a comfortable distance from the target in front.
  if (front >= 18 && front <= 45) {
    forward();
    delay(60);
    return;
  }

  if (front < 18) {
    stopMotors();
    delay(100);
    backward();
    delay(180);
    stopMotors();
    delay(100);
    return;
  }

  // No target in the forward follow zone: look to either side.
  stopMotors();
  delay(100);
  long leftDistance = scanAt(SERVO_LEFT);
  long rightDistance = scanAt(SERVO_RIGHT);
  sensorServo.write(SERVO_CENTER);
  delay(120);

  Serial.print(F("Left: "));
  Serial.print(leftDistance);
  Serial.print(F(" cm | Right: "));
  Serial.print(rightDistance);
  Serial.println(F(" cm"));

  const long TARGET_MAX_CM = 100;
  bool targetLeft = (leftDistance >= 18 && leftDistance <= TARGET_MAX_CM);
  bool targetRight = (rightDistance >= 18 && rightDistance <= TARGET_MAX_CM);

  if (targetLeft && targetRight) {
    // Prefer the nearer side, which is a rough target-following heuristic.
    if (leftDistance <= rightDistance) {
      turnLeft();
      delay(220);
    } else {
      turnRight();
      delay(220);
    }
  } else if (targetLeft) {
    turnLeft();
    delay(300);
  } else if (targetRight) {
    turnRight();
    delay(300);
  } else {
    // No nearby target found: stay still rather than driving blindly.
    stopMotors();
  }

  stopMotors();
  delay(120);
}
