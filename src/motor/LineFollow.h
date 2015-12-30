#ifndef _LINEFOLLOW_H
#define _LINEFOLLOW_H

#include <ArduinoRobotMotorBoard.h>

#define N_SENSOR 5

class LineFollow {
    public:
        LineFollow();
        void commitLineFollow();
        void turArrounhd();
    private:
        int sensors[N_SENSOR];
        int black = 0, white = 100, border = 50;
        int sign = -1, sum = 0, last_error = 0;
        int mid;
};

#endif
