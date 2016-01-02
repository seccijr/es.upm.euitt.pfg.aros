#ifndef _PIDLINEFOLLOW_H
#define _PIDLINEFOLLOW_H

#include <ArduinoRobotMotorBoard.h>

#define N_SENSOR 5

class PIDLineFollow {
    public:
        PIDLineFollow();
        void lineFollow();
        void turnArround();
    private:
        bool checkLine(int *sensors);
        void updateSensors(int *sensors);
        int mid_, sign_ = -1;
};

#endif
