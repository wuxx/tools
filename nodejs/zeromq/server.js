var zmq = require("zmq");  
var socket = zmq.socket("req");  
var counter = 0;

// Just a helper function for logging to the console with a timestamp.
function logToConsole (message) {  
    console.log("[" + new Date().toLocaleTimeString() + "] " + message);
}

function sendMessage (message) {  
    logToConsole("Sending: " + message);
    socket.send(message);
}

// Add a callback for the event that is invoked when we receive a message.
socket.on("message", function (message) {  
    // Convert the message into a string and log to the console.
    logToConsole("Response: " + message.toString("utf8"));
});

// Begin listening for connections on all IP addresses on port 9998.
socket.bind("tcp://*:9998", function (error) {  
    if (error) {
        logToConsole("Failed to bind socket: " + error.message);
        process.exit(0);
    }
    else {
        logToConsole("Server listening on port 9998");

        // Increment the counter and send the value to the clients every second.
        setInterval(function () { sendMessage(counter++); }, 1000);
    }
});
