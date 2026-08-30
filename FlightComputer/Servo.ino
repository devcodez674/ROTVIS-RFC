void WriteServos(float angle, uint8_t num){
  angle = constrain(angle, 70.0f, 110.0f);
  servoAngle[num] = static_cast<uint8_t>(angle);
  switch(num){
    case 0: servoFin1.write(angle);  break;
    case 1: servoFin2.write(angle);  break;
    case 2: servoFin3.write(angle);  break;
    case 3: servoFin4.write(angle);  break;
  }
}
