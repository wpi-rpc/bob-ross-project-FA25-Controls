#include "SwitchColorServo.h"
#include <Arduino.h>

SwitchColorServo :: SwitchColorServo(uint8_t servoPin) {
    servo.attach(servoPin);
    servo.write(color);
}

bool SwitchColorServo :: checkColor(Color testColor){
    return color == testColor;
}

Color SwitchColorServo :: getColor(){
    return color;
}

void SwitchColorServo :: setColor(Color newColor) {
    if (color != newColor) {
        color = newColor;
        servo.write(color);
        delay(1000);
    }
}


