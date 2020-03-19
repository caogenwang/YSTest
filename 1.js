function rgb2hsv(r, g, b) {
    r /= 255;
    g /= 255;
    b /= 255;
    var max = Math.max(r, g, b);
    var min = Math.min(r, g, b);
    var diff = max - min;
    var h = 0;
    var v = max;
    var s = max === 0 ? 0 : diff / max; // h

    if (max === min) {
      h = 0;
    } else if (max === r && g >= b) {
      h = 60 * ((g - b) / diff);
    } else if (max === r && g < b) {
      h = 60 * ((g - b) / diff) + 360;
    } else if (max === g) {
      h = 60 * ((b - r) / diff) + 120;
    } else if (max === b) {
      h = 60 * ((r - g) / diff) + 240;
    }
    return [Math.round(h), Math.round(s * 100), Math.round(v * 100)];
  }
  console.log(rgb2hsv(35,31,32));
  