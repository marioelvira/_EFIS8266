//var _ip = "192.168.43.37";
//var _ip = "192.168.1.5";
//var _ip = "172.16.0.50";
var _ip = "192.168.4.1";

localStorage.setItem("vip", _ip); 

// Disable form submissions if there are invalid fields
(function() {
	'use strict';
	window.addEventListener('load', function() {
		// Get the forms we want to add validation styles to
		var forms = document.getElementsByClassName('needs-validation');
		// Loop over them and prevent submission
		var validation = Array.prototype.filter.call(forms, function(form) {
			form.addEventListener('submit', function(event) {
				if (form.checkValidity() === false) {
					event.preventDefault();
					event.stopPropagation();
				}
				form.classList.add('was-validated');
			}, false);
		});
	}, false);
})();
