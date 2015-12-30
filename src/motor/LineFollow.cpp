#include "LineFollow.h"

#define ROBOT_SPEED 40
#define KP 8000
#define KD 64000
#define KI 3
#define INTEGRATION_TIME 2
#define EXTREM_FACTOR 0.05
#define CLOSE_FACTOR 2

LineFollow::LineFollow() {
    RobotMotor.begin();
    memset(sensors, 0, N_SENSOR);
    mid = (int)(N_SENSOR / 2);
}

LineFollow::commitFollow() {
    int vel = 0;
    bool out = true, finish = true;
    for (int count = 0; count < N_SENSOR; count++) {
        int value = map(RobotMotor.IRread(count + 1), 0, 1023, 0, 100);
        finish &= value < border;
        out &= value > border;
        sensors[count] = value;
    }

    while (!finish && !out) {
        int error = (sensors[0] * EXTREM_FACTOR) + sensors[1] * CLOSE_FACTOR - sensors[3] * CLOSE_FACTOR - (sensors[4] * EXTREM_FACTOR);
        error = map(error, - EXTREM_FACTOR * 100 - CLOSE_FACTOR * 100, EXTREM_FACTOR * 100 + CLOSE_FACTOR * 100, -100, 100);
        vel = error * KP / 1000 + (error - last_error) * KD / 1000 + sum * KI / 1000;
        last_error = error;
        sum += error;
        int motor_left = constrain((ROBOT_SPEED - vel), -100, 100);
        int motor_right = constrain((ROBOT_SPEED + vel), -100, 100);
        RobotMotor.motorsWritePct(motor_left, motor_right);
        delay(INTEGRATION_TIME);
    }
}

void loop() {
    } else {
        sum = 0;
        last_error = 0;
        sign *= -1;
        RobotMotor.motorsWritePct(35 * sign, -35* sign);
        bool inside = false;
        do {
            for (int count = mid; count < mid + 3; count++) {
                int value = map(RobotMotor.IRread(count + 1), 0, 1023, 0, 100);
                inside |= value < border;
            }
        } while (!inside);

}
