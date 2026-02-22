#include "UpDownServo.h"
#include <Arduino.h>

UpDownServo :: UpDownServo(uint8_t servoPin) {
    servo.attach(servoPin);
    servo.write(height);
}

bool UpDownServo :: checkUp(){
    return servo.read() == UP;
}

bool UpDownServo :: checkDown(){
    return servo.read() == DOWN;
}

void UpDownServo :: moveUp(){
    if (checkDown()) {
        height = UP;
        servo.write(height);
        delay(1000);
    }
    
}

void UpDownServo :: moveDown(){
    if (checkUp()) {
        height = DOWN;
        servo.write(height);
        delay(1000);
    }
}

Height UpDownServo :: getHeight() {
    return height;
}