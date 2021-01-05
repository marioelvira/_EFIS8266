var ip = localStorage.getItem("vip");

var altimeter;
var units_alt = 0;

$(document).ready( function()
{
	freInitStatus();
	fgetConfig();
	frefreshStatus();
});

function freInitStatus()
{
	var jsondir = "http://" + ip + "/unitsCfg.json";
	
	$.getJSON(jsondir, function(jsonData) {
			
		$.each(jsonData, function(index, obj) {
			
			if (obj.param == "units_alt")
			{
				units_alt = obj.value;
				
				if (units_alt == 0)
					altimeter = $.flightIndicator('#altimeter', 'altimeter', 'feet', {showBox: true});
				else
					altimeter = $.flightIndicator('#altimeter', 'altimeter', 'meters', {showBox: true});
				altimeter.setAltitude(0);
				altimeter.setPressure(0);
			}
		});
	});
}

function frefreshStatus()
{
	var jsondir = "http://" + ip +"/altimStatus.json";
	
	setTimeout( function() {	

		$.getJSON(jsondir, function(jsonData) {
			
			console.log(jsonData);
    		
			$.each(jsonData, function(index, obj) {
				
				if (obj.param == "altStatus")
					$("#altStatus").html(obj.value);
				
				if (obj.param == "alt_temp")
					$("#alt_temp").html(obj.value);

				if (obj.param == "alt_humid")
					$("#alt_humid").html(obj.value);
				
				if (obj.param == "alt_press")
					$("#alt_press").html(obj.value);
				
				if (obj.param == "altitude")
				{
					$("#altitude").html(obj.value);
					altimeter.setAltitude(obj.value);
				}
				
				if (obj.param == "qnh")
				{
					$("#qnh").html(obj.value);
					altimeter.setPressure(obj.value);
				}
			})
		});

		frefreshStatus();
	}, 1000);
}

function fgetConfig()
{
	var jsondir = "http://" + ip + "/altimCfg.json";
	var phpdir  = "http://" + ip + "/altimCfg.php";

	$("#formCfg").attr("action", phpdir);
	
	$.getJSON(jsondir, function(jsonData) {
		
		console.log(jsonData);
		
		$.each(jsonData, function(index, obj) {
			
			if (obj.param == "altInfo")
				$("#altInfo").html(obj.value);
				
			if (obj.param == "QNH")
				$("#QNH").val(obj.value);

		});
	});
}

