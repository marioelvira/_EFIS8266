///////////////////
// Configuration //
///////////////////

void _jsonAltCfg()
{
  String json= "";

  json = "[";

  json = json + "{ \"param\":\"altInfo\", \"value\":\"" + altInfo + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"cfg_qnh\", \"value\":\"" + altData.QNH + "\" }";
  json = json + "]";

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonAnemoCfg()
{
  String json= "";

  json = "[";

  json = json + "{ \"param\":\"airInfo\", \"value\":\"" + airInfo + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airDigOffset\", \"value\":\"" + airsData.digOffset + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airDigEOS\", \"value\":\"" + airsData.digEOS + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airmVoltsEOS\", \"value\":\"" + airsData.mVoltsEOS + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airSensR\", \"value\":\"" + airsData.airSensR + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airSensPA1\", \"value\":\"" + airsData.airSensPA1 + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airSensPA2\", \"value\":\"" + airsData.airSensPA2 + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airSensV1\", \"value\":\"" + airsData.airSensV1 + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"airSensV2\", \"value\":\"" + airsData.airSensV2 + "\" }";
  json = json + "]";

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonGyroCfg()
{
  String json= "";

  json = "[";

  json = json + "{ \"param\":\"gyroInfo\", \"value\":\"" + gyroInfo + "\" }";
  json = json + ",";
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

void _jsonUnitsCfg()
{
  String json= "";

  json = "[";
  
  json = json + "{ \"param\":\"units_alt\", \"value\":" + String(units.alt) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"units_airspeed\", \"value\":" + String(units.airspeed) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"units_vario\", \"value\":" + String(units.vario) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"units_temp\", \"value\":" + String(units.temp) + " }";
  
  json = json + "]";

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonNetworkCfg()
{
  String json= "";

  json = "[";

  json = json + "{ \"param\":\"wifiInfo\", \"value\":\"" + wifiInfo + "\" }";
  json = json + ",";
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

////////////
// Status //
////////////
void _jsonSystemStatus()
{
  String json = "";

  json = "[";

  #if (_USE_RTC_ == 1)
  json = json + "{ \"param\":\"uptime\", \"value\":\"" + RtcTimeStr + "\" }";
  #else
  json = json + "{ \"param\":\"uptime\", \"value\":\"" + String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec) + "\" }";
  #endif
  json = json + ",";
  json = json + "{ \"param\":\"outAux\", \"value\":" + String(outAux) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"inAux\", \"value\":" + String(inAux) + " }";

  json = json + "]";
  
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonAnemoStatus()
{
  String json = "";

  json = "[";

  json = json + "{ \"param\":\"airInValue\", \"value\":" + String(AirInValue) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"airInValueC\", \"value\":" + String(AirInValueCorrected) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"airInVolts\", \"value\":" + String(Air_mVolts) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"airPressure\", \"value\":" + String(AirPressure) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"airSpeed\", \"value\":" + String(AirSpeed) + " }";

  json = json + "]";
  
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonAltStatus()
{
  String json= "";
  String jsonAltStatus = "...";

  switch (altStatus)
  {
    case ALT_DETECTION:
      jsonAltStatus = "Detecting..."; break;
    case ALT_DETECTED:
      jsonAltStatus = "Detected"; break;
    case ALT_WORKING:
      jsonAltStatus = "Working"; break;
    case ALT_NOT_DETECTED:
      jsonAltStatus = "Not Detected"; break;
  }

  json = "[";
    
  json = json + "{ \"param\":\"altStatus\", \"value\":\"" + jsonAltStatus + "\" }";
  json = json + ",";
  if (units.temp == TEMP_KELVIN)
    json = json + "{ \"param\":\"alt_temp\", \"value\":\"" + String(temp_event.temperature + 273,15) + " K\" }";
  else if (units.temp == TEMP_FARENHEIT)
    json = json + "{ \"param\":\"alt_temp\", \"value\":\"" + String(((temp_event.temperature)* 9/5) + 32) + " ºF\" }";
  else
    json = json + "{ \"param\":\"alt_temp\", \"value\":\"" + String(temp_event.temperature) + " ºC\" }";
  json = json + ",";
  json = json + "{ \"param\":\"alt_humid\", \"value\":\"" + String(humidity_event.relative_humidity) + " %\" }";
  json = json + ",";
  json = json + "{ \"param\":\"alt_press\", \"value\":\"" + String(pressure_event.pressure) + " hPa\" }";
  json = json + ",";
  if (units.alt == ALT_FEET)
    json = json + "{ \"param\":\"alt_value\", \"value\":\"" + String(Altimeter) + " feet\" }";
  else 
    json = json + "{ \"param\":\"alt_value\", \"value\":\"" + String(Altimeter) + " meters\" }";
  json = json + ",";
  json = json + "{ \"param\":\"qnh_value\", \"value\":\"" + String(altData.QNH) + " hPa\" }";
  json = json + ",";
  json = json + "{ \"param\":\"altimeter\", \"value\":" + String(Altimeter) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"QNH\", \"value\":" + String(altData.QNH) + " }";
  json = json + "]";
  
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

void _jsonGyroStatus()
{
  String json= "";
  String jsonGyroStatus = "...";

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
  json = json + "{ \"param\":\"coor_x\", \"value\":" + String(gyroEvent.orientation.x) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"coor_y\", \"value\":" + String(gyroEvent.orientation.y) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"coor_z\", \"value\":" + String(gyroEvent.orientation.z) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_mag\", \"value\":" + String(gMag) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_roll\", \"value\":\"" + sRoll + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"gyro_pitch\", \"value\":\"" + sPitch + "\" }";
  json = json + ",";
  json = json + "{ \"param\":\"gforce\", \"value\":" + String(iGforce/10.0) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"ball\", \"value\":" + String(iBall) + " }";
  
  json = json + "]";
  
  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);
}

// Json data main
void _jsonDATA()
{
  String json= "";

  json = "[";
  
  json = json + "{ \"param\":\"airSpeed\", \"value\":" + String(AirSpeed) + " }";
  json = json + ",";
  if (units.airspeed == AIRS_KNOTS)
    json = json + "{ \"param\":\"airSpeedtxt\", \"value\":\"" + String(AirSpeed) + " knots\" }";
  else 
    json = json + "{ \"param\":\"airSpeedtxt\", \"value\":\"" + String(AirSpeed) + " km/h\" }";
  json = json + ",";
  
  json = json + "{ \"param\":\"rollAngle\", \"value\":" + String(gRoll) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"pitchAngle\", \"value\":" + String(-1*gPitch) + " }";
  json = json + ",";
  
  json = json + "{ \"param\":\"altimeter\", \"value\":" + String(Altimeter) + " }";
  json = json + ",";
  if (units.alt == ALT_FEET)
    json = json + "{ \"param\":\"altimetertxt\", \"value\":\"" + String(Altimeter) + " feet\" }";
  else 
    json = json + "{ \"param\":\"altimetertxt\", \"value\":\"" + String(Altimeter) + " meters\" }";
  json = json + ",";
  
  json = json + "{ \"param\":\"QNH\", \"value\":" + String(altData.QNH) + " }";
  json = json + ",";
  
  json = json + "{ \"param\":\"turnAngle\", \"value\":" + String(-1*gRoll) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"turnAngletxt\", \"value\":\"" + sRoll + "\" }";
  json = json + ",";

  json = json + "{ \"param\":\"heading\", \"value\":" + String(gMag) + " }";
  json = json + ",";
  json = json + "{ \"param\":\"headingtxt\", \"value\":\"" + String(gMag) + "º\" }";
  json = json + ",";
  
  json = json + "{ \"param\":\"vario\", \"value\":" + String(Vario) + " }";
  json = json + ",";
  if (units.vario == VARIO_FEETpM)
    json = json + "{ \"param\":\"variotxt\", \"value\":\"" + String(Vario) + " feet/min\" }";
  else
    json = json + "{ \"param\":\"variotxt\", \"value\":\"" + String(Vario) + " m/min\" }";
  json = json + ",";
  
  json = json + "{ \"param\":\"ratio\", \"value\":" + String(timeMilisec - timeJSONMilisec) + " }";
  
  json = json + "]";

  httpServer.sendHeader("Access-Control-Allow-Origin","*");
  httpServer.send (200, "application/json", json);

  timeJSONMilisec = timeMilisec;
}
