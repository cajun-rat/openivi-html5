
function Dial(jq_needle, minangle, maxangle, min, max) {
  this.jq_needle = jq_needle;
  this.minangle = minangle;
  this.maxangle = maxangle;
  this.min = min;
  this.max = max;
  this.value = min;
}

Dial.prototype.set = function (value) {
  var angle = this.minangle + (this.maxangle - this.minangle)/(this.max - this.min) * value;
  this.jq_needle.css("transform", "translateZ(0) rotate("+angle+"deg)");
  this.value = value;
};

Dial.prototype.fade = function (rate) {
  this.set(this.value * rate);
}

function init() {
  var amp_dial = new Dial($('#iatNeedle'), -143, 143, 0, 200);
  var rpm_dial = new Dial($('#rpmNeedle'), 5, 180, 0, 10000);
  var range_dial = new Dial($('#loadNeedle'), -90, 90, 0, 150);
  var oil_temp_dial = new Dial($('#oilTempNeedle'), 228, 185, 0, 80);
  var engine_coolant_dial = new Dial($('#engineCoolantNeedle'), 275, 324, 40, 140);

  amp_dial.set(55);
  oil_temp_dial.set(50);
  engine_coolant_dial.set(85);
  var speed = $('#velocity');
  if (window.car) {
    window.car.rpm.connect(function (rpm) {
      rpm_dial.set(rpm);
      amp_dial.set(rpm/100);
      range_dial.set(50);
      speed.text(Math.floor(rpm/80)); 
    });
  } else if (window.console) {
    console.log("window.car not found");
  }
}

$(init);
/* vim: set expandtab tabstop=2 shiftwidth=2: */
