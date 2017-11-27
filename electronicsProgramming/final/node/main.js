var serialPort = require('./serial.js');

var osc = require('node-osc');
var express = require('express');

var app = express();
var port = 3000;

app.use(express.static('static/'));
app.use(express.bodyParser());

app.get('/', function(req, res){
  res.sendfile(index.html);
});

app.post('/serial', function(req, res){
  var value = parseInt(req.body.value, 10) % 256;
  serialPort.write(String.fromCharCode(value));
  console.log('Serial req body/value:', req.body, value, typeof(value));

  if (typeof(value) === 'number'){
    res.send(202);
  } else {
    res.send(400, 'error: parseInt did not return a number on .value');
  }

});

// Setup our osc client
var client = new osc.Client('127.0.0.1', 3333);

// handle incoming serial msgs
serialPort.on('data', function(data){
  var buffer = data.toString();
  // console.log(buffer.charCodeAt(0));
  client.send('/water', + buffer.charCodeAt(0));
});

app.listen(port);
