//var ip = "192.168.43.37";
var ip = "192.168.1.5";

$(document).ready( function()
{
	frefreshStatus();
});

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
			})
		});

		frefreshStatus();
	}, 1000);
}
