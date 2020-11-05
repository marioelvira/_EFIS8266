var ip = "192.168.43.37";

$(document).ready( function()
{
	frefreshStatus();
});

function frefreshStatus()
{
	var jsondir = "http://" + ip +"/ioStatus.json";
	
	setTimeout( function() {	

		$.getJSON(jsondir, function(jsonData) {
			
			console.log(jsonData);
    		
			$.each(jsonData, function(index, obj) {
				
				if (obj.param == "uptime")
					$("#uptime").html(obj.value);
				
				if (obj.param == "outAux")
					$("#outAux").html(obj.value);
				
				if (obj.param == "inAux")
					$("#inAux").html(obj.value);
			})
		});

		frefreshStatus();
	}, 1000);
}

function sendOUT(out)
{
	var xhttp = new XMLHttpRequest();
	
	xhttp.open("GET", "http://" + ip + "/setOUT?OUTstate=" + out, true);
	xhttp.send();
}