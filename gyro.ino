
/////////////////
// Gyro set up //
/////////////////
void _GyroSetup(void)
{
  // Gyro status
  gyroStatus = GYRO_DETECTION;
  gyroNConnec = 0;

  gyroData.detected = 0;
  //gyroData.calibrated = 0; // Read from E2PROM

  gyroInfo = "";
}

////////////////////////
// Gyro state machine //
////////////////////////
void _GyroLoop()
{
   
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
        gyroTickReconnect = millis();
      }
      else
      {
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Gyro BNO055 detected...");
        #endif
        gyroData.detected = 1;
        gyroStatus = GYRO_DETECTED;
        gyroNConnec++;
      }
      break;

    case GYRO_DETECTED:

      // Get sensor Type and details...
      bno.getSensor(&gyroSensor);
      _GyroSensorDetails();

      // Check Calibration
      if (gyroData.calibrated == 1)
      {  
        // Write E2PORM data loaded on gyroCalVal into sensor...      
        bno.setSensorOffsets(gyroCalVal);
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Gyro BNO055 Calibrated...");
        _GyroSensorOffsets(gyroCalVal);
        #endif

        gyroStatus = GYRO_WORKING;
      }
      else
      {
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Gyro BNO055 in Calibration...");
        #endif    
        gyroStatus = GYRO_IN_CALIBRATION;
      }

      // Crystal must be configured AFTER
      // loading calibration data into BNO055.
      bno.setExtCrystalUse(true);         // TODO Check 
      
      break;
      
    case GYRO_IN_CALIBRATION:
      
      bno.getEvent(&gyroEvent);

      #if (_GYRO_SERIAL_DEBUG_ == 1)
      Serial.print("Cal -> ");
      #endif

      if (!bno.isFullyCalibrated())
      {
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.print("X: ");
        Serial.print(gyroEvent.orientation.x, 4);
        Serial.print("\tY: ");
        Serial.print(gyroEvent.orientation.y, 4);
        Serial.print("\tZ: ");
        Serial.print(gyroEvent.orientation.z, 4);
        #endif
               
        // Display calibration status
        bno.getCalibration(&sys, &gyro, &accel, &mag);
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        _GyroSensorCalStatus();
        #endif
        
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

      bno.getSensorOffsets(gyroCalVal);
      #if (_GYRO_SERIAL_DEBUG_ == 1)
      _GyroSensorOffsets(gyroCalVal);
      #endif

      EEPROM.write(EEPROM_ADD_GYRO_CAL, EEPROM_VAL_GYRO_CAL_OK);
      EEPROM.put(EERPOM_ADD_GYRO_VAL, gyroCalVal);

      EEPROM.commit();    //Store data to EEPROM
      
      gyroData.calibrated = 1;

      #if (_GYRO_SERIAL_DEBUG_ == 1)
      Serial.println("Data stored to EEPROM.");
      Serial.println("\n--------------------------------\n");
      #endif
      
      delay(500);

      gyroStatus = GYRO_WORKING;
     
      break;

    case GYRO_WORKING:
      bno.getEvent(&gyroEvent);

      #if (_GYRO_SERIAL_DEBUG_ == 1)
      Serial.print("X: ");
      Serial.print(gyroEvent.orientation.x, 4);
      Serial.print("\tY: ");
      Serial.print(gyroEvent.orientation.y, 4);
      Serial.print("\tZ: ");
      Serial.print(gyroEvent.orientation.z, 4);
      #endif
        
      // Display calibration status
      bno.getCalibration(&sys, &gyro, &accel, &mag);
      #if (_GYRO_SERIAL_DEBUG_ == 1)
      _GyroSensorCalStatus();
      #endif

      // Display sensor status
      bno.getSystemStatus(&system_status, &system_selftest, &system_error);
      #if (_GYRO_SERIAL_DEBUG_ == 1)
      _GyroSensorStatus();
      #endif

      // Calculus
      _GyroCalculus();
      
      #if (_GYRO_SERIAL_DEBUG_ == 1)
      // New line for the next sample
      Serial.println("");
      #endif

      // Wait the specified delay before requesting new data
      delay(GYRO_SAMPLERATE_DELAY_MS);
          
      break;

    case GYRO_NOT_DETECTED:
      if (millis() - gyroTickReconnect >= 1000)
        gyroStatus = GYRO_DETECTION;

      break;
  }
}

