void firePyro(int num){
  switch(num){
    case 1: digitalWrite(PyroChnl1, HIGH); pyroChnlState[1] = true; break;
    case 2: digitalWrite(PyroChnl2, HIGH); pyroChnlState[2] = true; break;
    case 3: digitalWrite(PyroChnl3, HIGH); pyroChnlState[3] = true; break;
    case 4: digitalWrite(PyroChnl4, HIGH); pyroChnlState[4] = true; break;
    default: break;
  }
}
void cutPyro(int num){
  switch(num){
    case 1: digitalWrite(PyroChnl1, LOW); pyroChnlState[1] = false; break;
    case 2: digitalWrite(PyroChnl2, LOW); pyroChnlState[2] = false; break;
    case 3: digitalWrite(PyroChnl3, LOW); pyroChnlState[3] = false; break;
    case 4: digitalWrite(PyroChnl4, LOW); pyroChnlState[4] = false; break;
    default: break;
  }
}
void checkPyroState(){
  if (pyroChnlState[1])      CurrPyroChnl = 1;
  else if (pyroChnlState[2]) CurrPyroChnl = 2;
  else if (pyroChnlState[3]) CurrPyroChnl = 3;
  else if (pyroChnlState[4]) CurrPyroChnl = 4;
  else                       CurrPyroChnl = 0;
}