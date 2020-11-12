//var ip = "192.168.43.37";
//var ip = "192.168.1.5";
var ip = "172.16.0.50";

$(document).ready( function()
{
	frefreshStatus();
});

function frefreshStatus()
{
	var jsondir = "http://" + ip +"/systemStatus.json";
	
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

function sendCMD(out)
{
	var xhttp = new XMLHttpRequest();
	
	xhttp.open("GET", "http://" + ip + "/setCMD?CMDsent=" + out, true);
	xhttp.send();
}