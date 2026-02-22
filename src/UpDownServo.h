#include <Servo.h>
#include "constants.h"



class UpDownServo {
    Height height = UP;

    Servo servo;

    UpDownServo(uint8_t servoPin);

    bool checkUp();
    bool checkDown();

    void moveUp();
    void moveDown();

    Height getHeight();
};