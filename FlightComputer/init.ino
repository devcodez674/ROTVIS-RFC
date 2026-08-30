void initSensors(){
    while (!IMU.begin()) {
    Serial.println("IMU communication has not been established");
    delay(1000);
  }

  while (!BARO.begin_SPI(baroCsPin)) {
    Serial.println("Barometer communication has not been established");
    delay(1000);
  }
  BARO.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  BARO.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  BARO.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);

}
void PyroInit() {

  pinMode(PyroChnl1, OUTPUT);
  pinMode(PyroChnl2, OUTPUT);
  pinMode(PyroChnl3, OUTPUT);
  pinMode(PyroChnl4, OUTPUT);

  // Always start safe
  digitalWrite(PyroChnl1, LOW);
  digitalWrite(PyroChnl2, LOW);
  digitalWrite(PyroChnl3, LOW);
  digitalWrite(PyroChnl4, LOW);


  pinMode(PyroCont1, INPUT);
  pinMode(PyroCont2, INPUT);
  pinMode(PyroCont3, INPUT);
  pinMode(PyroCont4, INPUT);
}
void initActuators(){
  PyroInit();
  // Servo attaches
  servoFin1.attach(FinServo1);
  servoFin2.attach(FinServo2);
  servoFin3.attach(FinServo3);
  servoFin4.attach(FinServo4);

}
void initPins(){
  pinMode(armPin, INPUT); // ARM switch
  pinMode(testPin, INPUT); // Test switch
  pinMode(BATT_PIN, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);


}

void initialize(){
  Serial.begin(115200);          // Debug / monitor
  initSensors();
  initActuators();
  initPins();
  initFlash();
  currentState = stateCalibration;
  pressureCalib();
}
