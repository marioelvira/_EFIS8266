void _phpNetworkCfg()
{
  String rwmode = httpServer.arg("wifimode");
  String rssid = httpServer.arg("wifissid");
  String rpass = httpServer.arg("wifipwd");
  
  String ripmode = httpServer.arg("ipmode");
  String ripaddress = httpServer.arg("ipaddress");
  String rmask = httpServer.arg("ipmask");
  String rgate = httpServer.arg("ipgateway");
    
  //String html = "";
  int i, j, k, m;
  int error = 0;
  char schar;
  char sbuf[4];
  byte val[4];

  IPAddress localip;
  IPAddress localmask;
  IPAddress localgate;

  #if (_PHP_SERIAL_DEBUG_ == 1)
  // Wi-Fi configuration
  Serial.print("---->Wi-Fi mode: ");
  Serial.println(rwmode);
  Serial.print("---->Wi-Fi SSID: ");
  Serial.println(rssid);
  Serial.print("---->Wi-Fi Password: ");
  Serial.println(rpass);
  Serial.println("");

  // IP configuration
  Serial.print("---->IP mode: ");
  Serial.println(ripmode);
  Serial.print("---->Local IP: ");
  Serial.println(localip);
  Serial.print("---->Local mask: ");
  Serial.println(localmask);
  Serial.print("---->Local gateway: ");
  Serial.println(localgate);
  #endif

  // Wi-Fi and IP configuration
  if (rwmode.length() > 0)
  {
    // Wi-Fi on Station mode
    if (rwmode == "1")
    {
      // must have a value
      if (rssid.length() == 0)
        error = 1;

      if (ripmode.length() == 0)
        error = 1;

      // must have a value
      if (ripmode == "1")
      {
        // Must be 
        if ((ripaddress.length() == 0) ||
            (rmask.length() == 0)      ||
            (rgate.length() == 0))
          error = 1;
      }
      // DHCP mode
      //else {}
      
    }
    // Wi-Fi Access Point mode
    //else {}
    
  }
  else
    error = 1;

  // If no error on data...
  if (error == 0)
  {
     /////////////////////////
     // Wi-Fi configuration //
     /////////////////////////
     #if (_PHP_SERIAL_DEBUG_ == 1)
     Serial.println("Wi-Fi 2 eeprom:");
     #endif
     
     // AP mode
     if (rwmode == "0")
       EEPROM.write(EEPROM_ADD_WIFI_MODE, ACCESSPOINT_MODE);
     else
     {
       // Station mode
       EEPROM.write(EEPROM_ADD_WIFI_MODE, STATION_MODE);
  
       // ssid
       for (i = 0; i < WIFI_SSID_MAX; i++)
         EEPROM.write(EEPROM_ADD_WIFI_SSID + i, 0);
       j = rssid.length();
       for (i = 0; i < j; i++)
         EEPROM.write(EEPROM_ADD_WIFI_SSID + i, rssid[i]);
       // password
       for (i = 0; i < WIFI_PSWD_MAX; i++)
         EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, 0);
       j = rpass.length();
       for (i = 0; i < j; i++)
         EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, rpass[i]);
       
       /////////////
       // IP Mpde //
       /////////////
       #if (_PHP_SERIAL_DEBUG_ == 1)
       Serial.println("IP 2 eeprom:");
       #endif
       // mode
       if (ripmode == "0")
         EEPROM.write(EEPROM_ADD_IP_MODE, DHCP_MODE);
       else
       {
         EEPROM.write(EEPROM_ADD_IP_MODE, FIXIP_MODE);
  
         // IP
         j = ripaddress.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = ripaddress[i];
           if (schar == '.')
           {        
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localip = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_IP1, val[0]);
         EEPROM.write(EEPROM_ADD_IP2, val[1]);
         EEPROM.write(EEPROM_ADD_IP3, val[2]);
         EEPROM.write(EEPROM_ADD_IP4, val[3]);
         
         // Mask
         j = rmask.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = rmask[i];
           if (schar == '.')
           {
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localmask = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_MASK1, val[0]);
         EEPROM.write(EEPROM_ADD_MASK2, val[1]);
         EEPROM.write(EEPROM_ADD_MASK3, val[2]);
         EEPROM.write(EEPROM_ADD_MASK4, val[3]);
    
         // Gateway
         j = rgate.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = rgate[i];
           if (schar == '.')
           {
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localgate = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_GATE1, val[0]);
         EEPROM.write(EEPROM_ADD_GATE2, val[1]);
         EEPROM.write(EEPROM_ADD_GATE3, val[2]);
         EEPROM.write(EEPROM_ADD_GATE4, val[3]);
       }

     }

     EEPROM.commit();

     #if (_READ_EEPROM_ == 1)
     _ReadEEPROM();
     delay(1000);
     #endif
    
     // Read config from EEPROM
     _readCONFIG();

     // OK
     i = 200;
  }
  else
  {
     #if (_PHP_SERIAL_DEBUG_ == 1)
     Serial.println("Sending 404");
     #endif

     // Error
     i = 404;
  }
  
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  if (i = 200)
    httpServer.send (i, "text/html", "OK"); // TODO
  else
    httpServer.send (i, "text/html", "Error"); // TODO
}

