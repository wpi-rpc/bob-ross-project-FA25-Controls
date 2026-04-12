#include <Arduino.h>
#include "FastAccelStepper.h"
#include <Servo.h>
#include "constants.h"
#include <vector>

#include "esp_log.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();

struct command {
  unsigned short x,y;
  uint8_t z;
  uint8_t colour;
};

class Stepper {
  private:
  
    FastAccelStepper* motor = NULL;
    const int STEPPER_PIN; 
    const int DIR_PIN;
    const int EN_PIN;  

  public: 

  Stepper(const int stepper_pin, int dir_pin, int en_pin) 
    : STEPPER_PIN(stepper_pin), DIR_PIN(dir_pin), EN_PIN(en_pin) {}

  void init() {
    motor = engine.stepperConnectToPin(STEPPER_PIN);
    motor->setSpeedInHz(200);
    motor->setAcceleration(50);
    motor->setDirectionPin(DIR_PIN);
    motor->setEnablePin(EN_PIN);
    motor->setAutoEnable(true);
  }

  int getSteps(double cm) {
    return (int)(cm * 53.0);
  }

  double getCm(int steps) {
    return (double)steps / 53.0;
  }

  void moveTo(double cm) {
    motor->moveTo(getSteps(cm), false);
  } 

  double getPosition() {
    return getCm(motor->getCurrentPosition());
  }

  void setAcceleration(double accel) { motor->setAcceleration(getSteps(accel)); }
  double getAcceleration() { return getCm(motor->getAcceleration()); }
  bool isRunning() { return motor->isRunning(); }
};

class Gantry {
  private: 
  // motor pins
  const int X_STEP_PIN = 27;
  const int X_DIR_PIN = 14;
  const int Y_STEP_PIN = 26;
  const int Y_DIR_PIN = 13;
  const int EN_PIN = 23;
  // servo pins 
  const int Z_SERVO = 12; 
  const int COLOR_SERVO = 25;
  // limit switch pins 
  const int X_LIMIT_PIN = 19;
  const int Y_LIMIT_PIN = 18;
  // motors 
  Stepper motor_x = Stepper(X_STEP_PIN, X_DIR_PIN, EN_PIN);
  Stepper motor_y = Stepper(Y_STEP_PIN, Y_DIR_PIN, EN_PIN);
  Servo servo_z = Servo();
  Servo servo_color = Servo();

  // other params 
  double max_acceleration = 10; 


  public: 

  void init() {
    motor_x.init();
    motor_y.init();
    pinMode(X_LIMIT_PIN, INPUT_PULLUP);
    pinMode(Y_LIMIT_PIN, INPUT_PULLUP);
    servo_z.attach(Z_SERVO);
    servo_color.attach(COLOR_SERVO);
    servo_color.write(125); // DOING ONE COLOR FOR NOW
  }

  bool isAtXLimit() { return digitalRead(X_LIMIT_PIN); }
  bool isAtYLimit() { return digitalRead(Y_LIMIT_PIN); }
  void setMaxAcceleration(double accel) { 
    max_acceleration = accel;
  }

  void move(double x_cm, double y_cm) {
    double dx = x_cm - motor_x.getPosition();
    double dy = y_cm - motor_y.getPosition();
    if(std::abs(dx) < 0.001 && std::abs(dy) < 0.001) 
      return;
    
    double denom = std::pow(std::pow(dx, 2.0) + std::pow(dy, 2.0), 0.5);
    double accel_dx = (max_acceleration * dx) / denom;
    double accel_dy = (max_acceleration * dy) / denom;

    motor_x.setAcceleration(accel_dx);
    motor_y.setAcceleration(accel_dy);
    motor_x.moveTo(x_cm);
    motor_y.moveTo(y_cm);

    while(motor_x.isRunning() || motor_y.isRunning()) {}
  }

  void movePen(int penDown) {
    if(penDown == 1) {
      // move down 
      servo_z.write(42);
    } else if(penDown == 0) {
      // move up
      servo_z.write(75);
    }
  }
};

Servo servo1;
Servo servo2;
Gantry gantry = Gantry();
const int xLimitPin = 19; 
const int yLimitPin = 18;


void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17);    
  Serial.begin(115200, SERIAL_8N1);
  Serial.println("Serial monitor set up");
  delay(500);

  Serial.println("Device initialized");
  engine.init();
  gantry.init();
  
}

struct Command {
    double x;
    double y;
    double p; // 1 for down, 0 for up
};

// Generates smooth arc points between two angles
void addArc(std::vector<Command>& list, float cx, float cy, float r, float startDeg, float endDeg, int points = 12) {
    for (int i = 0; i <= points; ++i) {
        float angle = (startDeg + (endDeg - startDeg) * (i / (float)points)) * (M_PI / 180.0f);
        list.push_back({cx + r * cos(angle), cy + r * sin(angle), 1});
    }
}

struct Step {
    float x;
    float y;
    int pen; // 1 = down, 0 = up
};

command uart_in;
void loop() {
  // Data list representing the Smiley Face drawing
  // --- LETTER R ---
  std::vector<Step> path = {
        // --- LETTER R ---
        {0.5, 1.0, 0}, {0.5, 5.0, 1}, // Stem
        {1.5, 5.0, 1}, {1.8, 4.0, 1}, // Top
        {1.5, 3.0, 1}, {0.5, 3.0, 1}, // Mid-bar
        {1.2, 3.0, 0}, {1.8, 1.0, 1}, // Leg
        
        // --- LETTER P ---
        {2.2, 1.0, 0}, {2.2, 5.0, 1}, // Stem
        {3.2, 5.0, 1}, {3.5, 4.0, 1}, // Top
        {3.2, 3.0, 1}, {2.2, 3.0, 1}, // Mid-bar
        
        // --- LETTER C ---
        {5.5, 4.5, 0}, {4.8, 5.0, 1}, // Top curve
        {4.2, 4.5, 1}, {4.2, 1.5, 1}, // Back wall
        {4.8, 1.0, 1}, {5.5, 1.5, 1}  // Bottom curve
    };
    // Execution Loop
    for (const auto& cmd : path) {
      gantry.movePen((int)cmd.pen);
      gantry.move(4.0*cmd.x, 4.0*cmd.y);  
    }

    while(1);



    if (Serial2.available()) {
        Serial2.readBytes((char*)&uart_in, sizeof(uart_in));
        ESP_LOGI("uart_in", "(%d,%d,%d,%d)", uart_in.x, uart_in.y, uart_in.z, uart_in.colour);
        Serial2.write(0x06);
        ESP_LOGI("uart_out", "Acknowledged");
        char buffer[100];
        sprintf(buffer, "<x,y,z,c> = (%d, %d, %d, %d)", uart_in.x, uart_in.y, uart_in.z, uart_in.colour);
        gantry.movePen(uart_in.z);
        double c = 60.0;
        gantry.move(uart_in.x / c, uart_in.y / c);
        // 2. Print the buffer itself
        Serial.println(buffer);
    } else {
        delay(100);
    }

    Serial.println(digitalRead(yLimitPin));
}