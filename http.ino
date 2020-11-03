void _HttpSetup(void)
{
  // Http status
  httpStatus = HTTP_INIT;
}

void _HttpEnd(void)
{
  httpServer.stop();
}

///////////
// Pages //
///////////

void _serveCSS()
{
  httpServer.send (200, "text/css", cssSTYLE);
}

void _serveMAIN()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Status</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>EFIS+ #Status<span>ESP8266 tech</span></h1>";

  html = html + "<div class=\"section\"><span>1</span>Time Alive</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<div class=\"sansserif\" id=\"TIMEid\">...</div>";
  html = html + "</div>";
  
  html = html + "<div class=\"section\"><span>1</span>Digital INs</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<div class=\"sansserif\" id=\"INValue\">...</div>";
  html = html + "</div>";
  
  html = html + "<div class=\"section\"><span>2</span>Digital OUTs</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<div class=\"sansserif\" id=\"OUTValue\">...</div>";
  html = html + "<p>";
  html = html + "  <input type=\"button\" value=\"Change\" onclick=\"sendOUT(2)\">";
  html = html + "</p>";
  html = html + "</div>";
  
  html = html + "<div class=\"section\"><span>3</span>Instruments</div>";
  html = html + "<p>";  
  html = html + "  <a href=\"gyro.htm\"><input type=\"button\" value=\"Gyroscope\"></a>";
  html = html + "</p>";

  html = html + "<div class=\"section\"><span>4</span>Configuration</div>";
  html = html + "<p>";  
  html = html + "  <a href=\"network.htm\"><input type=\"button\" value=\"Network\"></a>";
  html = html + "</p>";
  
  html = html + "</div>"; // "<div class=\"myform\">";

  html = html + "<script>";
  
  html = html + "function sendOUT(out) {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.open(\"GET\", \"setOUT?OUTstate=\"+out, true);";
  html = html +  "  xhttp.send();";
  html = html + "}";
  
  html = html + "setInterval(function() {";
  html = html + "  getOUT();";
  html = html + "  getIN();";
  html = html + "  getTIME();";
  html = html +  "}, 1000);";
  
  html = html +  "function getOUT() {";
  html = html +  "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"OUTValue\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html +  "  };";
  html = html + "  xhttp.open(\"GET\", \"readOUT\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "function getIN() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html +  "      document.getElementById(\"INValue\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readIN\", true);";
  html = html +  "  xhttp.send();";
  html = html + "}";

  html = html + "function getTIME() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"TIMEid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readTIME\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "</script>";

  html = html + "</div>";
  
  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

//////////
// Gyro //
//////////
void _serveGYRO()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Gyro</title>";
  html = html + "<head>";
  html = html + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>EFIS+ #Status<span>ESP8266 Gyro</span></h1>";

  // Gyro
  html = html + "<div class=\"section\"><span>1</span>Status</div>";
  html = html + "<div class=\"inner-wrap\">";
  html = html + "<p class=\"sansserif\" id=\"GYROid\">...</p>";
  html = html + "</div>";
  // End
  
  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Back\"></a>";
  html = html + "</div>";
  
  html = html + "<script>";
    
  html = html + "setInterval(function() {";
  html = html + "  getGYRO();";
  html = html +  "}, 1000);";
  
  html = html + "function getGYRO() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"GYROid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readGYRO\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "</script>";

  html = html + "</div>";
  
  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

///////////////////
// Configuration //
///////////////////
void _serveNETWORK()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Network Settings</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>ESP8266+ #Network settings<span>myWEB project</span></h1>";
  //html = html + "<form method=\"post\">";
  html = html + "<form method='get' action='networSettings'>";

  // Wi-Fi
  html = html + "<div class=\"section\"><span>1</span>Wi-Fi Settings</div>";
  html = html + "<div class=\"inner-wrap\">";

  if (wifiMode == STATION_MODE)
  {
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"ap\"> Access Point</label>";
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"st\" checked> Station</label>";
  }
  else
  {
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"ap\" checked> Access Point</label>";
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"st\"> Station</label>";
  }
  
  html = html + "<label>SSID <input type=\"text\" maxlength=\"30\" value=\"" + String(ssid) + "\" name=\"ssid\"/></label>";
  html = html + "<label>Password <input type=\"text\" maxlength=\"30\" value=\"" + String(password) + "\" name=\"pass\"/></label>";

  html = html + "</div>";
  // End

  // Red
  html = html + "<div class=\"section\"><span>2</span>IP Settings</div>";
  html = html + "<div class=\"inner-wrap\">";

  if (ipMode == DHCP_MODE)
  {
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\" checked> DHCP</label>";
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\"> Fix IP</label>";
  }
  else
  {
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\"> DHCP</label>";
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\" checked> Fix IP</label>";
  }

  html = html + "<label>IP Address <input type=\"text\"  maxlength=\"16\" value=\"" + String(ipAddress.toString()) + "\" name=\"ipaddress\"/></label>";
  html = html + "<label>Mask <input type=\"text\" maxlength=\"16\" value=\"" + String(netMask.toString()) + "\" name=\"mask\"/></label>";
  html = html + "<label>Gateway <input type=\"text\" maxlength=\"16\" value=\"" + String(gateWay.toString()) + "\" name=\"gateway\"/></label>";

  html = html + "</div>";
  // End
                        
  html = html + "<div class=\"button-section\">";
  html = html + "  <input type=\"submit\" value=\"Save\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Back\"></a>";
  html = html + "</div>";
  
  html = html + "</div>";
  html = html + "</div>";
  html = html + "</form>";
  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