void _phpAltCfg()
{ 
  String qnh = httpServer.arg("QNH");

  altData.QNH = qnh.toInt();

  #if (_PHP_SERIAL_DEBUG_ == 1)
  Serial.print("---->QNH: ");
  Serial.println(altData.QNH);
  Serial.println("");
  #endif

  EEPROM.put(EERPOM_ADD_ALT_VAL, altData);

  EEPROM.commit();    //Store data to EEPROM

  // Read config from EEPROM
  _readCONFIG();

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "text/html", "OK");
}

void _phpAnemoCfg()
{ 
  String sAirDigOffset = httpServer.arg("airDigOffset");
  String sAirDigEOS = httpServer.arg("airDigEOS");
  String sAirmVoltsEOS = httpServer.arg("airmVoltsEOS");
  String sAirSenSensivity = httpServer.arg("airSenSensivity");

  airsData.digOffset = sAirDigOffset.toInt();
  airsData.digEOS = sAirDigEOS.toInt();
  airsData.mVoltsEOS = (float)sAirmVoltsEOS.toFloat();
  airsData.senSensivity = (float)sAirSenSensivity.toFloat();

  #if (_PHP_SERIAL_DEBUG_ == 1)
  Serial.print("---->airDigOffset: ");
  Serial.println(airsData.digOffset);
  Serial.print("---->airDigEOS: ");
  Serial.println(airsData.digEOS);
  Serial.print("---->airmVoltsEOS: ");
  Serial.println(airsData.mVoltsEOS);
  Serial.print("---->airSenSensivity: ");
  Serial.println(airsData.senSensivity);
  Serial.println("");
  #endif

  EEPROM.put(EERPOM_ADD_AIRS_VAL, airsData);
  
  EEPROM.commit();    //Store data to EEPROM

  // Read config from EEPROM
  _readCONFIG();
    
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "text/html", "OK");
}

