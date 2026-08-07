
void readIMU() {
  IMU.getAGT();
  imuData.ax = IMU.accX(); 
  imuData.ay = IMU.accY(); 
  imuData.az = IMU.accZ();
  imuData.gx = IMU.gyrX();
  imuData.gy = IMU.gyrY();
  imuData.gz = IMU.gyrZ();
  float accelMagnitude = sqrt(
    imuData.ax * imuData.ax +
    imuData.ay * imuData.ay +
    imuData.az * imuData.az
);
}