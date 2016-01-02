#include "PIDLineFollow.h"

#define ROBOT_SPEED 40
#define KP 8000
#define KD 64000
#define KI 3
#define INTEGRATION_TIME 2
#define EXTREM_FACTOR 0.05
#define CLOSE_FACTOR 2
#define BORDER 50

PIDLineFollow::PIDLineFollow() {
    mid_ = (int)(N_SENSOR / 2);
}

void PIDLineFollow::lineFollow() {
    bool inside;
    int sensors[N_SENSOR] = {0}, sum = 0, last_error = 0;
    do {
        updateSensors(sensors);
        int error = (sensors[0] * EXTREM_FACTOR) + sensors[1] * CLOSE_FACTOR - sensors[3] * CLOSE_FACTOR - (sensors[4] * EXTREM_FACTOR);
        error = map(error, - EXTREM_FACTOR * 100 - CLOSE_FACTOR * 100, EXTREM_FACTOR * 100 + CLOSE_FACTOR * 100, -100, 100);
        int vel = error * KP / 1000 + (error - last_error) * KD / 1000 + sum * KI / 1000;
        last_error = error;
        sum += error;
        int motor_left = constrain((ROBOT_SPEED - vel), -100, 100);
        int motor_right = constrain((ROBOT_SPEED + vel), -100, 100);
        RobotMotor.motorsWritePct(motor_left, motor_right);
        inside = checkLine(sensors);
        delay(INTEGRATION_TIME);
    } while (inside);
	RobotMotor.motorsStop();
}

void PIDLineFollow::turnArround() {
    sign_ *= -1;
    RobotMotor.motorsWritePct(35 * sign_, -35 * sign_);
    bool inside = false;
    do {
        for (int count = mid_; count < mid_ + 3; count++) {
            int value = map(RobotMotor.IRread(count + 1), 0, 1023, 0, 100);
            inside |= value < BORDER;
        }
    } while (!inside);
	RobotMotor.motorsStop();
}

bool PIDLineFollow::checkLine(int *sensors) {
    bool out = true, finish = true;
    for (int count = 0; count < N_SENSOR; count++) {
        finish &= sensors[count] < BORDER;
        out &= sensors[count] > BORDER;
    }
    return !out && !finish;
}

void PIDLineFollow::updateSensors(int *sensors) {
    for (int count = 0; count < N_SENSOR; count++) {
        int value = map(RobotMotor.IRread(count + 1), 0, 1023, 0, 100);
        sensors[count] = value;
    }
}
