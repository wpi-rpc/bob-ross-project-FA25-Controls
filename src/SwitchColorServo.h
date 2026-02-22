#include <Servo.h>
#include "constants.h"

/**
 * Represents the servo on the Bob Ross project that changes the utensil being drawn with.
 */
class SwitchColorServo {
    private: 

    Color color = Color::FIRST;
    Servo servo;

    public: 

    /**
     * @brief Creates a SwitchColorServo instance
     */
    SwitchColorServo(uint8_t servoPin);
    bool checkColor(Color testColor);
    Color getColor();
    void setColor(Color newColor);

};