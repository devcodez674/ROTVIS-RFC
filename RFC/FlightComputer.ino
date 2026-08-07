#include <SPI.h>
#include <ICM42688.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <math.h>
#include <Servo.h>
#include <Arduino.h>
#define FLASH_CS_PIN 11
#define PyroChnl1 22 
#define PyroChnl2 23 
#define PyroChnl3 24 
#define PyroChnl4 25 

#define FinServo1 2
#define FinServo2 3
#define FinServo3 4
#define FinServo4 5           

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
ICM42688 IMU(SPI, 10);
Servo servoFin1;
Servo servoFin2;
Servo servoFin3;
Servo servoFin4;
SPIFlash flash(FLASH_CS_PIN);

// Global state variables
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
    uint8_t landingCounter = 0;
    uint8_t parachuteCounter = 0;
    float dt;
    //Baro
    float SeaLevelPressure_HPA = 1023.25;
    float previousAltitude = 0.0f;
  //Pyro
    int CurrPyroChnl = 0;
  //Constants
    const float alpha = 0.98f;
    const float RADtoDEG = 57.2957795f;
  //battery
    const float BATT_DIV_RATIO = 4.0f;
    const uint8_t BATT_PIN = PA0;
    uint16_t battADC = 0;
  //Arrays
    bool pyroChnlState[5] = {false, false, false, false, false};
    uint8_t servoAngle[3];

void setup() {
  initialize();
}

void loop() {

  checkPyroState();
  bool Test = digitalRead(26);

  if (digitalRead(27) && currentState == stateCalibration) {
    Serial.println("ARMED");
    currentState = stateArmed;
  } 

  timeStart();
  readIMU();
  readBaro();
  updateEstimated();
  runDetectors();
  stateSwitcher();
}
