void stateSwitcher(){
  switch (currentState) {
    case stateCalibration:
      handleCalibration();
      break;
    case stateArmed:
      handleArmed();
      break;
    case stateAscent:
      handleAscent();
      break;
    case stateCoast:
      handleCoast();
      break;
    case stateApogee:
      handleApogee();
      break;
    case stateDescent:
      handleDescent();
      break;
    case stateLanded:
      handleLanded();
      break;
    case stateTest:
      if (Test == 1 ) {
        handleTest();
      }
      break;
    default:
      break;
  }
}
void handleArmed() {

  findBattVoltage();
  if (estimatedData.BatteryVoltage < 3.0f){
    currentState = stateIdle;
    errorWarn();
    delay(10000);
    errorClear();
  }
    runEvery(lastIMURead, 5, readIMU);
    // Launch detection — ay spike above 1.5g for at least 50ms
    if (currentState == stateArmed){
    updateEstimated();
    flightDetector();
    }
  


  runEvery(lastBaroRead, 10, readBaro);
  runEvery(lastLogTime, 10, updateLog);
}

// renamed from stateAscent() to handleAscent() to avoid conflict with enum value stateAscent
void handleAscent() {
  runEvery(lastIMURead, 5, readIMU);
  runEvery(lastBaroRead, 10, readBaro);
  runEvery(lastLogTime, 10, updateLog);
  runStability();
}

void handleCalibration() {
  runEvery(lastIMURead, 5, readIMU);
  runEvery(lastBaroRead, 10, readBaro);
}
void handleCoast(){
  runEvery(lastIMURead, 5, readIMU);
  runEvery(lastBaroRead, 10, readBaro);
  runEvery(lastLogTime, 10, updateLog);
  runStability();
  
}
void handleApogee() {
   if (parachuteCounter == 0)
        parachuteCounter = now;
      ArmPyro();
      firePyro(1);
      if (now - parachuteCounter >= 500){
        cutPyro(1);
      }
  currentState = stateDescent;
}
void handleDescent(){
  handleCoast();
  
}
void handleLanded(){
digitalWrite(buzzerPin, HIGH);

}
