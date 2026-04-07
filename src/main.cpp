#include <Arduino.h>
#include "FastAccelStepper.h"
#include <Servo.h>
#include "constants.h"



FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper1 = NULL;
FastAccelStepper *stepper2 = NULL;
Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== FastAccelStepper ESP32 test ===");

  engine.init();
  Serial.println("Engine init done");

  stepper1 = engine.stepperConnectToPin(stepPinStepper1);
  stepper2 = engine.stepperConnectToPin(stepPinStepper2);

  if (!stepper1 || !stepper2) {
    Serial.println("ERROR: stepper is NULL! Check stepPinStepper and wiring.");
    while (true) {
      delay(1000);  // halt so we don't crash dereferencing a null pointer
    }
  }
  Serial.println("Stepper connected OK");

  stepper1->setDirectionPin(dirPinStepper1);
  stepper1->setEnablePin(enablePinStepper);
  stepper1->setAutoEnable(true);

  stepper2->setDirectionPin(dirPinStepper2);
  stepper2->setEnablePin(enablePinStepper);
  stepper2->setAutoEnable(true);

  stepper1->setSpeedInHz(1000);    // try a bit faster to clearly see motion
  stepper1->setAcceleration(800);

  stepper2->setSpeedInHz(500);    // try a bit faster to clearly see motion
  stepper2->setAcceleration(800);

  Serial.println("Stepper configured");

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  Serial.println("Servos configured");

}

void loop() {/*
  if (stepper1 && !(stepper1->isRunning())) {
    stepper1->runForward();
    // Serial.println(stepper1->getCurrentPosition());
    // stepper1->move(2000);
  }
  if (stepper2 && !(stepper2->isRunning())) {
  stepper2->runBackward();

  // Serial.println(stepper1->getCurrentPosition());
  // stepper1->move(2000);
  }
  if(servo1.read() == 180){
    servo1.write(0);
  } else {
    servo1.write(180);
  }
  if(servo2.read() == 180){
    servo2.write(0);
  } else {
    servo2.write(180);
  }
  delay(1000);*/
}






// void setup() {
//   engine.init();
//   stepper1 = engine.stepperConnectToPin(stepPinStepper1);
//   Serial.begin(115200);
//   if (stepper1) {
//     stepper1->setDirectionPin(dirPinStepper1);
//     stepper1->setAutoEnable(true);

//     stepper1->setSpeedInHz(500);       // 500 steps/s
//     stepper1->setAcceleration(100);    // 100 steps/s²
//     stepper1->move(1000);
//   }
// }

// void loop() {
//   //Serial.println("Hello");
//   stepper1->runForward();
// }

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }



// FastAccelStepperEngine engine;
// FastAccelStepper* stepper = nullptr;


