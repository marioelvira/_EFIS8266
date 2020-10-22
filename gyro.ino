
/////////////////
// Gyro set up //
/////////////////
void _GyroSetup(void)
{
  // Gyro status
  gyroStatus = GYRO_DETECTION;

  gyroData.dataStored = 0;
  gyroData.detected = 0;
  gyroData.calibrated = 0;
}

////////////////////////
// Gyro state machine //
////////////////////////
void _GyroLoop()
{
  //sensors_event_t event;
    
  switch (gyroStatus)
  {
    case GYRO_DETECTION:
      // Initialise the sensor...
      if (!bno.begin())
      {
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.print("Gyro BNO055 Not detected ... Check your wiring or I2C ADDR!");
        #endif
        gyroData.detected = 0;
        gyroStatus = GYRO_NOT_DETECTED;
      }
      else
      {
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Gyro BNO055 detected...");
        #endif
        gyroData.detected = 1;
        gyroStatus = GYRO_DETECTED;
      }
      break;

    case GYRO_DETECTED:

      // Check Calibration
      if (gyroData.dataStored == 1)
      {
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        _GryoSensorOffsets(gyroCalVal);
        #endif

        // Write E2PORM data on sensor...        
        bno.setSensorOffsets(gyroCalVal);

        gyroStatus = GYRO_IN_CALIBRATION;
      }
      else       
        gyroStatus = GYRO_NOT_CALIBRATED;

      // Get sensor details
      _GryoSensorDetails();

      // Get sensor current status
      _GryoSensorStatus();

      // Crystal must be configured AFTER
      // loading calibration data into BNO055.
      bno.setExtCrystalUse(true);
      
      break;
      
    case GYRO_IN_CALIBRATION:

      bno.getEvent(&event);
      
      #if (_GYRO_SERIAL_DEBUG_ == 1)
      Serial.println("Move sensor slightly to calibrate magnetometers");
      #endif
      
      if (!bno.isFullyCalibrated())
      {
        delay(GYRO_SAMPLERATE_DELAY_MS);
      }
      else
        gyroStatus = GYRO_CALIBRATED;
      
      break;

    case GYRO_NOT_CALIBRATED:
      
      bno.getEvent(&event);

      if (!bno.isFullyCalibrated())
      {
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.print("X: ");
        Serial.print(event.orientation.x, 4);
        Serial.print("\tY: ");
        Serial.print(event.orientation.y, 4);
        Serial.print("\tZ: ");
        Serial.print(event.orientation.z, 4);
        #endif
        
        // Display calibration status
        _GryoSensorCalStatus();

        #if (_GYRO_SERIAL_DEBUG_ == 1)
        // New line for the next sample
        Serial.println("");
        #endif

        // Wait the specified delay before requesting new data
        delay(GYRO_SAMPLERATE_DELAY_MS);
      }
      else
       gyroStatus = GYRO_CALIBRATED;
      
      break;

    case GYRO_CALIBRATED:

      #if (_GYRO_SERIAL_DEBUG_ == 1)
      Serial.println("\nFully calibrated!");
      Serial.println("--------------------------------");
      Serial.println("Calibration Results: ");     
      #endif

      bno.getSensorOffsets(gyroCalValNew);
      #if (_GYRO_SERIAL_DEBUG_ == 1)
      _GryoSensorOffsets(gyroCalValNew);
      #endif

      EEPROM.write(EEPROM_ADD_GYRO_CAL, EEPROM_VAL_GYRO_CAL_OK);
      EEPROM.put(EERPOM_ADD_GYRO_VAL, gyroCalValNew);

      #if (_GYRO_SERIAL_DEBUG_ == 1)
      Serial.println("Data stored to EEPROM.");
      Serial.println("\n--------------------------------\n");
      #endif
      
      delay(500);

      gyroStatus = GYRO_CONNECTED;
     
      break;

    case GYRO_CONNECTED:
      bno.getEvent(&event);

      #if (_GYRO_SERIAL_DEBUG_ == 1)
      Serial.print("X: ");
      Serial.print(event.orientation.x, 4);
      Serial.print("\tY: ");
      Serial.print(event.orientation.y, 4);
      Serial.print("\tZ: ");
      Serial.print(event.orientation.z, 4);
      #endif
        
      // Display calibration status
      _GryoSensorCalStatus();

      // Optional: Display sensor status (debug only)
      _GryoSensorStatus();

      #if (_GYRO_SERIAL_DEBUG_ == 1)
      // New line for the next sample
      Serial.println("");
      #endif

      // Wait the specified delay before requesting new data
      delay(GYRO_SAMPLERATE_DELAY_MS);
          
      break;

    case GYRO_NOT_DETECTED:
      break;
  }
}

