#include <Servo.h>

// Define constants
#define KP 0.1
#define KI 0.01
#define KD 0.5
#define SERVO_PIN 9
#define X_PIN A0
#define Y_PIN A1
#define SETPOINT_X 0
#define SETPOINT_Y 0
#define SAMPLE_TIME 2

// Declare variables
float error_x = 0.0, error_y = 0.0;
float integral_x = 0.0, integral_y = 0.0;
float derivative_x = 0.0, derivative_y = 0.0;
float last_error_x = 0.0, last_error_y = 0.0;
float output_x = 0.0, output_y = 0.0;
float x = 0.0, y = 0.0;
Servo servo;

void setup() {
  // Set up serial communication
  Serial.begin(9600);

  // Set up servo motor
  servo.attach(SERVO_PIN);

  // Initialize variables
  last_error_x = SETPOINT_X - x;
  last_error_y = SETPOINT_Y - y;
}

void loop() {
  // Read sensor values
  x = analogRead(X_PIN);
  y = analogRead(Y_PIN);

  // Calculate errors
  error_x = SETPOINT_X - x;
  error_y = SETPOINT_Y - y;

  // Calculate integral terms
  integral_x += error_x * SAMPLE_TIME;
  integral_y += error_y * SAMPLE_TIME;

  // Calculate derivative terms
  derivative_x = (error_x - last_error_x) / SAMPLE_TIME;
  derivative_y = (error_y - last_error_y) / SAMPLE_TIME;

  // Calculate output values
  output_x = KP * error_x + KI * integral_x + KD * derivative_x;
  output_y = KP * error_y + KI * integral_y + KD * derivative_y;

  // Save current errors
  last_error_x = error_x;
  last_error_y = error_y;

  // Limit output values to servo range
  output_x = constrain(output_x, -45, 45);
  output_y = constrain(output_y, -45, 45);

  // Move servo to new position
  servo.write(90 + output_x);

  // Print debug information
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("\tY: ");
  Serial.print(y);
  Serial.print("\tOutput X: ");
  Serial.print(output_x);
  Serial.print("\tOutput Y: ");
  Serial.println(output_y);

  // Wait for next sample time
  delay(SAMPLE_TIME);
}
