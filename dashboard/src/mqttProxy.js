const awsIot = require('aws-iot-device-sdk');
const express = require('express');
const http = require('http');
const WebSocket = require('ws');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

const device = awsIot.device({
  keyPath: '../certs/client.key',
  certPath: '../certs/client.crt',
  caPath: '../certs/root_cert_auth.crt',
  clientId: 'BinCascade',
  host: 'a3ksmy0rrvp2q3-ats.iot.ap-southeast-1.amazonaws.com'
});

device.on('connect', () => {
  console.log('Connected to AWS IoT');
  device.subscribe('esp32/example/topic');
});

device.on('message', (topic, payload) => {
  wss.clients.forEach(client => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(payload.toString())
      console.log(payload.toString())
    }
  });
});

server.listen(3001, () => {
  console.log('WebSocket server listening on port 3001');
});
