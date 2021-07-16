
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
  gyroStatusStr = "...";
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
        gyroStatusStr = "Detecting...";
        
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Gyro BNO055 Not detected ... Check your wiring or I2C ADDR!");
        #endif
        gyroData.detected = 0;
        
        gyroStatus = GYRO_WAIT_MS;
        gyroNextStatus = GYRO_DETECTION;
        gyroTicksWait = 1000;
        gyroTickStatus = millis();
      }
      else
      {
        gyroStatusStr = "Detected...";
        
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Gyro BNO055 detected...");
        #endif
        gyroData.detected = 1;

        // Get sensor Type and details...
        bno.getSensor(&gyroSensor);
        
        // Update HPPT details...
        _GyroSensorDetailsHTML();
        
        gyroStatus = GYRO_DETECTED;
        gyroNConnec++;
      }
      break;

    case GYRO_DETECTED:

      // Check Calibration
      if (gyroData.calibrated == 1)
      {
        gyroStatusStr = "Loading...";
        
        // Write E2PORM calibration into sensor...      
        bno.setSensorOffsets(gyroCalVal);
        
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Valid BNO055 Calib stored on EERPOM -> Loading...");
        _GyroSensorOffsetsSerialDebug(gyroCalVal);
        
        Serial.println("Move sensor slightly to calibrate magnetometers");
        #endif
      }
      else
      {
        gyroStatusStr = "Not Calib...";
        
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Invalid BNO055 Calib stored on EERPOM: in Calibration...");
        #endif
      }

      // Crystal must be configured AFTER
      // loading calibration data into BNO055.
      bno.setExtCrystalUse(true);

      gyroStatus = GYRO_WAIT_MS;
      gyroNextStatus = GYRO_IN_CALIB;
      gyroTicksWait = 1000;
      gyroTickStatus = millis();
      break;

    case GYRO_IN_CALIB:
      
      bno.getEvent(&gyroEvent);

      if (!bno.isFullyCalibrated())
      {
        gyroStatusStr = "In Calib...";
        
        #if (_GYRO_SERIAL_DEBUG_ == 1)      
        Serial.print("In Cal -> X: ");
        Serial.print(gyroEvent.orientation.x, 4);
        Serial.print("\tY: ");
        Serial.print(gyroEvent.orientation.y, 4);
        Serial.print("\tZ: ");
        Serial.print(gyroEvent.orientation.z, 4);
 
        // Display calibration status
        _GyroSensorCalStatusSerialDebug();
        #endif
        
        // Wait the specified delay before requesting new data
        delay(GYRO_SAMPLERATE_DELAY_MS);
        /*
        gyroStatus = GYRO_WAIT_MS;
        gyroNextStatus = GYRO_IN_CALIB;
        gyroTicksWait = 500;
        gyroTickStatus = millis();
        */
      }
      else
      {
        gyroStatusStr = "Calib OK...";
        
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("\nFully calibrated!");
        Serial.println("--------------------------------");
        Serial.println("Calibration Results: ");     
        #endif

        bno.getSensorOffsets(gyroCalVal);
        #if (_GYRO_SERIAL_DEBUG_ == 1)
        _GyroSensorOffsetsSerialDebug(gyroCalVal);
        #endif

        EEPROM.write(EEPROM_ADD_GYRO_CAL, EEPROM_VAL_GYRO_CAL_OK);
        EEPROM.put(EERPOM_ADD_GYRO_VAL, gyroCalVal);

        EEPROM.commit();    //Store data to EEPROM
      
        gyroData.calibrated = 1;

        #if (_GYRO_SERIAL_DEBUG_ == 1)
        Serial.println("Data stored to EEPROM.");
        Serial.println("\n--------------------------------\n");
        #endif
        
        gyroStatus = GYRO_WAIT_MS;
        gyroNextStatus = GYRO_WORKING;
        gyroTicksWait = 500;
        gyroTickStatus = millis();
      }
      
      break;

    case GYRO_WORKING:

      gyroStatusStr = "Working...";
    
      bno.getEvent(&gyroEvent);

      // Calculus
      _GyroCalculus();
      
      #if (_GYRO_SERIAL_DEBUG_ == 1)
      // Display calibration status
      _GyroSensorCalStatusSerialDebug();

      // Display sensor status
      //_GyroSensorStatusSerialDebug();
      #endif

      // Wait the specified delay before requesting new data
      gyroStatus = GYRO_WAIT_MS;
      gyroNextStatus = GYRO_WORKING;
      gyroTicksWait = 100;
      gyroTickStatus = millis();
      break;

    case GYRO_WAIT_MS:
      if (millis() - gyroTickStatus >= gyroTicksWait)
        gyroStatus = gyroNextStatus;

      break;
  }
}

/**************************/
/* Gyro basic information */
/**************************/
void _GyroSensorDetailsHTML(void)
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

/*********************/
/* Gyro Calculations */
/*********************/
void _GyroCalculus (void)
{ 
  float gforce = 1.0;
  float ball = 1.0;

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

  //////////////////////
  // G-Force and ball //
  //////////////////////
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  gforce = acc.z();
  iGforce = round(gforce*10/9.8); 
  ball = acc.x();
  iBall = round(ball*100);

  #if (_GYRO_SERIAL_DEBUG_ == 1)

  Serial.print("gMag: ");
  Serial.print(gMag);
  Serial.print("\tsRoll: ");
  Serial.print(sRoll);
  Serial.print("\tsPitch: ");
  Serial.print(sPitch);
  Serial.print("\tiGforce: ");
  Serial.print(iGforce);
  Serial.print("\tiBall: ");
  Serial.print(iBall);
  
  #endif
}

/****************/
/* Serial Debug */
/****************/
#if (_GYRO_SERIAL_DEBUG_ == 1)
void _GyroSensorOffsetsSerialDebug(const adafruit_bno055_offsets_t &calibData)
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

void _GyroSensorStatusSerialDebug(void)
{
  bno.getSystemStatus(&system_status, &system_selftest, &system_error);
  
  Serial.println("");
  Serial.print("System Status: 0x");
  Serial.println(system_status, HEX);
  Serial.print("Self Test:     0x");
  Serial.println(system_selftest, HEX);
  Serial.print("System Error:  0x");
  Serial.println(system_error, HEX);
  Serial.println("");
}

void _GyroSensorCalStatusSerialDebug(void)
{
  bno.getCalibration(&sys, &gyro, &accel, &mag);
  
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
  Serial.println(mag, DEC);
}
#endif
