var ip = localStorage.getItem("vip");

$(document).ready( function()
{
	frefreshStatus();
});

function frefreshStatus()
{
	var jsondir = "http://" + ip + "/systemStatus.json";
	
	setTimeout( function() {	

		$.getJSON(jsondir, function(jsonData) {
			
			console.log(jsonData);
    		
			$.each(jsonData, function(index, obj) {
				
				if (obj.param == "date")
					$("#datetxt").html(obj.value);
				
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