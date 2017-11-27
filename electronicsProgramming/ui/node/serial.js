var SerialPort = require("serialport").SerialPort;

var portName = "/dev/tty.usbserial-FTGNNHBR";
var serialPort = new SerialPort(portName, {
  baudrate: 115200
});

var buffer;

serialPort.on('open', function(){
  console.log('serialPort open:', portName);
  serialPort.on('data', function(data){
    buffer = data.toString();

    console.log('new data: "'+ buffer + '" END', buffer.charCodeAt(0));
  });
});

module.exports = serialPort;
