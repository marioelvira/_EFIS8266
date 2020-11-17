
//////////////////
// Wi-Fi set up //
//////////////////
void _WifiSetup(void)
{
  // Wi-Fi status
  wifiStatus = WIFI_START_ACCESSPOINT;
  wifiInfo = "";
}

/////////////////////////
// Wi-Fi state machine //
/////////////////////////
void _WifiLoop()
{
  switch (wifiStatus)
  {
    case WIFI_START_ACCESSPOINT:

      wifiInfo =            "Access point mode start </br>";
      wifiInfo = wifiInfo + "SSID: " + ssidAp + "</br>";
      wifiInfo = wifiInfo + "PASSWORD: " + passwordAp + "</br>";
    
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssidAp, passwordAp);
  
      wifiIP = WiFi.softAPIP();

      wifiInfo = wifiInfo + "AP IP address: " + wifiIP.toString() + "</br>";
      
      #if (_WIFI_SERIAL_DEBUG_ == 1)
      Serial.println("------------------------------------");
      Serial.println(wifiInfo);
      Serial.println("------------------------------------");
      Serial.println("");
      #endif
      
      // Http setup
      _HttpSetup();

      wifiAPTick = millis();
        
      wifiStatus = WIFI_ON_ACCESSPOINT;
      break;

    case WIFI_ON_ACCESSPOINT:
      // Station mode...
      if (wifiMode == STATION_MODE)
      {       
        if (millis() - wifiAPTick >= WIFI_ACCESSPOINT_TIMEOUT)
        {
          _HttpEnd();

          wifiStatus = WIFI_START_STATION;
        }
      }
      // Access point mode...
      else
      {
        wifiAPTick = millis();
      }   
      break;

    case WIFI_START_STATION:
    
      WiFi.begin(ssid, password);
      WiFi.macAddress(mac);
     
      WiFi.disconnect();          // Prevent connecting to wifi based on previous configuration
      WiFi.hostname(deviceName);  // DHCP Hostname (useful for finding device for static lease)
    
      if (ipMode == FIXIP_MODE)
        WiFi.config(ipAddress, netMask, gateWay);

      WiFi.begin(ssid, password);
      WiFi.mode(WIFI_STA);        // WiFi mode station (connect to wifi router only)

      wifiInfo =            "Station Mode start </br>";
      wifiInfo = wifiInfo + "SSID: " + ssid + "</br>";
      wifiInfo = wifiInfo + "PASSWORD: " + password + "</br>";

      #if (_WIFI_SERIAL_DEBUG_ == 1)
      Serial.println("------------------------------------");
      Serial.println(wifiInfo);
      Serial.println("------------------------------------");
      Serial.println("");
      #endif

      wifiStatus = WIFI_STATION_CONNECTING;
      break;
      
    case WIFI_STATION_CONNECTING:
      // If no connected...
      if (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
    
        #if (_WIFI_SERIAL_DEBUG_ == 1)
        Serial.print(".");
        #endif
      }
      // If connected...
      else
      {

        ipAddress = WiFi.localIP();
        gateWay   = WiFi.gatewayIP();
        netMask   = WiFi.subnetMask();

        wifiInfo = wifiInfo + "IP Mode: ";
        if (ipMode == FIXIP_MODE)
          wifiInfo = wifiInfo + "Fix </br>";
        else
          wifiInfo = wifiInfo + "DHCP </br>";
        
        wifiInfo = wifiInfo + "IP address: " + ipAddress.toString() + "</br>";
        wifiInfo = wifiInfo + "Mask: "       + netMask.toString()   + "</br>";
        wifiInfo = wifiInfo + "Gateway: "    + gateWay.toString()   + "</br>";
        //wifiInfo = wifiInfo + "MAC: " + (String)(mac[5],HEX) + ":" + (String)(mac[4],HEX) + ":" + (String)(mac[3],HEX) + ":" + (String)(mac[2],HEX) + ":" + (String)(mac[1],HEX) + ":" + (String)(mac[0],HEX) + "</br>";  

        #if (_WIFI_SERIAL_DEBUG_ == 1)
        Serial.println("------------------------------------");
        Serial.println(wifiInfo);
        Serial.println("------------------------------------");
        Serial.println("");
        Serial.print("MAC: ");
        Serial.print(mac[5],HEX);
        Serial.print(":");
        Serial.print(mac[4],HEX);
        Serial.print(":");
        Serial.print(mac[3],HEX);
        Serial.print(":");
        Serial.print(mac[2],HEX);
        Serial.print(":");
        Serial.print(mac[1],HEX);
        Serial.print(":");
        Serial.println(mac[0],HEX);
        #endif
        
        // Http setup
        _HttpSetup();
      
        wifiStatus = WIFI_STATION_CONNECTED;
      }
      break;

    case WIFI_STATION_CONNECTED:
      // If no connected...
      if (WiFi.status() != WL_CONNECTED)
      {
        _HttpEnd();
        
        wifiStatus = WIFI_START_STATION;
      }

      break;
  }
}

/////////////////////////
// Wi-Fi state machine //
/////////////////////////
void _WifiLedLoop()
{
  switch (wifiStatus)
  {
    case WIFI_START_ACCESSPOINT:
      wifiLEDTick = millis();
      outLed = IO_OFF;
      break;

    case WIFI_ON_ACCESSPOINT:
      if (millis() - wifiLEDTick >= WIFI_BLINK_ACCESSPOINT)
      {
        if (outLed == IO_OFF)
          outLed = IO_ON;
        else
          outLed = IO_OFF;

        wifiLEDTick = millis();

        //#if (_WIFI_SERIAL_DEBUG_ == 1)
        //if (wifiMode == STATION_MODE)
        //  Serial.print(">");
        //else
        //  Serial.print(".");
        //#endif
      } 
      break;

    case WIFI_START_STATION:
    case WIFI_ON_STATION:
    case WIFI_STATION_CONNECTING:
      if (millis() - wifiLEDTick >= WIFI_BLINK_CONNECTING)
      {
        if (outLed == IO_OFF)
          outLed = IO_ON;
        else
          outLed = IO_OFF;

        wifiLEDTick = millis();
      } 
      break;

    case WIFI_STATION_CONNECTED:
      if (millis() - wifiLEDTick >= WIFI_BLINK_STATION)
      {
        //#if (_WIFI_SERIAL_DEBUG_ == 1)
        //Serial.print("-");
        //#endif
        
        wifiLEDTick = millis();
      } 
    
      outLed = IO_ON;
      break;
  }
}
