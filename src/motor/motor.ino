#include <Arduino.h>
#include <ArduinoRobotMotorBoard.h>
#include "utility/credentials.h"
#include "utility/aros_definitions.h"
#include "PIDLineFollow.h"

PIDLineFollow lf;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  RobotMotor.begin();
}

void loop() {
  int n = Serial1.available();
  if (n > 0) {
    byte msg = Serial1.read();
    masterSelector(msg);
  }
}

void masterSelector(const byte &msg) {
  switch (msg) {
    case MOTOR_COMMAND_LINE_FOLLOW:
      Serial.println("Following line");
      lf.lineFollow();
      Serial1.write(MOTOR_COMMAND_LINE_FOLLOW_END);
      break;
    case MOTOR_COMMAND_TURN_ARROUND:
      Serial.println("Turning arround");
      lf.turnArround();
      Serial1.write(MOTOR_COMMAND_TURN_ARROUND_END);
      break;
    default:
      break;
  }
}
