#define enablePinStepper 23

#define dirPinStepper1    14
#define stepPinStepper1   27

#define dirPinStepper2    13
#define stepPinStepper2   26


#define servoPin1 25
#define servoPin2 12

// #define UP 180 // angle that servo is up
// #define DOWN 0 // angle servo is down

#define stepsToRevolution 200
#define stepsToAnlge  stepsToRevolution / (2 * M_PI)
#define wheelRadius 10 // meters
 
namespace GPIOPins {
    uint8_t SERVO_Z = 0;
    uint8_t SERVO_COLOR = 1;
    
    uint8_t STEPPER_X_DIR = 2;
    uint8_t STEPPER_X_ENABLE = 3;
    uint8_t STEPPER_X_STEP = 4;

    uint8_t STEPPER_Y_DIR = 5;
    uint8_t STEPPER_Y_ENABLE = 6;
    uint8_t STEPPER_Y_STEP = 7;
};

enum Height {
    UP = 180,
    DOWN = 0
};

enum Color {
    FIRST = 0,
    SECOND = 30,
    THIRD = 60,
    FOURTH = 90,
    FIFTH = 120,
    SIXTH = 150
};

struct Position{
    int x = 0;
    int y = 0;
    
};