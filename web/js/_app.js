var ip = localStorage.getItem("vip");

// Dynamic examples
var attitude;
var heading;
var variometer;
var airspeed;
var altimeter;
var turn_coordinator;

var units_alt = 0;
var units_airspeed = 0;
var units_vario = 0;

$(document).ready( function()
{
	freInitStatus();
	frefreshStatus();
});

function freInitStatus()
{
	var jsondir = "http://" + ip + "/unitsCfg.json";
	
	$.getJSON(jsondir, function(jsonData) {
		
		console.log(jsonData);
			
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
			
			if (obj.param == "units_airspeed")
			{
				units_airspeed = obj.value;
				
				airspeed = $.flightIndicator('#airspeed', 'airspeed', '0', {showBox: true});
				airspeed.setAirSpeed(0);
			}
			
			if (obj.param == "units_vario")
			{
				units_vario = obj.value;
				
				variometer = $.flightIndicator('#variometer', 'variometer', '0', {vario:-5, showBox:true});
				variometer.setVario(0);
			}
			
			//if (obj.param == "units_temp")
			//	units_temp = obj.value;
		});
	});
	

	
	attitude = $.flightIndicator('#attitude', 'attitude', '0', {roll:50, pitch:-20, size:200, showBox : true});
	attitude.setRoll(0);
	attitude.setPitch(0);

	heading = $.flightIndicator('#heading', 'heading', '0', {heading:150, size:200, showBox:true});
	heading.setHeading(0);
	
	turn_coordinator = $.flightIndicator('#turn_coordinator', 'turn_coordinator', '0', {turn:0});
	turn_coordinator.setTurn(0);
	
	$("#appInfo").html("<i class=\"fas fa-wifi\" style=\"color:red;\"></i> Connecting...");
}

function frefreshStatus()
{
	var jsondir = "http://" + ip + "/data.json";
	
	setInterval(function()
	{	
		$.getJSON(jsondir, function(jsonData) {
			
			console.log(jsonData);
				
			$.each(jsonData, function(index, obj) {

				$("#appInfo").html("<i class=\"fas fa-wifi\" style=\"color:blue;\"></i> Connected");

				if (obj.param == "airSpeed")
					airspeed.setAirSpeed(obj.value);

				if (obj.param == "rollAngle")
					attitude.setRoll(obj.value);

				if (obj.param == "pitchAngle")
					attitude.setPitch(obj.value);
				
				if (obj.param == "altitude")
					altimeter.setAltitude(obj.value);

				if (obj.param == "QNH")
					altimeter.setPressure(obj.value);			
				
				if (obj.param == "heading")
					heading.setHeading(obj.value);
			
				if (obj.param == "turnAngle")
					turn_coordinator.setTurn(obj.value);
				
				if (obj.param == "vario")
					variometer.setVario(obj.value);
			})

		});
			
	}, 100);
}

