#include <Servo.h>
#include "constants.h"


/**
 * @brief Represents the servo on the Bob Ross project that actuates along the z-axis. 
 */
class UpDownServo {
    private: 

    Height height = Height::UP;
    Servo servo;

    public:

    /**
     * @brief Creates a UpDownServo instance
     */
    UpDownServo(uint8_t servoPin);

    bool checkUp();
    bool checkDown();

    void moveUp();
    void moveDown();

    Height getHeight();
};