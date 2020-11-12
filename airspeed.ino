
/////////////////////
// Airspeed set up //
/////////////////////
void _AirspeedSetup(void)
{
	
  // TODO read form E2PROM
  airInfo = "";
  
  airDigOffset = AIR_DIG_OFFSET;
  airDigEOS = AIR_DIG_EOS;
  airmVoltsEOS = AIR_MVOLTS_EOS;
  airSenSensivity = AIR_SENS_SENSIVITY;

  AirPressure = 0;  
  AirInValue = 0;

  for (int i = 0; i < AIR_ARRAY_SIZE; i++)
    AirInArray[i] = 0;

  AirInPointer = 0;
  
  _AirSensorDetails();
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

  AirInValueCorrected = AirInValue - airDigOffset;
  if (AirInValueCorrected < 0)
    AirInValueCorrected = 0;

  Air_mVolts = (float)AirInValueCorrected * (airmVoltsEOS /(airDigEOS - airDigOffset));
      
  AirPressure = ((Air_mVolts) / airSenSensivity * CONV_MMH2O_KPA);        // result in kPa

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

/******************************/
/* Airspeed basic information */
/******************************/
void _AirSensorDetails(void)
{
  airInfo =           "Sensor:     " + (String)AIR_SENS_INFO_TYPE + "</br>";
  airInfo = airInfo + "Max Value:  " + (String)AIR_SENS_INFO_MAX + "</br>";
  airInfo = airInfo + "Sensivity:  " + (String)AIR_SENS_INFO_SENSIVITY + "</br>";

  #if (_AIR_SERIAL_DEBUG_ == 1)
  Serial.println("------------------------------------");
  Serial.println(airInfo);
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
  #endif
}
