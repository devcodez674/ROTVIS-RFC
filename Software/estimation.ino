void compFilter(
    float ax, float ay, float az,
    float gx, float gy, float gz
){
    float accelPitch = atan2(-ax, sqrt(ay * ay + az * az)) * RADtoDEG;
    float accelYaw   = atan2(az, sqrt(ax * ax + ay * ay)) * RADtoDEG;

    estimatedData.pitch += gx * dt;
    estimatedData.yaw += gz * dt;
    estimatedData.pitch =     alpha * estimatedData.pitch + (1.0f - alpha) * accelPitch;
    estimatedData.yaw =     alpha * estimatedData.yaw + (1.0f - alpha) * accelYaw;
}
void updateEstimated(){
  estimatedData.roll += imuData.gy * dt;//intergration
  findBattVoltage();
  estimatedData.altitude = baroData.altitude;
  compFilter(imuData.ax, imuData.ay, imuData.az, imuData.gx, imuData.gy, imuData.gz);
}