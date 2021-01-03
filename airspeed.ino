
/////////////////////
// Airspeed set up //
/////////////////////
void _AirspeedSetup(void)
{
  airInfo = "";

  // TODO read form E2PROM
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
  float airSpeed_mps = 0;

  AirInArray[AirInPointer] = analogRead(PIN_AIR_IN);
  AirInPointer++;
  if (AirInPointer >= AIR_ARRAY_SIZE)
    AirInPointer = 0;

  // Calculamos la media del Array...
  for (int i = 0; i < AIR_ARRAY_SIZE; i++)
    airAcc = airAcc + AirInArray[i];
  
  AirInValue = airAcc/AIR_ARRAY_SIZE;

  AirInValueCorrected = AirInValue - airsData.digOffset;
  if (AirInValueCorrected < 0)
    AirInValueCorrected = 0;

  Air_mVolts = (float)AirInValueCorrected * (airsData.mVoltsEOS /(airsData.digEOS - airsData.digOffset));
  
  AirPressure = (Air_mVolts)*(AIR_SENS_M/AIR_SENS_R) + AIR_SENS_B;  // Pa

  // https://www.vcalc.com/wiki/vCalc/Air+Speed
  if (AirPressure <= 0)
    airSpeed_mps = 0;
  else 
    airSpeed_mps = (float) sqrt(2*(float)AirPressure/(float)AIR_DENSITY);   // m/s

  //if (airSpeed_mps < 20)
  //  airSpeed_mps = 0; 
  
  if (units.airspeed == AIRS_KNOTS)
    AirSpeed = (float)CONV_MPS_KNOTS * airSpeed_mps;
  else 
    AirSpeed = (float)CONV_MPS_KMH * airSpeed_mps;

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
  airInfo = airInfo + "Pa (range): " + (String)AIR_SENS_INFO_PA + "</br>";
  airInfo = airInfo + "V (range):  " + (String)AIR_SENS_INFO_V + "</br>";

  #if (_AIR_SERIAL_DEBUG_ == 1)
  Serial.println("------------------------------------");
  Serial.println(airInfo);
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
  #endif
}
