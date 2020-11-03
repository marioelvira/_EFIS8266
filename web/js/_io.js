
$(document).ready( function()
{
	frefreshStatus();
});

function frefreshStatus()
{
	setTimeout( function() {	

		$.getJSON("http://192.168.1.5/ioStatus.json", function(jsonData) {
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