/**************************/
/* Gyro basic information */
/**************************/
void _GyroSensorDetails(void)
{
  gyroInfo =            "Sensor:      " + (String)gyroSensor.name + "</br>";
  gyroInfo = gyroInfo + "Connections: " + (String)gyroNConnec + "</br>";
  gyroInfo = gyroInfo + "Driver Ver:  " + (String)gyroSensor.version + "</br>";
  gyroInfo = gyroInfo + "Unique ID:   " + (String)gyroSensor.sensor_id + "</br>";
  gyroInfo = gyroInfo + "Max Value:   " + (String)gyroSensor.max_value + "</br>";
  gyroInfo = gyroInfo + "Min Value:   " + (String)gyroSensor.min_value + "</br>";
  gyroInfo = gyroInfo + "Resolution:  " + (String)gyroSensor.resolution + "</br>";

  #if (_GYRO_SERIAL_DEBUG_ == 1)
  Serial.println("------------------------------------");
  Serial.println(gyroInfo);
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
  #endif
}

#if (_GYRO_SERIAL_DEBUG_ == 1)
/******************************************/
/* Raw calibration offset and radius data */
/******************************************/
void _GyroSensorOffsets(const adafruit_bno055_offsets_t &calibData)
{
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
}

/***********************/
/* Basic Sensor status */
/***********************/
void _GyroSensorStatus(void)
{
    Serial.println("");
    Serial.print("System Status: 0x");
    Serial.println(system_status, HEX);
    Serial.print("Self Test:     0x");
    Serial.println(system_selftest, HEX);
    Serial.print("System Error:  0x");
    Serial.println(system_error, HEX);
    Serial.println("");
    delay(500);
}

/*****************************/
/* Sensor calibration status */
/*****************************/
void _GyroSensorCalStatus(void)
{
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
}
#endif

void _GyroCalculus (void)
{ 
  float Gforce = 1.0;

  gMag = gyroEvent.orientation.x + 0.5;
  
  if (gyroEvent.orientation.y >= 0)
    gRoll = gyroEvent.orientation.y + 0.5;
  else
    gRoll = gyroEvent.orientation.y - 0.5;
    
  if (gyroEvent.orientation.z >= 0)
    gPitch = gyroEvent.orientation.z + 0.5;
  else
    gPitch = gyroEvent.orientation.z - 0.5;

  // Pitch
  if (abs(gPitch) > 90)
  {
    if (gRoll > 0)
      gRoll = 180 - gRoll;
    else
      gRoll = -180 - gRoll;
  }

  if (gPitch > 90)
    gPitch = 180 - gPitch;

  if (gPitch < -90)
    gPitch = -180 - gPitch;

  // Roll
  sRoll = "";
  if (abs(gRoll) < 10)
    sRoll += " ";  
    
  sRoll += abs(gRoll);
  
  if (gRoll < 0)
    sRoll += "R";  
  
  if (gRoll > 0)  
    sRoll += "L";

  // Pitch  
  sPitch = "";
  if (abs(gPitch) < 10)
    sPitch += " ";
    
  sPitch += abs(gPitch);
  
  if (gPitch < 0)  
    sPitch += "U";  
  
  if (gPitch > 0)  
    sPitch += "D";

  ///////////////////
  // G-Force meter //
  ///////////////////
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  Gforce = acc.z();
  iGforce = round(Gforce*10/9.8);
}
