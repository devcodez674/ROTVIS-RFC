
void findBattVoltage(){
  battADC = analogRead(BATT_PIN);
  float adcVoltage = (battADC / 4095.0f) * 3.3f;
  estimatedData.BatteryVoltage = adcVoltage * BATT_DIV_RATIO;
}
