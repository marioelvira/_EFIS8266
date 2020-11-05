
/////////////////////
// Airspeed set up //
/////////////////////
void _AirspeedSetup(void)
{
  AirPressure = 0;  
  AirInValue = 0;

  for (int i = 0; i < AIR_ARRAY_SIZE; i++)
    AirInArray[i] = 0;

  AirInPointer = 0;
}

////////////////////////////
// Airspeed state machine //
////////////////////////////
void _AirspeedLoop(void)
{
  int airAcc = 0;

  AirInArray[AirInPointer] = analogRead(PIN_AIR_IN);
  AirInPointer++;
  if (AirInPointer >= AIR_ARRAY_SIZE)
    AirInPointer = 0;

  // Calculamos la media del Array...
  for (int i = 0; i < AIR_ARRAY_SIZE; i++)
    airAcc = airAcc + AirInArray[i];
  
  AirInValue = airAcc/AIR_ARRAY_SIZE;

  AirPressure = map(AirInValue,
                   (int)AIR_SENSOR_IN_SHIFT,
                   (int)AIR_SENSOR_IN_MAX,
                   (int)AIR_SENSOR_PA_MIN,
                   (int)AIR_SENSOR_PA_MAX);
 
  if (AirPressure < 0)
    AirPressure = 0;

  IAirSpeed = (float)CONV_MPS_KNOTS * sqrt(2*(float)AirPressure/(float)AIR_DENSITY);

  // TODO
  //if (IAirSpeed < 20)
  //  IAirSpeed = 0; 

  #if (_AIR_SERIAL_DEBUG_ == 1)
  AirCurrentTime = millis();
  if (AirCurrentTime - AirPreviousTime >= AIR_TICK)
  {
    Serial.print("AirInValue: ");
    Serial.print(AirInValue);
    Serial.print("\t AirPressure: ");
    Serial.print(AirPressure);
    Serial.print("\t IAirSpeed: ");
    Serial.println(IAirSpeed);
            
    AirPreviousTime = AirCurrentTime;
  }
  #endif
}
