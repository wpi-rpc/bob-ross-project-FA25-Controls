#include "GantryStepper.h"
#include "UpDownServo.h"
#include "SwitchColorServo.h"

/**
 * @brief Represent the Bob Ross robot gantry. The gantry logic involves sensors and stepper/servo motor actuation. 
 * The sensors used are limit switches. 
 */
class Gantry {
    private: 
    
    // servo class members 
    UpDownServo& zServo;
    SwitchColorServo& colorServo;
    // stepper class members 
    GantryStepper& stepperX;
    GantryStepper& stepperY;

    public: 

    /**
     * @brief Create a Gantry instance. 
     */
    Gantry();
    
    /**
     * @brief Initializes the robot gantry. This function is called once. 
     */
    void setup();

    /**
     * @brief Runs the robot gantry. This function is iteratively/continuously called. 
     */
    void loop();
};