void readBaro() {
    if (BARO.performReading()) {
        baroData.altitude = BARO.readAltitude(SeaLevelPressure_HPA);
        baroData.pressure = BARO.pressure / 100.0f;
        baroData.temperature = BARO.temperature;

        estimateVerticalVelocity(baroData.altitude, dt);
    }
}
void estimateVerticalVelocity(float altitude, float dt)
{
    // Raw derivative
    float rawVelocity = (altitude - previousAltitude) / dt;

    previousAltitude = altitude;

    // Low pass filter
    estimatedData.verticalVelocity = 0.9f * estimatedData.verticalVelocity + 0.1f * rawVelocity;
}