void _setNETWORK()
{
  String rwmode = httpServer.arg("wifimode");
  String rssid = httpServer.arg("ssid");
  String rpass = httpServer.arg("pass");
  
  String ripmode = httpServer.arg("ipmode");
  String ripaddress = httpServer.arg("ipaddress");
  String rmask = httpServer.arg("mask");
  String rgate = httpServer.arg("gateway");
    
  String html = "";
  int i, j, k, m;
  int error = 0;
  char schar;
  char sbuf[4];
  byte val[4];

  IPAddress localip;
  IPAddress localmask;
  IPAddress localgate;

  // Wi-Fi and IP configuration
  if (rwmode.length() > 0)
  {
    // Wi-Fi on Station mode
    if (rwmode == "st")
    {
      // must have a value
      if (rssid.length() == 0)
        error = 1;

      if (ripmode.length() == 0)
        error = 1;

      // must have a value
      if (ripmode == "ipfx")
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
     #if (_SERIAL_DEBUG_ == 1)
     Serial.println("Wi-Fi 2 eeprom:");
     #endif
     
     // AP mode
     if (rwmode == "ap")
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
       #if (_SERIAL_DEBUG_ == 1)
       Serial.println("IP 2 eeprom:");
       #endif
       // mode
       if (ripmode == "dhcp")
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
     
     #if (_SERIAL_DEBUG_ == 1)
     // Wi-Fi configuration
     Serial.print("---->Wi-Fi mode: ");
     Serial.println(rwmode);
     Serial.print("---->Wi-Fi SSID: ");
     Serial.println(rssid);
     Serial.print("---->Wi-Fi Password: ");
     Serial.println(rpass);
     Serial.println("");

     // IP configuration
     Serial.print("---->Local IP: ");
     Serial.println(localip);
     Serial.print("---->Local mask: ");
     Serial.println(localmask);
     Serial.print("---->Local gateway: ");
     Serial.println(localgate);
     #endif
     
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
     #if (_SERIAL_DEBUG_ == 1)
     Serial.println("Sending 404");
     #endif

     // Error
     i = 404;
   }

  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Network Settings</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>ESP8266+ #Network settings<span>myWEB project</span></h1>";
  
  if (i == 200)
    html += "<p>Settings OK: Saved</p>";
  else
    html += "<p>Settings Error: Not Saved</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Back\"></a>";
  html = html + "</div>";

  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

/////////////
// Actions //
/////////////
void _readIN()
{
  String html = "";

  html = "<table style=\"width:100%\">";
   
  html = html + "<tr>";
  html = html + "<td>Alarma </td>";
  if (inAux == IO_ON)
   html = html + "<td><font style=\"color:red\">Activa</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">OFF</font></td>";
  html = html + "</tr>";
  
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readOUT()
{
  String html = "";

  html = "<table style=\"width:100%\">";
   
  html = html + "<tr>";
  html = html + "<td>Aviso Alarma</td>";
  if (outAux == IO_ON)
   html = html + "<td><font style=\"color:red\">Activado</font></td>";
  else
   html = html + "<td><font style=\"color:grey\">Desactivado</font></td>";
  html = html + "</tr>";
    
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}
 
void _setOUT()
{
 String t_state = httpServer.arg("OUTstate");
 String html = "";
 
 #if (_HTTP_SERIAL_DEBUG_ == 1)
 Serial.print("Change state out: ");
 Serial.println(outAux);
 #endif

 if(t_state == "2")
 {
   if (outAux == IO_ON)
   {
     outAux = IO_OFF;
     html = "OFF";
     
     #if (_HTTP_SERIAL_DEBUG_ == 1)
     Serial.println("Out OFF");
     #endif
   }
   else
   {
     outAux = IO_ON;
     html = "ON";

     #if (_HTTP_SERIAL_DEBUG_ == 1)
     Serial.println("Out OFF");
     #endif
   }
 }
 else
 {
   html = "Error";

   #if (_HTTP_SERIAL_DEBUG_ == 1)
   Serial.println("Out Error");
   #endif
 }

 httpServer.sendHeader("Access-Control-Allow-Origin","*");
 httpServer.send(200, "text/plane", html);
}

void _readTIME()
{ 
  String html = "";

  html = "<table style=\"width:100%\">";
  
  html = html + "<tr>";
  html = html + "<td>Tiempo Encendio</td>";
  html = html + "<td>" + String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec) + "</td>";
  html = html + "</tr>";

  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

void _readGYRO()
{
  String html = "";

  html = "<table style=\"width:100%\">";

  html = html + "<tr>";
  html = html + "<td>Status</td>";
  switch (gyroStatus)
  {
    case GYRO_DETECTION:
      html = html + "<td>Detecting...</td>"; break;
    case GYRO_DETECTED:
      html = html + "<td>Detected</td>"; break;
    case GYRO_CALIBRATED:
      html = html + "<td>Calibrated</td>"; break;
    case GYRO_IN_CALIBRATION:
      html = html + "<td>In Calibration</td>"; break;
    case GYRO_WORKING:
      html = html + "<td>Working</td>"; break;
    case GYRO_NOT_DETECTED:
      html = html + "<td>Not Detected</td>"; break;
  }
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>System</td>";
  html = html + "<td>Status: 0x" + String(system_status) + " Test: 0x" + String(system_selftest) + " Error: 0x" + String(system_error) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Calibration</td>";
  html = html + "<td> sys: " + String(sys) + " - G: " + String(gyro) + " - A: " + String(accel) + " - M: " + String(mag) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Giro</td>";
  html = html + "<td>x " + String(gyroCalVal.gyro_offset_x) + " y " + String(gyroCalVal.gyro_offset_y) + " z " + String(gyroCalVal.gyro_offset_z) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Accel</td>";
  html = html + "<td>x " + String(gyroCalVal.accel_offset_x) + " y " + String(gyroCalVal.accel_offset_y) + " z " + String(gyroCalVal.accel_offset_z) + " r " + String(gyroCalVal.accel_radius) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Mag</td>";
  html = html + "<td>x " + String(gyroCalVal.mag_offset_x) + " y " + String(gyroCalVal.mag_offset_y) + " z " + String(gyroCalVal.mag_offset_z) + " r " + String(gyroCalVal.mag_radius) + "</td>";
  html = html + "</tr>";
  
  html = html + "<tr>";
  html = html + "<td>Coordenadas</td>";
  html = html + "<td> x: " + String(event.orientation.x) + " y: " + String(event.orientation.y) + " z: " + String(event.orientation.z) + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>Gyro</td>";
  html = html + "<td> MAG: " + String(gMag) + " Roll: " + sRoll + " Pitch: " + sPitch + "</td>";
  html = html + "</tr>";

  html = html + "<tr>";
  html = html + "<td>G Force</td>";
  html = html + "<td> G: " + String(iGforce/10.0) + "</td>";
  html = html + "</tr>";
    
  html = html + "</table>";
  
  httpServer.send(200, "text/plane", html);
}

// Json Cfg
void _jsonGyroCfg()
{
  String json= "";

  json = "[";
    
  json = json + "{ \"param\":\"accel_offset_x\", \"value\":" + String(gyroCalVal.accel_offset_x) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"accel_offset_y\", \"value\":" + String(gyroCalVal.accel_offset_y) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"accel_offset_z\", \"value\":" + String(gyroCalVal.accel_offset_z) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"accel_radius\", \"value\":" + String(gyroCalVal.accel_radius) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_offset_x\", \"value\":" + String(gyroCalVal.gyro_offset_x) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_offset_y\", \"value\":" + String(gyroCalVal.gyro_offset_y) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_offset_z\", \"value\":" + String(gyroCalVal.gyro_offset_z) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"mag_offset_x\", \"value\":" + String(gyroCalVal.mag_offset_x) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"mag_offset_y\", \"value\":" + String(gyroCalVal.mag_offset_y) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"mag_offset_z\", \"value\":" + String(gyroCalVal.mag_offset_z) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"mag_radius\", \"value\":" + String(gyroCalVal.mag_radius) + " }";
  
  json = json + "]";

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonNetworkCfg()
{
  String json= "";

  json = "[";
  
  json = json + "{ \"param\":\"wifimode\", \"value\":" + String(wifiMode) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"wifissid\", \"value\":\"" + String(ssid) + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"wifipwd\", \"value\":\"" + String(password) + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"ipmode\", \"value\":" + String(ipMode) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"ipaddress\", \"value\":\"" + String(ipAddress.toString()) + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"ipmask\", \"value\":\"" + String(netMask.toString()) + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"ipgateway\", \"value\":\"" + String(gateWay.toString()) + "\" }";
  
  json = json + "]";

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

// Json Status
void _jsonIOStatus()
{
  String json = "";

  json = "[";
  
  json = json + "{ \"param\":\"uptime\", \"value\":\"" + String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec) + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"outAux\", \"value\":" + String(outAux) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"inAux\", \"value\":" + String(inAux) + " }";

  json = json + "]";
  
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonGyroStatus()
{
  String json= "";
  String jsonGyroStatus = "";

  switch (gyroStatus)
  {
    case GYRO_DETECTION:
      jsonGyroStatus = "Detecting..."; break;
    case GYRO_DETECTED:
      jsonGyroStatus = "Detected"; break;
    case GYRO_CALIBRATED:
      jsonGyroStatus = "Calibrated"; break;
    case GYRO_IN_CALIBRATION:
      jsonGyroStatus = "In Calibration"; break;
    case GYRO_WORKING:
      jsonGyroStatus = "Working"; break;
    case GYRO_NOT_DETECTED:
      jsonGyroStatus = "Not Detected"; break;
  }

  json = "[";
    
  json = json + "{ \"param\":\"gyroStatus\", \"value\":\"" + jsonGyroStatus + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"system_status\", \"value\":" + String(system_status) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"system_selftest\", \"value\":" + String(system_selftest) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"system_error\", \"value\":" + String(system_error) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"cal_sys\", \"value\":" + String(sys) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"cal_gyro\", \"value\":" + String(gyro) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"cal_accel\", \"value\":" + String(accel) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"cal_mag\", \"value\":" + String(mag) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"coor_x\", \"value\":" + String(event.orientation.x) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"coor_y\", \"value\":" + String(event.orientation.y) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"coor_z\", \"value\":" + String(event.orientation.z) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_mag\", \"value\":" + String(gMag) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_roll\", \"value\":\"" + sRoll + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_pitch\", \"value\":\"" + sPitch + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"gforce\", \"value\":" + String(iGforce/10.0) + " }";
  
  json = json + "]";
  
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

// Json data main
void _jsonDATA()
{
  String json= "";

  json = "[";
  
  json = json + "{ \"param\":\"airSpeed\", \"value\":" + String(airSpeed) + " }"; // TODO
  json = json + ",";
  json = json + "{ \"param\":\"rollAngle\", \"value\":" + String(gRoll) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"pitchAngle\", \"value\":" + String(-1*gPitch) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"altitute\", \"value\":" + String(altitute) + " }"; // TODO
  json = json + ",";
  json = json + "{ \"param\":\"QNH\", \"value\":" + String(QNH) + " }"; // TODO
  json = json + ",";
  json = json + "{ \"param\":\"turnAngle\", \"value\":" + String(-1*gRoll) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"heading\", \"value\":" + String(gMag) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"vario\", \"value\":" + String(vario) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"ratio\", \"value\":" + String(timeMilisec - timeJSONMilisec) + " }"; // TODO
  
  json = json + "]";

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);

  timeJSONMilisec = timeMilisec;
}

////////////////////////
// Http state machine //
////////////////////////
void _HttpLoop()
{
  switch (httpStatus)
  {
    case HTTP_INIT:

      // css Style
      httpServer.on("/style.css",         _serveCSS);

      // html pages
      httpServer.on("/",                  _serveMAIN);
      httpServer.on("/index.htm",         _serveMAIN);
      httpServer.on("/gyro.htm",          _serveGYRO);
      httpServer.on("/network.htm",       _serveNETWORK);

      // acctions
      httpServer.on("/setOUT",            _setOUT);
      httpServer.on("/readOUT",           _readOUT);
      httpServer.on("/readIN",            _readIN);
      httpServer.on("/readTIME",          _readTIME);
      httpServer.on("/readGYRO",          _readGYRO);
      httpServer.on("/networSettings",    _setNETWORK);

      // Json data
      httpServer.on("/data.json",         _jsonDATA);

      // Json Status
      httpServer.on("/ioStatus.json",     _jsonIOStatus);
      httpServer.on("/gyroStatus.json",   _jsonGyroStatus);

      // Json Config
      httpServer.on("/networkCfg.json",   _jsonNetworkCfg);
      httpServer.on("/gyroCfg.json",      _jsonGyroCfg);
      
      httpServer.begin();

      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.print("HTTP server started on ");
      Serial.print(HTTP_PORT);
      Serial.println(" port");      
      #endif
      httpStatus = HTTP_ONSERVE;
      break;
    
    case HTTP_ONSERVE:
      httpServer.handleClient();
      break;
  }
}
