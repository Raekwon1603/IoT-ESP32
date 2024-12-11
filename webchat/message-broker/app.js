const input = document.querySelector('input');
const button = document.querySelector('button');
const messages = document.querySelector('#messages');

let clientId;
let client;
let host;
let options;

function setClient() {
    clientId = 'student-' + Math.random().toString(16).substr(2, 4);
    host = 'wss://netwerkenbasis.com:1884';
    options = {
        username: 'student',
        password: 'welkom01',
        keepalive: 50,
        clientId: clientId,
        protocolVersion: 4,
        clean: true,
        reconnectPeriod: 2000,
        connectTimeout: 50000,
    };
    client = mqtt.connect(host, options);
}

function subscribeToMessages() {
    client.on('connect', () => {
        console.log('Connected to the broker');
        client.subscribe('chat/message');
    });
}

function handleConnectionError() {
    client.on('error', (err) => {
        console.log('Connection failed error: ', err);
        client.end();
    });
}

function displayReceivedMessage(topic, message, packet) {
        const li = document.createElement('li');
        li.innerHTML = message
        messages.appendChild(li);
    }

function sendMessage() {
    if (input.value) {
        client.publish('chat/message', input.value)
        input.value = '';
    }
}

input.addEventListener('keyup', function(event) {
    if (event.keyCode === 13) {
        event.preventDefault();
        sendMessage();
    }
});

button.addEventListener('click', sendMessage);

setClient();
subscribeToMessages();
handleConnectionError();

client.on('message', displayReceivedMessage);
