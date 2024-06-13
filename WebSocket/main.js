const express = require('express');
const fs = require("fs");
const path = require("path");
const os = require("os");
const expressws = require('express-ws');

const app = express();
const port = 9500;
const host = "0.0.0.0";

const static_path = path.join(__dirname, 'public');

app.set('view engine', 'ejs');
app.use("/static", express.static(static_path));


app.get('/', (req, res) => {
	res.render('index.ejs');
});

var ws = expressws(app);
app.ws('/echo', function(ws, req) {
	console.log("Connected client");
	ws.on('message', function(msg) {
		// ws.send(msg);
		console.log(">> ", msg);
	});
});


app.listen(port, host, () => {
	console.log("Example app listening on  http://" + host + ":" + port);
});
