#include "GantryStepper.h"
#include "UpDownServo.h"
#include "SwitchColorServo.h"
#include "Gantry.h"

Gantry :: Gantry() {
    // create gantry stepper motor engine
    FastAccelStepperEngine engineX = FastAccelStepperEngine();
    FastAccelStepperEngine engineY = FastAccelStepperEngine();
    // initialize servos 
    zServo = UpDownServo(GPIOPins::SERVO_Z);
    colorServo = SwitchColorServo(GPIOPins::SERVO_COLOR);
    // initializes stepper 
    stepperX = GantryStepper(engineX, GPIOPins::STEPPER_X_STEP, GPIOPins::STEPPER_X_DIR, GPIOPins::STEPPER_X_ENABLE);
    stepperY = GantryStepper(engineY, GPIOPins::STEPPER_Y_STEP, GPIOPins::STEPPER_Y_DIR, GPIOPins::STEPPER_Y_ENABLE);
}

void Gantry :: setup() {

}

void Gantry :: loop() {

}