void _phpGyroCfg()
{
  adafruit_bno055_offsets_t  gyroCalWeb;
  
  String accel_offset_x = httpServer.arg("accel_offset_x");
  String accel_offset_y = httpServer.arg("accel_offset_y");
  String accel_offset_z = httpServer.arg("accel_offset_z");
  String accel_radius   = httpServer.arg("accel_radius");

  String gyro_offset_x = httpServer.arg("gyro_offset_x");
  String gyro_offset_y = httpServer.arg("gyro_offset_y");
  String gyro_offset_z = httpServer.arg("gyro_offset_z");

  String mag_offset_x = httpServer.arg("mag_offset_x");
  String mag_offset_y = httpServer.arg("mag_offset_y");
  String mag_offset_z = httpServer.arg("mag_offset_z");
  String mag_radius   = httpServer.arg("mag_radius");

  gyroCalWeb.accel_offset_x = accel_offset_x.toInt();
  gyroCalWeb.accel_offset_y = accel_offset_y.toInt();
  gyroCalWeb.accel_offset_z = accel_offset_z.toInt();
  gyroCalWeb.accel_radius   = accel_radius.toInt();

  gyroCalWeb.gyro_offset_x = gyro_offset_x.toInt();
  gyroCalWeb.gyro_offset_y = gyro_offset_y.toInt();
  gyroCalWeb.gyro_offset_z = gyro_offset_z.toInt();

  gyroCalWeb.mag_offset_x = mag_offset_x.toInt();
  gyroCalWeb.mag_offset_y = mag_offset_y.toInt();
  gyroCalWeb.mag_offset_z = mag_offset_z.toInt();
  gyroCalWeb.mag_radius   = mag_radius.toInt();

  #if (_PHP_SERIAL_DEBUG_ == 1)
  Serial.print("----gyroCalWeb.accel_offset_x: ");
  Serial.println(gyroCalWeb.accel_offset_x);
  Serial.print("---->gyroCalWeb.accel_offset_y: ");
  Serial.println(gyroCalWeb.accel_offset_y);
  Serial.print("---->gyroCalWeb.accel_offset_z: ");
  Serial.println(gyroCalWeb.accel_offset_z);
  Serial.print("---->gyroCalWeb.accel_radius: ");
  Serial.println(gyroCalWeb.accel_radius);
  Serial.println("");
  Serial.print("----gyroCalWeb.gyro_offset_x: ");
  Serial.println(gyroCalWeb.gyro_offset_x);
  Serial.print("---->gyroCalWeb.gyro_offset_y: ");
  Serial.println(gyroCalWeb.gyro_offset_y);
  Serial.print("---->gyroCalWeb.gyro_offset_z: ");
  Serial.println(gyroCalWeb.gyro_offset_z);
  Serial.println("");
  Serial.print("----gyroCalWeb.mag_offset_x: ");
  Serial.println(gyroCalWeb.mag_offset_x);
  Serial.print("---->gyroCalWeb.mag_offset_y: ");
  Serial.println(gyroCalWeb.mag_offset_y);
  Serial.print("---->gyroCalWeb.mag_offset_z: ");
  Serial.println(gyroCalWeb.mag_offset_z);
  Serial.print("---->gyroCalWeb.mag_radius: ");
  Serial.println(gyroCalWeb.mag_radius);
  Serial.println("");
  #endif

  EEPROM.put(EERPOM_ADD_GYRO_VAL, gyroCalWeb);

  EEPROM.commit();    //Store data to EEPROM

  // Read config from EEPROM
  _readCONFIG();
    
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "text/html", "OK");
}

void _phpUnitsCfg()
{
  String units_alt = httpServer.arg("units_alt");
  String units_airspeed = httpServer.arg("units_airspeed");
  String units_vario = httpServer.arg("units_vario");
  String units_temp = httpServer.arg("units_temp");

  units.alt = units_alt.toInt();
  units.airspeed = units_airspeed.toInt();
  units.vario = units_vario.toInt();
  units.temp = units_temp.toInt();

  #if (_PHP_SERIAL_DEBUG_ == 1)
  Serial.print("----> alt: ");
  Serial.println(units.alt);
  Serial.print("----> airspeed: ");
  Serial.println(units.airspeed);
  Serial.print("---> vario: ");
  Serial.println(units.vario);
  Serial.print("----> temp: ");
  Serial.println(units.temp);
  Serial.println("");
  #endif

  EEPROM.put(EERPOM_ADD_UNITS_VAL, units);
  
  EEPROM.commit();    //Store data to EEPROM

  // Read config from EEPROM
  _readCONFIG();
    
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "text/html", "OK");
}