/**************************/
/* Gyro basic information */
/**************************/
void _GryoSensorDetails(void)
{
    bno.getSensor(&gyroSensor);

    #if (_GYRO_SERIAL_DEBUG_ == 1)
    Serial.println("------------------------------------");
    Serial.print("Sensor:       "); Serial.println(gyroSensor.name);
    Serial.print("Driver Ver:   "); Serial.println(gyroSensor.version);
    Serial.print("Unique ID:    "); Serial.println(gyroSensor.sensor_id);
    Serial.print("Max Value:    "); Serial.print  (gyroSensor.max_value);  Serial.println(" xxx");
    Serial.print("Min Value:    "); Serial.print  (gyroSensor.min_value);  Serial.println(" xxx");
    Serial.print("Resolution:   "); Serial.print  (gyroSensor.resolution); Serial.println(" xxx");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
    #endif
}

/***********************/
/* Basic Sensor status */
/***********************/
void _GryoSensorStatus(void)
{
    // Get the system status values (mostly for debugging purposes)
    //uint8_t system_status, self_test_results, system_error;
    system_status = self_test_results = system_error = 0;
    bno.getSystemStatus(&system_status, &self_test_results, &system_error);

    #if (_GYRO_SERIAL_DEBUG_ == 1)
    Serial.println("");
    Serial.print("System Status: 0x");
    Serial.println(system_status, HEX);
    Serial.print("Self Test:     0x");
    Serial.println(self_test_results, HEX);
    Serial.print("System Error:  0x");
    Serial.println(system_error, HEX);
    Serial.println("");
    delay(500);
    #endif
}

/*****************************/
/* Sensor calibration status */
/*****************************/
void _GryoSensorCalStatus(void)
{
    // Get the four calibration values (0..3)
    // Any sensor data reporting 0 should be ignored,
    // 3 means 'fully calibrated"
    //uint8_t sys, gyro, accel, mag;
    sys = gyro = accel = mag = 0;
        
    bno.getCalibration(&sys, &gyro, &accel, &mag);

    #if (_GYRO_SERIAL_DEBUG_ == 1)
    // The data should be ignored until the system calibration is > 0
    Serial.print("\t");
    if (!sys)
    {
        Serial.print("! ");
    }

    Serial.print("Sys:");
    Serial.print(sys, DEC);
    Serial.print(" G:");
    Serial.print(gyro, DEC);
    Serial.print(" A:");
    Serial.print(accel, DEC);
    Serial.print(" M:");
    Serial.print(mag, DEC);
    #endif
}

/******************************************/
/* Raw calibration offset and radius data */
/******************************************/
#if (_GYRO_SERIAL_DEBUG_ == 1)
void _GryoSensorOffsets(const adafruit_bno055_offsets_t &calibData)
{
    #if (_GYRO_SERIAL_DEBUG_ == 1)
    Serial.print("Accelerometer: ");
    Serial.print(calibData.accel_offset_x); Serial.print(" ");
    Serial.print(calibData.accel_offset_y); Serial.print(" ");
    Serial.print(calibData.accel_offset_z); Serial.print(" ");

    Serial.print("\nGyro: ");
    Serial.print(calibData.gyro_offset_x); Serial.print(" ");
    Serial.print(calibData.gyro_offset_y); Serial.print(" ");
    Serial.print(calibData.gyro_offset_z); Serial.print(" ");

    Serial.print("\nMag: ");
    Serial.print(calibData.mag_offset_x); Serial.print(" ");
    Serial.print(calibData.mag_offset_y); Serial.print(" ");
    Serial.print(calibData.mag_offset_z); Serial.print(" ");

    Serial.print("\nAccel Radius: ");
    Serial.print(calibData.accel_radius);

    Serial.print("\nMag Radius: ");
    Serial.print(calibData.mag_radius);
    #endif
}
#endif
