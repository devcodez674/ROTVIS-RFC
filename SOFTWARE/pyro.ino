void firePyro(uint8_t num){
   if(!pyroArmed) {

    Serial.println("PYRO BLOCKED - NOT ARMED");
    return;
  }
  switch(num){
    case 1: digitalWrite(PyroChnl1, HIGH); pyroChnlState[1] = true; break;
    case 2: digitalWrite(PyroChnl2, HIGH); pyroChnlState[2] = true; break;
    case 3: digitalWrite(PyroChnl3, HIGH); pyroChnlState[3] = true; break;
    case 4: digitalWrite(PyroChnl4, HIGH); pyroChnlState[4] = true; break;
    default: break;
  }
}
void cutPyro(uint8_t num){
  switch(num){
    case 1: digitalWrite(PyroChnl1, LOW); pyroChnlState[1] = false; break;
    case 2: digitalWrite(PyroChnl2, LOW); pyroChnlState[2] = false; break;
    case 3: digitalWrite(PyroChnl3, LOW); pyroChnlState[3] = false; break;
    case 4: digitalWrite(PyroChnl4, LOW); pyroChnlState[4] = false; break;
    default: break;
  }
}
void ArmPyro() {

  pyroArmed = true;

  Serial.println("PYRO SYSTEM ARMED");
}
void DisarmPyro() {

  pyroArmed = false;

  // kill all outputs
  digitalWrite(PyroChnl1, LOW);
  digitalWrite(PyroChnl2, LOW);
  digitalWrite(PyroChnl3, LOW);
  digitalWrite(PyroChnl4, LOW);

  Serial.println("PYRO SYSTEM SAFE");
}

bool CheckPyroContinuity(uint8_t channel) {

  switch(channel) {

    case 1:
      return digitalRead(PyroCont1);

    case 2:
      return digitalRead(PyroCont2);

    case 3:
      return digitalRead(PyroCont3);

    case 4:
      return digitalRead(PyroCont4);
  }

  return false;
}

void checkPyroState(){
  if (pyroChnlState[1])      CurrPyroChnl = 1;
  else if (pyroChnlState[2]) CurrPyroChnl = 2;
  else if (pyroChnlState[3]) CurrPyroChnl = 3;
  else if (pyroChnlState[4]) CurrPyroChnl = 4;
  else                       CurrPyroChnl = 0;
}