void compFilter(
    float ax, float ay, float az,
    float gx, float gy, float gz
){
    float accelPitch = atan2(-ax, sqrt(ay * ay + az * az)) * RADtoDEG;
    float accelYaw   = atan2(az, sqrt(ax * ax + ay * ay)) * RADtoDEG;

    EstimatedData.pitch += gx * dt;
    EstimatedData.yaw += gz * dt;
    EstimatedData.pitch =
    alpha * EstimatedData.pitch +
    (1.0f - alpha) * accelPitch;
    EstimatedData.yaw =
    alpha * EstimatedData.yaw +
    (1.0f - alpha) * accelYaw;
}
void updateEstimated(){
  EstimatedData.roll += imuData.gy * dt;//intergration
  findBattVoltage();
  readBaro();
  compFilter(imuData.ax, imuData.ay, imuData.az, imuData.gx, imuData.gy, imuData.gz);
}