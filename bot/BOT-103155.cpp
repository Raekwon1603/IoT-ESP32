#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESPmDNS.h> 
#include <DHT.h>
#include "secret.h"

#define LED 2
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);           // Initialize DHT sensor
WiFiClientSecure espClient;         // Initialize Wi-Fi client with SSL/TLS
PubSubClient mqttClient(espClient); // Initialize MQTT client with Wi-Fi client


void connectToWiFi(){   //connect to WIi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length){ // MQTT message callback
  Serial.print("Message received on topic [");
  Serial.print(topic);
  Serial.print("]: ");
  String receivedMessage = "";
  for (int i = 0; i < length; i++)
  {
    receivedMessage.concat((char)payload[i]);
  }
  Serial.println(receivedMessage);

  if(receivedMessage.startsWith(MQTT_CLIENT_ID)){   // Parse the incoming message and respond accordingly
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
    if (isnan(humidity) || isnan(temperature)) {     // Check if the DHT sensor reading is valid
      mqttClient.publish("chat/message", "Fout bij het lezen van de DHT Sensor van BOT-1034155");
      return;
    }

    String message = receivedMessage.substring(13);
    if(message.equals("led:uit")){
      digitalWrite(LED, LOW);
      mqttClient.publish("chat/message", "LED is uit");
    }
    else if(message.equals("led:aan")){
      digitalWrite(LED, HIGH);
      mqttClient.publish("chat/message", "LED is aan");
    }
    else if(message.equals("vochtigheid")){
      String humidityMessage = "Vochtigheid is " + String(humidity) + "%";
      mqttClient.publish("chat/message", humidityMessage.c_str());
    }
    else if(message.equals("temperatuur")){
      String temperatureMessage = "Temperatuur is " + String(temperature) + "°C";
      mqttClient.publish("chat/message", temperatureMessage.c_str());
    }
  }
}

void connectToMQTT(){
  while (!mqttClient.connected()){
    Serial.print("Connecting to MQTT...");
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)){
      mqttClient.subscribe("chat/message", 0);
      mqttClient.publish("chat/message", "BOT-1034155 has joined the chat");
    }
    else{
      Serial.print("failed, status code = ");
      Serial.print(mqttClient.state());
      Serial.println(". Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup(){    // Initialize components and connect to Wi-Fi and MQTT
  Serial.begin(115200);
  connectToWiFi();

  espClient.setCACert(local_root_ca);

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)){
    mqttClient.subscribe("chat/message", 0);
    mqttClient.publish("chat/message", "BOT-1034155 has joined the chat");
  }

  mqttClient.setCallback(callback);
  
  dht.begin();
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop(){
  if (!mqttClient.connected()){
    connectToMQTT();
  }
  
  mqttClient.loop();
}
