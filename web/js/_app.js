var ip = "192.168.43.37";

// Dynamic examples
var attitude = $.flightIndicator('#attitude', 'attitude', {roll:50, pitch:-20, size:200, showBox : true});
var heading = $.flightIndicator('#heading', 'heading', {heading:150, size:200, showBox:true});
var variometer = $.flightIndicator('#variometer', 'variometer', {vario:-5, showBox:true});
var airspeed = $.flightIndicator('#airspeed', 'airspeed', {showBox: true});
var altimeter = $.flightIndicator('#altimeter', 'altimeter');
var turn_coordinator = $.flightIndicator('#turn_coordinator', 'turn_coordinator', {turn:0});

// Update at 20Hz
var increment = 0;


setInterval(function()
{
	var jsondir = "http://" + ip +"/data.json";
	
	$.getJSON(jsondir, function(jsonData) {
		
		console.log(jsonData);
    		
		$.each(jsonData, function(index, obj) {

			if (obj.param == "airSpeed")
			{
				airspeed.setAirSpeed(obj.value);
				$("#vairspeed").html(obj.value);
			}

			if (obj.param == "rollAngle")
				attitude.setRoll(obj.value);

			if (obj.param == "pitchAngle")
				attitude.setPitch(obj.value);
					
			if (obj.param == "heading")
			{
				heading.setHeading(obj.value);
				$("#vheading").html(obj.value);
			}
					
			if (obj.param == "turnAngle")
			{
				turn_coordinator.setTurn(obj.value);
				$("#vturn").html(obj.value);
			}
		})

	});
		
	// Airspeed update
	//airspeed.setAirSpeed(80 + 80*Math.sin(increment/10));

	// Attitude update
	//attitude.setRoll(30*Math.sin(increment/10));
	//attitude.setPitch(50*Math.sin(increment/20));

	// Altimeter update
	altimeter.setAltitude(10*increment);
	altimeter.setPressure(1000 + 3*Math.sin(increment/50));
	increment++;
		
	// TC update - note that the TC appears opposite the angle of the attitude indicator, as it mirrors the actual wing up/down position
	//turn_coordinator.setTurn((30*Math.sin(increment/10))*-1);

	// Heading update
	//heading.setHeading(increment);
		
	// Vario update
	variometer.setVario(2*Math.sin(increment/10));
}, 100);

