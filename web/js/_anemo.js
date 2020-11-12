//var ip = "192.168.43.37";
//var ip = "192.168.1.5";
var ip = "172.16.0.50";

$(document).ready( function()
{
	fgetConfig();
	frefreshStatus();
});

function frefreshStatus()
{
	var jsondir = "http://" + ip +"/anemoStatus.json";
	
	setTimeout( function() {	

		$.getJSON(jsondir, function(jsonData) {
			
			console.log(jsonData);
    		
			$.each(jsonData, function(index, obj) {
				
				if (obj.param == "airInValue")
					$("#airInValue").html(obj.value);
				
				if (obj.param == "airInVolts")
					$("#airInVolts").html(obj.value);

				if (obj.param == "airPressure")
					$("#airPressure").html(obj.value);
				
				if (obj.param == "airSpeed")
					$("#airSpeed").html(obj.value);
			})
		});

		frefreshStatus();
	}, 1000);
}

function fgetConfig()
{
	var jsondir = "http://" + ip + "/anemoCfg.json";
	
	$.getJSON(jsondir, function(jsonData) {
		
		console.log(jsonData);
		
		$.each(jsonData, function(index, obj) {
			
			if (obj.param == "airInfo")
				$("#airInfo").html(obj.value);
				
			if (obj.param == "airDigOffset")
				$("#airDigOffset").val(obj.value);
			
			if (obj.param == "airDigEOS")
				$("#airDigEOS").val(obj.value);

			if (obj.param == "airmVoltsEOS")
				$("#airmVoltsEOS").val(obj.value);
			
			if (obj.param == "airSenSensivity")
				$("#airSenSensivity").val(obj.value);
		});
	});
}
