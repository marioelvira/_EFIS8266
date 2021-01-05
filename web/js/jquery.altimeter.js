/* 
* jQuery Flight Indicators plugin
* By Sébastien Matton (seb_matton@hotmail.com)
* Published under GPLv3 License.
* 
* https://github.com/sebmatton/jQuery-Flight-Indicators
*/
(function($) {
	function FlightIndicator( placeholder, type, units, options ) {
		// Initial configuration
		var attitude = this;
		var settings = $.extend({
			altitude: 0,
			pressure: 1000,
			showBox : true,
			img_directory : 'img/'
		}, options );

		// Creation of the instrument
		placeholder.each(function(){
			switch(type){
				case 'altimeter':		
					if (units == 'feet')
						$(this).html('<div class="instrument altimeter"><img src="' + settings.img_directory + 'fi_box.svg" class="background box" alt="" /><div class="pressure box"><img src="' + settings.img_directory + 'altitude_pressure.svg" class="box" alt="" /></div><img src="' + settings.img_directory + 'altitude_ticks_feet.svg" class="box" alt="" /><div class="needleSmall box"><img src="' + settings.img_directory + 'fi_needle_small.svg" class="box" alt="" /></div><div class="needle box"><img src="' + settings.img_directory + 'fi_needle.svg" class="box" alt="" /></div><div class="mechanics box"><img src="' + settings.img_directory + 'fi_circle.svg" class="box" alt="" /></div></div>');
					else
						$(this).html('<div class="instrument altimeter"><img src="' + settings.img_directory + 'fi_box.svg" class="background box" alt="" /><div class="pressure box"><img src="' + settings.img_directory + 'altitude_pressure.svg" class="box" alt="" /></div><img src="' + settings.img_directory + 'altitude_ticks_meter.svg" class="box" alt="" /><div class="needleSmall box"><img src="' + settings.img_directory + 'fi_needle_small.svg" class="box" alt="" /></div><div class="needle box"><img src="' + settings.img_directory + 'fi_needle.svg" class="box" alt="" /></div><div class="mechanics box"><img src="' + settings.img_directory + 'fi_circle.svg" class="box" alt="" /></div></div>');
					_setAltitude(settings.altitude);
					_setPressure(settings.pressure);
					break;
				default:
					$(this).html('<div class="instrument attitude"><img src="' + settings.img_directory + 'fi_box.svg" class="background box" alt="" /><div class="roll box"><img src="' + settings.img_directory + 'horizon_back.svg" class="box" alt="" /><div class="pitch box"><img src="' + settings.img_directory + 'horizon_ball.svg" class="box" alt="" /></div><img src="' + settings.img_directory + 'horizon_circle.svg" class="box" alt="" /></div><div class="mechanics box"><img src="' + settings.img_directory + 'horizon_mechanics.svg" class="box" alt="" /><img src="' + settings.img_directory + 'fi_circle.svg" class="box" alt="" /></div></div>');
					_setRoll(settings.roll);
					_setPitch(settings.pitch);
			}
			$(this).find('div.instrument').css({height : settings.size, width : settings.size});
			$(this).find('div.instrument img.box.background').toggle(settings.showBox);
		});

		function _setAltitude(altitude){
			var needle = 90 + altitude%1000 * 360 / 1000;
			var needleSmall = altitude / 10000 * 360;
			placeholder.each(function(){
				$(this).find('div.instrument.altimeter div.needle').css('transform', 'rotate(' + needle + 'deg)');
				$(this).find('div.instrument.altimeter div.needleSmall').css('transform', 'rotate(' + needleSmall + 'deg)');
			});	
		}

		function _setPressure(pressure){
			pressure = 2*pressure - 1980;
			placeholder.each(function(){
				$(this).find('div.instrument.altimeter div.pressure').css('transform', 'rotate(' + pressure + 'deg)');
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
		this.setAltitude = function(altitude){_setAltitude(altitude);}
		this.setPressure = function(pressure){_setPressure(pressure);}
		this.resize = function(size){_resize(size);}
		this.showBox = function(){_showBox();}
		this.hideBox = function(){_hideBox();}

		return attitude;
	};

	// Extension to jQuery
	$.flightIndicator = function(placeholder, type, options){
		var flightIndicator = new FlightIndicator($(placeholder), type, options)
		return flightIndicator;
	}

	$.fn.flightIndicator = function(data, type, options){
		return this.each(function(){
			$.flightIndicator(this, type, options);
		});
	}
}( jQuery ));
