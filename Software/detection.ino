void flightDetector(){
      if (imuData.ay >= 1.50f) {
      if (launchStart == 0)
        launchStart = now;
      if (now - launchStart >= 50 && currentState == stateArmed) {
        Serial.println("Launch detected!");
        currentState = stateAscent;
      }
    } else {
      launchStart = 0;
    }
}
void apogeeDetector(){
  if (currentState == stateAscent || currentState == stateCoast){
    if(estimatedData.verticalVelocity < -1.0f && estimatedData.altitude >= 1.50f )
    {
        apogeeCounter++;

        if(apogeeCounter > 10)
        {
            Serial.println("Apogee detected!");
            currentState = stateApogee;
        }
    }
    else
    {
        apogeeCounter = 0;
    }
  }
}
void coastDetector(){
  if(accelMagnitude < 0.5f && estimatedData.altitude >= 1.50f && currentState == stateAscent)
  {
    coastCounter++;
    if(coastCounter > 10)
    {
      Serial.println("Coast detected!");
      currentState = stateCoast;
    }
  }
  else
  {
    coastCounter = 0;
  }
}
void landingDetector(){
   if (landingCounter == 0)
        landingCounter = now;
      if (now - landingCounter >= 50 && estimatedData.altitude < 1.50f && currentState == stateDescent && accelMagnitude < 1.0f)
        {
        currentState = stateLanded;
        }
      else
      {
        landingCounter = 0;
      }
}
void runDetectors(){
  flightDetector();
  apogeeDetector();
  coastDetector();
  landingDetector();
}