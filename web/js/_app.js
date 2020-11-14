var ip = localStorage.getItem("vip");

// Dynamic examples
var attitude = $.flightIndicator('#attitude', 'attitude', {roll:50, pitch:-20, size:200, showBox : true});
var heading = $.flightIndicator('#heading', 'heading', {heading:150, size:200, showBox:true});
var variometer = $.flightIndicator('#variometer', 'variometer', {vario:-5, showBox:true});
var airspeed = $.flightIndicator('#airspeed', 'airspeed', {showBox: true});
var altimeter = $.flightIndicator('#altimeter', 'altimeter');
var turn_coordinator = $.flightIndicator('#turn_coordinator', 'turn_coordinator', {turn:0});

$(document).ready( function()
{
	freInitStatus();
	frefreshStatus();
});

function freInitStatus()
{
	airspeed.setAirSpeed(0);
	attitude.setRoll(0);
	attitude.setPitch(0);
	altimeter.setAltitude(0);
	altimeter.setPressure(0);
	heading.setHeading(0);
	turn_coordinator.setTurn(0);
	variometer.setVario(0);
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

