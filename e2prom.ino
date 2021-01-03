
void _ConfigSetup(void)
{
  #if (_READ_EEPROM_ == 1)
  _ReadEEPROM();
  delay(1000);
  #endif
    
  // Config setup
  #if (_ERASE_EEPROM_ == 1)
  _ResetEEPROM();
  delay(1000);
  #endif

  // Read config from EEPROM
  _readCONFIG();

  #if (_READ_EEPROM_ == 1)
  delay(1000);
  _ReadEEPROM();
  #endif

  resetConfig = 0;
}

void _ConfigLoop(void)
{
   
  if (resetConfig == 1)
  {
    resetConfig = 0;
    _ResetEEPROM();
    delay(1000);
  }
}

void _readCONFIG (void)
{
  int i;
  #if (_WRITE_SSID_EEPROM_ == 1)
  int j;
  #endif
  byte val[4];
  
  EEPROM.begin(EEPROM_SIZE);
    
  i = EEPROM.read(EEPROM_ADD_OK);
  
  // Si NO esta grabada la configuracion...
  if (i != EEPROM_VAL_OK)
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("00 - EPROM Config NOK");
    #endif
   
    EEPROM.write(EEPROM_ADD_OK,      EEPROM_VAL_OK);
   
    // IP Mode
    EEPROM.write(EEPROM_ADD_IP_MODE, EEPROM_VAL_IP_MODE);
    EEPROM.write(EEPROM_ADD_IP1,     EEPROM_VAL_IP1);
    EEPROM.write(EEPROM_ADD_IP2,     EEPROM_VAL_IP2);
    EEPROM.write(EEPROM_ADD_IP3,     EEPROM_VAL_IP3);
    EEPROM.write(EEPROM_ADD_IP4,     EEPROM_VAL_IP4);
    EEPROM.write(EEPROM_ADD_MASK1,   EEPROM_VAL_MASK1);
    EEPROM.write(EEPROM_ADD_MASK2,   EEPROM_VAL_MASK2);
    EEPROM.write(EEPROM_ADD_MASK3,   EEPROM_VAL_MASK3);
    EEPROM.write(EEPROM_ADD_MASK4,   EEPROM_VAL_MASK4);
    EEPROM.write(EEPROM_ADD_GATE1,   EEPROM_VAL_GATE1);
    EEPROM.write(EEPROM_ADD_GATE2,   EEPROM_VAL_GATE2);
    EEPROM.write(EEPROM_ADD_GATE3,   EEPROM_VAL_GATE3);
    EEPROM.write(EEPROM_ADD_GATE4,   EEPROM_VAL_GATE4);

    // Wi-Fi
    EEPROM.write(EEPROM_ADD_WIFI_MODE, EEPROM_VAL_WIFI_MODE);
  
    for (i = 0; i < WIFI_SSID_MAX; i++)
      EEPROM.write(EEPROM_ADD_WIFI_SSID + i, 0);

    #if (_WRITE_SSID_EEPROM_ == 1)
    j = strlen(ssidSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_WIFI_SSID + i, ssidSt[i]);
    #endif

    for (i = 0; i < WIFI_PSWD_MAX; i++)
      EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, 0);

    #if (_WRITE_SSID_EEPROM_ == 1)
    j = strlen(passwordSt);
    for (i = 0; i < j; i++)
      EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, passwordSt[i]);
    #endif
    
    // Gyro
    EEPROM.write(EEPROM_ADD_GYRO_CAL, EEPROM_VAL_NOT_CAL);
    for (i = 0; i < EEPROM_GYRO_MAX; i++)
      EEPROM.write(EERPOM_ADD_GYRO_VAL + i, 0);

    // Airspeed
    airsData.digOffset = AIR_DIG_OFFSET;
    airsData.digEOS = AIR_DIG_EOS;
    airsData.mVoltsEOS = AIR_MVOLTS_EOS;
    airsData.senSensivity = 0;
    EEPROM.put(EERPOM_ADD_AIRS_VAL, airsData);
	
	  // Altimeter
	  altData.QNH = QNH_ISA;
	  EEPROM.put(EERPOM_ADD_ALT_VAL, altData);

	  // Units
	  units.alt = ALT_FEET;
    units.airspeed = AIRS_KMH;
    units.vario = VARIO_FEETpS;
    units.temp = TEMP_CELSIUS;
	  EEPROM.put(EERPOM_ADD_UNITS_VAL, units);

    EEPROM.commit();    //Store data to EEPROM
  }
  else
  {
    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.println("00 - EPROM Config OK");
    #endif
  }


  // IP Mode
  ipMode = EEPROM.read(EEPROM_ADD_IP_MODE);
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("01 - EPROM IP Mode: ");
  Serial.print(ipMode);
  if (ipMode == FIXIP_MODE)
    Serial.println(" FIX IP");   
  else
    Serial.println(" DHCP");
  #endif
  
  if (ipMode == FIXIP_MODE)
  {
    // Ip Address
    val[0] = EEPROM.read(EEPROM_ADD_IP1);
    val[1] = EEPROM.read(EEPROM_ADD_IP2);
    val[2] = EEPROM.read(EEPROM_ADD_IP3);
    val[3] = EEPROM.read(EEPROM_ADD_IP4);
    ipAddress = IPAddress(val[0], val[1], val[2], val[3]);
    
    // Mask
    val[0] = EEPROM.read(EEPROM_ADD_MASK1);
    val[1] = EEPROM.read(EEPROM_ADD_MASK2);
    val[2] = EEPROM.read(EEPROM_ADD_MASK3);
    val[3] = EEPROM.read(EEPROM_ADD_MASK4);
    netMask = IPAddress(val[0], val[1], val[2], val[3]);

    // Gateway
    val[0] = EEPROM.read(EEPROM_ADD_GATE1);
    val[1] = EEPROM.read(EEPROM_ADD_GATE2);
    val[2] = EEPROM.read(EEPROM_ADD_GATE3);
    val[3] = EEPROM.read(EEPROM_ADD_GATE4);
    gateWay = IPAddress(val[0], val[1], val[2], val[3]);
  }

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("IP: ");
  Serial.print(ipAddress);
  Serial.print(" Mask: ");
  Serial.print(netMask);
  Serial.print(" Gateway: ");
  Serial.println(gateWay);
  #endif
  
  // Wi-Fi Mode
  wifiMode = EEPROM.read(EEPROM_ADD_WIFI_MODE);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("02 - EPROM Wi-Fi Mode: ");
  if (wifiMode == STATION_MODE)
    Serial.println("Station");
  else
    Serial.println("Access point");
  #endif

  if (wifiMode == STATION_MODE)
  {
    for (i = 0; i < WIFI_SSID_MAX; i++)
      ssid[i] = char(EEPROM.read(EEPROM_ADD_WIFI_SSID + i));

    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.print("SSID: ");
    Serial.println(ssid);
    #endif

    for (i = 0; i < WIFI_SSID_MAX; i++)
      password[i] = char(EEPROM.read(EEPROM_ADD_WIFI_PSWD + i));

    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    Serial.print("PASSWORD: ");
    Serial.println(password);
    #endif
  }

  // Gyro Calibration
  gyroData.calibrated = EEPROM.read(EEPROM_ADD_GYRO_CAL);
  if (gyroData.calibrated == EEPROM_VAL_GYRO_CAL_OK)
  {
    gyroData.calibrated = 1;
    EEPROM.get(EERPOM_ADD_GYRO_VAL, gyroCalVal);
  }
  else
    gyroData.calibrated = 0;
    
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("03 - EPROM GYRO CAL: ");
  Serial.print(i);
  if (gyroData.calibrated == 1)
    Serial.println(" OK");
  else
   Serial.println(" NOK");
  #endif

  // Airspeed
  EEPROM.get(EERPOM_ADD_AIRS_VAL, airsData);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("04 - EPROM AIRSPEED: ");
  Serial.print(" digOffset: ");
  Serial.print(airsData.digOffset);
  Serial.print(" digEOS: ");
  Serial.print(airsData.digEOS);
  Serial.print(" mVoltsEOS: ");
  Serial.print(airsData.mVoltsEOS);
  Serial.print(" Gateway: ");
  Serial.println(airsData.senSensivity);  
  #endif
  
  // Altimeter
  EEPROM.get(EERPOM_ADD_ALT_VAL, altData);
  
  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("05 - EPROM ALT: "); 
  Serial.print(" QNH: ");
  Serial.println(altData.QNH);
  #endif
 
  // Units
  EEPROM.get(EERPOM_ADD_UNITS_VAL, units);

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.print("06 - EPROM UNITS: ");
  Serial.print(" alt: ");
  Serial.print(units.alt);
  Serial.print(" airspeed: ");
  Serial.print(units.airspeed);
  Serial.print(" vario: ");
  Serial.print(units.vario);
  Serial.print(" temp: ");
  Serial.println(units.temp);
  #endif
}

void _ResetEEPROM() {

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println("Erasing E2PROM 512 size... ");
  #endif

  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0xFF);
  }
  
  EEPROM.commit();    //Store data to EEPROM
}

void _ReadEEPROM() {

  int j = 0;

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println("Reading E2PROM 512 size... ");
  #endif

  EEPROM.begin(EEPROM_SIZE);
   
  for (int i = 0; i < EEPROM_SIZE; i++) {

    #if (_EEPROM_SERIAL_DEBUG_ == 1)
    j = EEPROM.read(i);
    if (j < 16)
      Serial.print("0");
    Serial.print(j, HEX);
    #endif
  }

  #if (_EEPROM_SERIAL_DEBUG_ == 1)
  Serial.println(" ");
  Serial.println("End ...");
  #endif  
}
