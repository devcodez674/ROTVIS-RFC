void CheckSensors() {
  Serial.println("-----Testing-----");
  readIMU();

  Serial.print("Accel (g): ");
  Serial.print(imuData.ax); Serial.print(", ");
  Serial.print(imuData.ay); Serial.print(", ");
  Serial.print(imuData.az);

  Serial.print(" | Gyro (deg/s): ");
  Serial.print(imuData.gx); Serial.print(", ");
  Serial.print(imuData.gy); Serial.print(", ");
  Serial.println(imuData.gz);
  Serial.println("IMU TESTING COMPLETE GOING TO BARO");

  if (!BARO.performReading()) {
    Serial.println("Failed to read BMP388");
    errorWarn();
    delay(2000);
    errorClear();
    return;
  }

  float temp = BARO.temperature;
 float pressure = BARO.pressure / 100.0f;
  float altitude = BARO.readAltitude(SeaLevelPressure_HPA);

  Serial.print(" Temperature: "); Serial.print(temp);
  Serial.print("C | Pressure: "); Serial.print(pressure);
  Serial.print(" hPa | Altitude: "); Serial.print(altitude);
  Serial.println(" m");

  int BatteryRaw = analogRead(A0);
  Serial.print("Battery Raw ADC: "); Serial.println(BatteryRaw);
}
void PyroContinuityTest() {

  Serial.println("---- PYRO CONTINUITY TEST ----");


  if(CheckPyroContinuity(1))
    Serial.println("PYRO 1: OK");
  else{
    Serial.println("PYRO 1: OPEN");
    errorWarn();
    delay(2000);
    errorClear();
  }


  if(CheckPyroContinuity(2))
    Serial.println("PYRO 2: OK");
  else{
    Serial.println("PYRO 2: OPEN");
    errorWarn();
    delay(2000);
    errorClear();
  }


  if(CheckPyroContinuity(3))
    Serial.println("PYRO 3: OK");
  else{
    Serial.println("PYRO 3: OPEN");
    errorWarn();
    delay(2000);
    errorClear();
  }


  if(CheckPyroContinuity(4))
    Serial.println("PYRO 4: OK");
  else{
    Serial.println("PYRO 4: OPEN");
    errorWarn();
    delay(2000);
    errorClear();
  }
}

void CheckPyro() {
  Serial.println("STARTING PYROTECHNIC TESTS");
  delay(3000);
  if (pyroArmed == false){
    Serial.println("PYROTECHNIC IS NOT ARMED");
    errorWarn();
    delay(2000);
    errorClear();
    Serial.println("PYROTECHNIC IS NOT ARMED ARMING PYROS");
    ArmPyro();
    return;
  }
  firePyro(1); Serial.println("PYRO CHANNEL 1 IS HIGH MAKE SURE IGNITOR IS NOT CONNECTED");
  delay(3000);
  cutPyro(1);  Serial.println("PYRO CHANNEL 1 TEST IS OVER STARTING CHANNEL 2");
  delay(3000);
  firePyro(2); Serial.println("PYRO CHANNEL 2 IS HIGH MAKE SURE IGNITOR IS NOT CONNECTED");
  delay(3000);
  cutPyro(2);  Serial.println("PYRO CHANNEL 2 TEST IS OVER STARTING CHANNEL 3");
  delay(3000);
  firePyro(3); Serial.println("PYRO CHANNEL 3 IS HIGH MAKE SURE IGNITOR IS NOT CONNECTED");
  delay(3000);
  cutPyro(3);  Serial.println("PYRO CHANNEL 3 TEST IS OVER STARTING CHANNEL 4");
  delay(3000);
  firePyro(4); Serial.println("PYRO CHANNEL 4 IS HIGH MAKE SURE IGNITOR IS NOT CONNECTED");
  delay(3000);
  cutPyro(4);  Serial.println("PYRO CHANNEL 4 TEST IS OVER");
  Serial.println("PyroTechnic tests are completed");
}
void handleTest(){

    Serial.println("CURRENT STATE IS TESTING I AM BEGINNING THE TESTING PROCEDURE");
    currentState = stateTest;
    PyroContinuityTest();
    delay(3000);
    CheckPyro();
    delay(3000);
    CheckSensors();
    delay(3000);
    Serial.println("TEST IS FINISHED. PLEASE TURN OFF THE TEST SWITCH. TO TEST AGAIN PLEASE TURN IT BACK ON.");
    delay(5000);
    currentState = stateIdle;
  
}
void errorWarn(){
  digitalWrite(buzzerPin, HIGH);

}
void errorClear(){
  digitalWrite(buzzerPin, LOW);

}