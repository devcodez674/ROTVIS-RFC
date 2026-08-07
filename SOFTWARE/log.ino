#include <SPIFlash.h>
#pragma pack(push, 1)
FlightLog ramBuffer[5];
int bufferIndex = 0;
#pragma pack(pop)
uint32_t flashAddress = 0;
void initFlash(){
  SPI.begin();

if (!flash.begin()) {
    Serial.println("Flash init failed!");
    while (1);
}
}
void updateLog(){
    ramBuffer[bufferIndex].timestamp = now;
    ramBuffer[bufferIndex].pressure = baroData.pressure;
    ramBuffer[bufferIndex].altitude = baroData.altitude;
    ramBuffer[bufferIndex].temperature = baroData.temperature;
    ramBuffer[bufferIndex].ax = imuData.ax;
    ramBuffer[bufferIndex].ay = imuData.ay;
    ramBuffer[bufferIndex].az = imuData.az;
    ramBuffer[bufferIndex].gx = imuData.gx;
    ramBuffer[bufferIndex].gy = imuData.gy;
    ramBuffer[bufferIndex].gz = imuData.gz;
    ramBuffer[bufferIndex].pitch = estimatedData.pitch;
    ramBuffer[bufferIndex].roll = estimatedData.roll;
    ramBuffer[bufferIndex].yaw = estimatedData.yaw;
    ramBuffer[bufferIndex].estAltitude = estimatedData.altitude;
    ramBuffer[bufferIndex].verticalVelocity = estimatedData.verticalVelocity;
    ramBuffer[bufferIndex].batteryVoltage = estimatedData.BatteryVoltage;
    ramBuffer[bufferIndex].logStateNo = currentState;
    ramBuffer[bufferIndex].logPyroChnl = CurrPyroChnl;
    ramBuffer[bufferIndex].logServoAngle[0] = servoAngle[0];
    ramBuffer[bufferIndex].logServoAngle[1] = servoAngle[1];
    ramBuffer[bufferIndex].logServoAngle[2] = servoAngle[2];
    ramBuffer[bufferIndex].logServoAngle[3] = servoAngle[3];
    bufferIndex++;
    if (bufferIndex >= 5) {
      updateFlash();
      bufferIndex = 0;
    }
}
void updateFlash(){
    //write the entire ramBuffer into flas
    flash.writeByteArray(flashAddress, (uint8_t*)ramBuffer, sizeof(ramBuffer));
    // Move our memory address forward so we don't overwrite previous logs
    flashAddress = flashAddress + sizeof(ramBuffer);
}
