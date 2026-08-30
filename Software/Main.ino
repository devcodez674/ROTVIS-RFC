#include <SPI.h>
#include <ICM42688.h>
#include <SPIMemory.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <math.h>
#include <Servo.h>

#define PyroChnl1 PB5
#define PyroChnl2 PB6 
#define PyroChnl3 PB7 
#define PyroChnl4 PB8 

#define PyroCont1 PB12
#define PyroCont2 PB13
#define PyroCont3 PB14
#define PyroCont4 PB15

#define FinServo1 PA0
#define FinServo2 PA1
#define FinServo3 PA2
#define FinServo4 PA3           
#define armPin PA11
#define testPin PA12
#define baroCsPin PA8
#define imuCsPin PA9
#define flashCsPin PA10
#define BATT_PIN PA7
#define buzzerPin PB9
#define ledPin PB0


struct IMUData {
  float ax, ay, az, gx, gy, gz;
};
struct BaroData {
  float pressure, altitude, temperature;
};
struct EstimatedData {
  float pitch, roll, yaw;
  float altitude, BatteryVoltage, verticalVelocity;
};
struct FlightLog {
   uint32_t timestamp; 
    // barometer data
    float pressure, altitude, temperature;

    // IMU data
    float ax, ay, az, gx, gy, gz;

    // estimated data
    float pitch, roll, yaw;
    float estAltitude;
    float verticalVelocity;
    float batteryVoltage;


  //state data
  uint8_t logStateNo;
  uint8_t logPyroChnl;
  uint8_t logServoAngle[4];

};
enum flightState {
  stateIdle,
  stateCalibration,
  stateArmed,
  stateAscent,
  stateCoast,
  stateApogee,
  stateDescent,
  stateLanded,
  stateTest
};
//Struct objects
IMUData imuData;
BaroData baroData;
EstimatedData estimatedData;
flightState currentState = stateIdle;

//OBJECTs
Adafruit_BMP3XX BARO;
ICM42688 IMU(SPI, 11);
Servo servoFin1;
Servo servoFin2;
Servo servoFin3;
Servo servoFin4;
SPIFlash flash(flashCsPin, &SPI);

// Global state variables
  bool Test;
  float accelMagnitude;
  //Time
    unsigned long startTime;
    unsigned long endTime;
    unsigned long launchStart = 0;
    unsigned long apogeeStart = 0;
    unsigned long now = 0;
    unsigned long lastIMURead = 0;
    unsigned long lastBaroRead = 0;
    unsigned long lastLogTime = 0;
    unsigned long prevMicros = 0;
    uint8_t apogeeCounter = 0;
    uint8_t coastCounter = 0;
    unsigned long landingCounter = 0;
    unsigned long parachuteCounter = 0;
    float dt;
    //Baro
    float SeaLevelPressure_HPA = 1023.25;
    float previousAltitude = 0.0f;
  //Pyro
    int CurrPyroChnl = 0;
    bool pyroArmed = false;
  //Constants
    const float alpha = 0.98f;
    const float RADtoDEG = 57.2957795f;
  //battery
    const float BATT_DIV_RATIO = 4.0f;
    uint16_t battADC = 0;
    //target
    float targetPitch = 0;
    float targetYaw = 0;
    //control
    float Kp = 1;
    float Kd = 1;
    float pitchCmd = 0;
    float yawCmd = 0;
    float pitchError = 0;
    float yawError = 0;
  //Arrays
    bool pyroChnlState[5] = {false, false, false, false, false};
    uint8_t servoAngle[4];

void setup() {
  initialize();
}

void loop() {

  checkPyroState();
  Test = digitalRead(testPin);

  if (digitalRead(armPin) && (currentState == stateCalibration || currentState == stateTest)) {
    Serial.println("ARMED");
    currentState = stateArmed;
  } 

  timeStart();
  stateSwitcher();
  runDetectors();
}
