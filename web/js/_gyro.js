
$(document).ready( function()
{
	fgetConfig();
});

function fgetConfig()
{
	$.getJSON("http://192.168.1.5/gyroCfg.json", function(jsonData) {
		
		console.log(jsonData);
			
		$.each(jsonData, function(index, obj) {
			
			// Gyroscope
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
