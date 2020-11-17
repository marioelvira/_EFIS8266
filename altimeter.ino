
//////////////////////
// Altimeter set up //
//////////////////////
void _AltimeterSetup(void)
{
  // Alt status
  altStatus = GYRO_DETECTION;

  altInfo = "";

  Altitude_m = 0;
}

/////////////////////////////
// Altimeter state machine //
/////////////////////////////
void _AltimeterLoop(void)
{
   switch (altStatus)
  {
    case ALT_DETECTION:
      if (!bme.begin())
      {
        #if (_ALT_SERIAL_DEBUG_ == 1)
        Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
        #endif
        
        altStatus = ALT_NOT_DETECTED;
      }
      else
      {
        #if (_ALT_SERIAL_DEBUG_ == 1)
        Serial.println("Alt BME280 detected...");
        #endif

        altStatus = ALT_DETECTED;
      }
      break;
      
    case ALT_DETECTED:
      altInfo = "Temp: </br>";
      bme_temp->getSensor(&altSensor);
      _AltSensorDetails();
      altInfo = altInfo + "Pressure: </br>";
      bme_pressure->getSensor(&altSensor);
      _AltSensorDetails();
      altInfo = altInfo + "Humidity: </br>";
      bme_humidity->getSensor(&altSensor);
      _AltSensorDetails();      
      
      altStatus = ALT_WORKING;
      break;
      
    case ALT_WORKING:

      // Porsia...
      if (bme.isReadingCalibration())
       break;

      bme_temp->getEvent(&temp_event);
      bme_pressure->getEvent(&pressure_event);
      bme_humidity->getEvent(&humidity_event);

      _FromQHN2Altitude();

      #if (_ALT_SERIAL_DEBUG_ == 1)
      Serial.print(F("Temperature = "));
      Serial.print(temp_event.temperature);
      Serial.println(" ºC");
    
      Serial.print(F("Humidity = "));
      Serial.print(humidity_event.relative_humidity);
      Serial.println(" %");
    
      Serial.print(F("Pressure = "));
      Serial.print(pressure_event.pressure);
      Serial.println(" hPa");
      #endif

      // Wait the specified delay before requesting new data
      delay(ALT_SAMPLERATE_DELAY_MS);
    
      break;
      
    case ALT_NOT_DETECTED:
      break;
  }
}

/*******************************/
/* Altimeter basic information */
/*******************************/
void _AltSensorDetails(void)
{
  altInfo = altInfo + "Sensor:     " + (String)altSensor.name + "</br>";
  altInfo = altInfo + "Driver Ver: " + (String)altSensor.version + "</br>";
  altInfo = altInfo + "Unique ID:  " + (String)altSensor.sensor_id + "</br>";
  altInfo = altInfo + "Max Value:  " + (String)altSensor.max_value + "</br>";
  altInfo = altInfo + "Min Value:  " + (String)altSensor.min_value + "</br>";
  altInfo = altInfo + "Resolution: " + (String)altSensor.resolution + "</br>";

  #if (_ALT_SERIAL_DEBUG_ == 1)
  Serial.println("------------------------------------");
  Serial.println(altInfo);
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
  #endif
}

void _FromQHN2Altitude (void)
{ 
  Altitude_m = (float)T0_DIV_L * (1.0 - pow(((float)(pressure_event.pressure)/((float) altData.QNH)), LR_DIV_Mg));

  if (units.alt == ALT_FEET)
    Altimeter = CONV_METERS_TO_FEET * Altitude_m;
  else
    Altimeter = Altitude_m;
}

void _FromAltitude2QNH (void)
{
  altData.QNH = ((float)pressure_event.pressure) / (pow(1.0 - (Altitude_m / T0_DIV_L), Mg_DIV_LR));
}
