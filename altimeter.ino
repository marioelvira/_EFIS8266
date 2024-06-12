
//////////////////////
// Altimeter set up //
//////////////////////
void _AltimeterSetup(void)
{
  // Alt status
  altStatus = GYRO_DETECTION;
  altNConnec = 0;

  altInfo = "";
  altStatusStr = "...";

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

      if (! bme.begin(BNE_I2C_ADDRESS, &Wire))
      //if (!bme.begin())
      {
        altStatusStr = "Detecting...";
        
        #if (_ALT_SERIAL_DEBUG_ == 1)
        Serial.println("Alt BME280 Not detected ... Check your wiring or I2C ADDR!");
        #endif

        altStatus = ALT_WAIT_MS;
        altNextStatus = ALT_DETECTION;
        altTicksWait = 1000;
        altTickStatus = millis();
      }
      else
      {
        altStatusStr = "Detected...";
        
        #if (_ALT_SERIAL_DEBUG_ == 1)
        Serial.println("Alt BME280 detected...");
        Serial.println("normal mode, 16x pressure / 2x temperature / 1x humidity oversampling,");
        Serial.println("0.5ms standby period, filter 16x");
        #endif
    
        bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X2,  // temperature
                        Adafruit_BME280::SAMPLING_X16, // pressure
                        Adafruit_BME280::SAMPLING_X1,  // humidity
                        Adafruit_BME280::FILTER_X16,
                        Adafruit_BME280::STANDBY_MS_0_5 );

        altStatus = ALT_DETECTED;
        altNConnec++;
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

      altStatusStr = "Working??...";

      // Porsia...
      if (bme.isReadingCalibration())
       break;

      altStatusStr = "Working...";

      delay(50); // 50 ms ??
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
      altStatus = ALT_WAIT_MS;
      altNextStatus = ALT_WORKING;
      altTicksWait = 100;
      altTickStatus = millis();
    
      break;
      
    case ALT_WAIT_MS:
      if (millis() - altTickStatus >= altTicksWait)
        altStatus = altNextStatus;
         
      break;
  }
}

/*******************************/
/* Altimeter basic information */
/*******************************/
void _AltSensorDetails(void)
{
  altInfo = altInfo + "Sensor:      " + (String)altSensor.name + "</br>";
  altInfo = altInfo + "Connections: " + (String)altNConnec + "</br>";
  altInfo = altInfo + "Driver Ver:  " + (String)altSensor.version + "</br>";
  altInfo = altInfo + "Unique ID:   " + (String)altSensor.sensor_id + "</br>";
  altInfo = altInfo + "Max Value:   " + (String)altSensor.max_value + "</br>";
  altInfo = altInfo + "Min Value:   " + (String)altSensor.min_value + "</br>";
  altInfo = altInfo + "Resolution:  " + (String)altSensor.resolution + "</br>";

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
  if (pressure_event.pressure > 0)
    Altitude_m = (float)T0_DIV_L * (1.0 - pow(((float)(pressure_event.pressure)/((float) altData.QNH)), LR_DIV_Mg));
  else
    Altitude_m = 0;

  if (units.alt == ALT_FEET)
    Altimeter = CONV_METERS_TO_FEET * Altitude_m;
  else
    Altimeter = Altitude_m;
}

void _FromAltitude2QNH (void)
{
  altData.QNH = ((float)pressure_event.pressure) / (pow(1.0 - (Altitude_m / T0_DIV_L), Mg_DIV_LR));
}
