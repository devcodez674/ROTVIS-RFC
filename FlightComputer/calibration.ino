

void pressureCalib(){
    delay(1000);
  for (int i = 0; i < 10; i++) {
    BARO.performReading();
    delay(10);
  }
  if (BARO.performReading()) {
    SeaLevelPressure_HPA = BARO.pressure / 100.0f;
  }
}