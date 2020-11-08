
//////////////////////
// Altimeter set up //
//////////////////////
void _AltimeterSetup(void)
{
  // Alt status
  altStatus = GYRO_DETECTION;

  altInfo = "";
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
      #if (_ALT_SERIAL_DEBUG_ == 1)
      bme_temp->printSensorDetails();
      bme_pressure->printSensorDetails();
      bme_humidity->printSensorDetails();
      #endif
      altStatus = ALT_WORKING;
      break;
      
    case ALT_WORKING:
      
      bme_temp->getEvent(&temp_event);
      bme_pressure->getEvent(&pressure_event);
      bme_humidity->getEvent(&humidity_event);

      #if (_ALT_SERIAL_DEBUG_ == 1)
      Serial.print(F("Temperature = "));
      Serial.print(temp_event.temperature);
      Serial.println(" *C");
    
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
