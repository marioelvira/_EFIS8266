var ip = localStorage.getItem("vip"); 

$(document).ready( function()
{
	fgetConfig();
});

function fgetConfig()
{
	var jsondir = "http://" + ip + "/unitsCfg.json";
	var phpdir  = "http://" + ip + "/unitsCfg.php";

	$("#formCfg").attr("action", phpdir);
	
	$.getJSON(jsondir, function(jsonData) {
		
		console.log(jsonData);
			
		$.each(jsonData, function(index, obj) {
			
			if (obj.param == "units_alt")
				$("#units_alt").val(obj.value);

			if (obj.param == "units_airspeed")
				$("#units_airspeed").val(obj.value);
			
			if (obj.param == "units_vario")
				$("#units_vario").val(obj.value);
			
			if (obj.param == "units_temp")
				$("#units_temp").val(obj.value);

		});
	});
}

