var ip = "192.168.43.37";

$(document).ready( function()
{
	fgetConfig();
	frefreshStatus();
});

function frefreshStatus()
{
	var jsondir = "http://" + ip +"/gyroStatus.json";
	
	setTimeout( function() {	

		$.getJSON(jsondir, function(jsonData) {
			
			console.log(jsonData);
    		
			$.each(jsonData, function(index, obj) {
				
				if (obj.param == "gyroStatus")
					$("#gyroStatus").html(obj.value);
				
				if (obj.param == "system_status")
					$("#system_status").html(obj.value);
				
				if (obj.param == "system_selftest")
					$("#system_selftest").html(obj.value);
				
				if (obj.param == "system_error")
					$("#system_error").html(obj.value);
				
				if (obj.param == "cal_sys")
					$("#cal_sys").html(obj.value);
				
				if (obj.param == "cal_gyro")
					$("#cal_gyro").html(obj.value);
				
				if (obj.param == "cal_accel")
					$("#cal_accel").html(obj.value);
				
				if (obj.param == "cal_mag")
					$("#cal_mag").html(obj.value);
				
				if (obj.param == "coor_x")
					$("#coor_x").html(obj.value);
				
				if (obj.param == "coor_y")
					$("#coor_y").html(obj.value);
				
				if (obj.param == "coor_z")
					$("#coor_z").html(obj.value);
				
				if (obj.param == "gyro_mag")
					$("#gyro_mag").html(obj.value);
				
				if (obj.param == "gyro_roll")
					$("#gyro_roll").html(obj.value);
				
				if (obj.param == "gyro_pitch")
					$("#gyro_pitch").html(obj.value);
				
				if (obj.param == "gforce")
					$("#gforce").html(obj.value);

			})
		});

		frefreshStatus();
	}, 1000);
}

function fgetConfig()
{
	var jsondir = "http://" + ip +"/gyroCfg.json";
	
	$.getJSON(jsondir, function(jsonData) {
		
		console.log(jsonData);
			
		$.each(jsonData, function(index, obj) {
			
			if (obj.param == "gyroInfo")
				$("#gyroInfo").html(obj.value);
			
			if (obj.param == "accel_offset_x")
				$("#accel_offset_x").val(obj.value);
			
			if (obj.param == "accel_offset_y")
				$("#accel_offset_y").val(obj.value);
			
			if (obj.param == "accel_offset_z")
				$("#accel_offset_z").val(obj.value);
			
			if (obj.param == "accel_radius")
				$("#accel_radius").val(obj.value);
			
			if (obj.param == "gyro_offset_x")
				$("#gyro_offset_x").val(obj.value);
			
			if (obj.param == "gyro_offset_y")
				$("#gyro_offset_y").val(obj.value);
			
			if (obj.param == "gyro_offset_z")
				$("#gyro_offset_z").val(obj.value);
			
			if (obj.param == "mag_offset_x")
				$("#mag_offset_x").val(obj.value);
			
			if (obj.param == "mag_offset_y")
				$("#mag_offset_y").val(obj.value);
			
			if (obj.param == "mag_offset_z")
				$("#mag_offset_z").val(obj.value);
			
			if (obj.param == "mag_radius")
				$("#mag_radius").val(obj.value);

		});
	});
}

function _sendGyroCfg()
{
	var xhttp = new XMLHttpRequest();
	
	xhttp.open("GET", "http://" + ip + "/setOUT?OUTstate=" + out, true);
	xhttp.send();
}