var express = require('express');
var app = express();
var url = require('url');
var notp = require('notp')

var flag = '0'
var lastReq = ""
var lastBody = ""
var key = '12345678738462738192';

app.get('/lastBody', function(req, res){
	res.send(lastBody);
})

app.get('/lastReq', function(req, res){
	res.send(lastReq);
})

app.get('/', function(req, res){
	res.send(flag);
	flag = '0';
});

app.get('/sms', function(req, res){
	lastReq = url.parse(req.url, true);
	lastReq = lastReq.query;
	lastBody = lastReq.Body;
	console.log("Code entered: " + lastBody);
	
	var auth = notp.totp.verify(lastBody, key);

	if (auth){
		flag = '1';
		console.log("Door Unlock");
	} else {
		console.log("Incorrect Code");
	}
	res.send('Thanks for the text!');
});

app.listen((process.env.PORT || 80));
