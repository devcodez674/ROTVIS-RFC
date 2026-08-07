void readBaro(){
    baroData.altitude = BARO.readAltitude(SeaLevelPressure_HPA);
    baroData.pressure = BARO.pressure / 100.0f; // in hPa
    baroData.temperature = BARO.temperature;
    EestimateVerticalVelocity(EstimatedData.altitude, dt);
}

void estimateVerticalVelocity(float altitude, float dt)
{
    // Raw derivative
    float rawVelocity = (altitude - previousAltitude) / dt;

    previousAltitude = altitude;

    // Low pass filter
    EstimatedData.verticalVelocity = 0.9f * EstimatedData.verticalVelocity + 0.1f * rawVelocity;
}
