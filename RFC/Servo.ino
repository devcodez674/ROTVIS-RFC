void WriteServos(int angle, int num){
  angle = constrain(angle, 70, 110);
  servoAngle[num] = angle;
  switch(num){
    case 0: servoFin1.write(angle);  break;
    case 1: servoFin2.write(angle);  break;
    case 2: servoFin3.write(angle);  break;
    case 3: servoFin4.write(angle);  break;
  }
}
