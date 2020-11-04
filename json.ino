
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
