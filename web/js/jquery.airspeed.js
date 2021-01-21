(function($) {
	function jQAirspeedIndicator( placeholder, units, options ) {
		// Initial configuration
		var attitude = this;
		var settings = $.extend({
			size : 200,
			airspeed: 0,
			showBox : true,
			img_directory : 'img/'
		}, options );

		var constants = {
			airspeed_bound_l : 0,
			airspeed_bound_h : 160
		}

		// Creation of the instrument
		placeholder.each(function(){
			switch(units){
				default:
					$(this).html('<div class="instrument airspeed"><img src="' + settings.img_directory + 'fi_box.svg" class="background box" alt="" /><img src="' + settings.img_directory + 'speed_mechanics.svg" class="box" alt="" /><div class="speed box"><img src="' + settings.img_directory + 'fi_needle.svg" class="box" alt="" /></div><div class="mechanics box"><img src="' + settings.img_directory + 'fi_circle.svg" class="box" alt="" /></div></div>');
					_setAirSpeed(settings.airspeed);
					break
			}
			$(this).find('div.instrument').css({height : settings.size, width : settings.size});
			$(this).find('div.instrument img.box.background').toggle(settings.showBox);
		});

		// Private methods
		function _setAirSpeed(speed){
			if(speed > constants.airspeed_bound_h){speed = constants.airspeed_bound_h;}
			else if(speed < constants.airspeed_bound_l){speed = constants.airspeed_bound_l;}
			speed = 90+speed*2;
			placeholder.each(function(){
				$(this).find('div.instrument.airspeed div.speed').css('transform', 'rotate(' + speed + 'deg)');
			});	
		}

		function _resize(size){
			placeholder.each(function(){
				$(this).find('div.instrument').css({height : size, width : size});
			});
		}

		function _showBox(){
			placeholder.each(function(){
				$(this).find('img.box.background').show();
			});
		}

		function _hideBox(){
			placeholder.each(function(){
				$(this).find('img.box.background').hide();
			});
		}

		// Public methods
		this.setAirSpeed = function(speed){_setAirSpeed(speed);}
		this.resize = function(size){_resize(size);}
		this.showBox = function(){_showBox();}
		this.hideBox = function(){_hideBox();}

		return attitude;
	};

	// Extension to jQuery
	$.jQAirspeed = function(placeholder, type, options){
		var jQAirspeed = new jQAirspeedIndicator($(placeholder), type, options)
		return jQAirspeed;
	}

	$.fn.jQAirspeed = function(data, type, options){
		return this.each(function(){
			$.jQAirspeed(this, type, options);
		});
	}
}( jQuery ));
