void servoMixer(){
  // Roll angle in radians
  float roll = estimatedData.roll * DEG_TO_RAD;

    // Rotate the commands into the rocket's current body frame
    float bodyPitch = pitchCmd * cos(roll) + yawCmd * sin(roll);
    float bodyYaw   = -pitchCmd * sin(roll) + yawCmd * cos(roll);

    // + Fin Configuration
    servoAngle[0] = constrain(90 + bodyPitch, 70, 110); // Top
    servoAngle[1] = constrain(90 + bodyYaw,   70, 110); // Right
    servoAngle[2] = constrain(90 - bodyPitch, 70, 110); // Bottom
    servoAngle[3] = constrain(90 - bodyYaw,   70, 110); // Left
    WriteServos(90 + bodyPitch, 0);
    WriteServos(90 + bodyYaw,   1);
    WriteServos(90 - bodyPitch, 2);
    WriteServos(90 - bodyYaw,   3);
}
void runStability()
{
    targetPitch = 0.0f;
    targetYaw   = 0.0f;
    updateEstimated();
    pitchError = targetPitch - estimatedData.pitch;
    yawError   = targetYaw   - estimatedData.yaw;
    
    pitchCmd = Kp * pitchError - Kd * imuData.gx;
    yawCmd   = Kp * yawError - Kd * imuData.gz;

    servoMixer();
}