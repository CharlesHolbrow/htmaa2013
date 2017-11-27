var serial = require('./serial.js');
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
  serial.write(String.fromCharCode(value));
  console.log('Serial req body/value:', req.body, value, typeof(value));

  if (typeof(value) === 'number'){
    res.send(202);
  } else {
    res.send(400, 'error: parseInt did not return a number on .value');
  }

});

app.listen(port);
