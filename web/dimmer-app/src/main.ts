
document.addEventListener('DOMContentLoaded', () => {

  const socket = new WebSocket('ws://m5stamp.local:443');
  const brightnessSlider = document.getElementById('brightness');
  const brightnessValue = document.getElementById('brightnessValue');
  const kelvinSlider = document.getElementById('kelvin');
  const kelvinValue = document.getElementById('kelvinValue');

  socket.onopen = function () {
    console.log('WebSocket connection opened.');
  };

  brightnessSlider?.addEventListener('input', function () {
    const brightness = brightnessSlider.value;
    brightnessValue.textContent = brightness;
    socket.send("w " + brightness + " " + kelvinValue.textContent);
  });

  kelvinSlider.addEventListener('input', function () {
    const kelvin = kelvinSlider.value;
    kelvinValue.textContent = kelvin;
    socket.send("w " + brightnessSlider.value + " " + kelvin);
  });

  socket.onmessage = function (event) {
    console.log(event.data);
  };

});