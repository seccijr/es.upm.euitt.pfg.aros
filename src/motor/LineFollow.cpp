#include <ArduinoRobotMotorBoard.h>

#define ROBOT_SPEED 40
#define KP 30
#define KD 5
#define KI 10
#define INTEGRATION_TIME 1
#define N_SENSOR 5
#define EXTREM_FACTOR 10
#define OUT_FACTOR 1.3

int sensors[N_SENSOR] = {0};
int black = 1023, white = 0;
int border = 512;
int mid = 0;

void setup() {
  Serial.begin(9600);
  RobotMotor.begin();
  doCalibration(30, 500);
  doCalibration(-30, 800);
  doCalibration(30, 500);
  border = (int)map((white - black) / 2, 0, 1023, 0, 100);
  mid = (int)(N_SENSOR / 2);
}

void loop() {
  int last_error = 0, corr = 0, sum = 0, vel = 0;
  bool out = true, finish = true;
  for (int count = 0; count < N_SENSOR; count++) {
    int value = map(RobotMotor.IRread(count + 1), 0, 1023, 0, 100);
    finish &= value < border;
    out &= value > border * OUT_FACTOR;
    sensors[count] = value;
  }

  if (!finish && !out) {
    int error = (sensors[0] * EXTREM_FACTOR) + sensors[1] - sensors[3] - (sensors[4] * EXTREM_FACTOR);
    error = constrain(error, -100, 100);
    vel = error * KP / 100 + (error - last_error) * KD / 100 + sum * KI / 100;
    last_error = error;
    sum += error;
    int motor_left = constrain((ROBOT_SPEED - vel), -100, 100);
    int motor_right = constrain((ROBOT_SPEED + vel), -100, 100);
    RobotMotor.motorsWritePct(motor_left, motor_right);
  } else {
    RobotMotor.motorsStop();
  }
  delay(INTEGRATION_TIME);
}

void doCalibration(int speed, int time) {
  RobotMotor.motorsWritePct(speed, -speed);
  unsigned long beginTime = millis();
  while ((millis() - beginTime) < time) {
    setLevels();
  }
  RobotMotor.motorsStop();
}

void setLevels() {
  int lectura = 0;
  for (int count = 0; count < N_SENSOR; count++) {
    lectura = RobotMotor.IRread(count);
    if (lectura > white) {
      white = lectura;
    }
    if (lectura < black) {
      black = lectura;
    }
  }
}
