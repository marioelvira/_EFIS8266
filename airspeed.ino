
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

  AirInValueCorrected = AirInValue - AIR_DIG_OFFSET;
  if (AirInValueCorrected < 0)
    AirInValueCorrected = 0;

  Air_mVolts = (float)AirInValueCorrected * (AIR_MVOLTS_EOS /(AIR_DIG_EOS - AIR_DIG_OFFSET));
      
  AirPressure = ((Air_mVolts) / AIR_SENS_SENSIVITY * CONV_MMH2O_KPA);        // result in kPa

  //AirSpeed = (float)CONV_MPS_KNOTS * sqrt(2*(float)AirPressure/(float)AIR_DENSITY);
  AirSpeed = (float)CONV_MPS_KMH * sqrt(2*(float)(AirPressure*1000)/(float)AIR_DENSITY);

  // TODO
  if (AirSpeed < 20)
    AirSpeed = 0; 

  #if (_AIR_SERIAL_DEBUG_ == 1)
  AirCurrentTime = millis();
  if (AirCurrentTime - AirPreviousTime >= AIR_TICK)
  {
    Serial.print("AirInValue: ");
    Serial.print(AirInValue);
    Serial.print("AirInValueC: ");
    Serial.print(AirInValueCorrected);
    Serial.print("\t AirInVolts: ");
    Serial.print(Air_mVolts);
    Serial.print("\t AirPressure: ");
    Serial.print(AirPressure);
    Serial.print("\t AirSpeed: ");
    Serial.println(AirSpeed);
            
    AirPreviousTime = AirCurrentTime;
  }
  #endif
}
