#include <Servo.h>
#include "constants.h"

class SwitchColorServo {
    Color color = FIRST;

    Servo servo;

    SwitchColorServo(uint8_t servoPin);

    bool checkColor(Color testColor);

    Color getColor();

    void setColor(Color newColor);

};