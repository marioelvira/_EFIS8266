var ip = localStorage.getItem("vip");

$(document).ready( function()
{
	fgetConfig();
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
				
				if (obj.param == "altitude")
					$("#altitude").html(obj.value);
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

