var SerialPort = require("serialport").SerialPort;

var portName = "/dev/tty.usbserial-FTGNNHBR";
var serialPort = new SerialPort(portName, {
  baudrate: 115200
});

var buffer;

serialPort.on('open', function(){
  console.log('serialPort open:', portName);
});

module.exports = serialPort;
