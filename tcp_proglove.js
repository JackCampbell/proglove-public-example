const net = require("net");

const port = 9393;

const server = net.createServer((socket) => {
    console.log("Client connected");

    socket.on("data", (data) => {
        const strData = data.toString();
        console.log(`Received: ${strData}`);
        
    });
	// socket.write(result.toString());
    socket.on("end", () => {
        console.log("Client disconnected");
    });

    socket.on("error", (error) => {
        console.log(`Socket Error: ${error.message}`);
    });
});

server.on("error", (error) => {
    console.log(`Server Error: ${error.message}`);
});

server.listen(port, "0.0.0.0", () => {
    console.log(`TCP socket server is running on port: ${port}`);
});

