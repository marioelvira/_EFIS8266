$(document).ready( function()
{
	fRefreshData();
});

function fRefreshData()
{
	setTimeout( function() {	

		$.getJSON("http://192.168.1.5/data.json", function(jsonData) {
		
			console.log(jsonData);
    		
			$.each(jsonData, function(index, obj) {

				//if (obj.param == "airSpeed")
				//	$("#date").html(obj.value);

				//if (obj.param == "rollAngle")
				//	$("#modeTxt").html(obj.value);

			})

		});

		fRefreshData();
	
	}, 1000);
}

