
$(document).ready( function()
{
	fgetConfig();
});

function fgetConfig()
{
	$.getJSON("http://192.168.1.5/networkCfg.json", function(jsonData) {
		
		console.log(jsonData);
			
		$.each(jsonData, function(index, obj) {
			
			// Network
			if (obj.param == "wifimode")
				$("#wifimode").val(obj.value);

			if (obj.param == "wifissid")
				$("#wifissid").val(obj.value);
			
			if (obj.param == "wifipwd")
				$("#wifipwd").val(obj.value);
			
			if (obj.param == "ipmode")
				$("#ipmode").val(obj.value);
			
			if (obj.param == "ipaddress")
				$("#ipaddress").val(obj.value);
			
			if (obj.param == "ipmask")
				$("#ipmask").val(obj.value);

			if (obj.param == "ipgateway")
				$("#ipgateway").val(obj.value);

		});
	});
}