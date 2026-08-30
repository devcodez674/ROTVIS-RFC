void timeStart(){
  now = millis();
  if (startTime == 0) {
    startTime = millis();
  }
  unsigned long currentmicros = micros();

  dt = (currentmicros - prevMicros) / 1000000.0;
  prevMicros = currentmicros;
}

void runEvery(
    unsigned long &lastTime,
    unsigned long interval,
    void (*task)())
  {
    if (now - lastTime >= interval) {
        lastTime = now;
        task();
    }
}