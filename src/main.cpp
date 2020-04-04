#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>
#include <constants.h>
#include <connect.h>


WiFiClient net;
MQTTClient client;


long reportTimer = millis();
long alarmTimer = millis();

void setup() {
  
  

  Serial.begin(115200);
  WiFi.begin(SSID, SSID_PASSWORD);

  client.begin(BROKER, net);

  connect(Serial, net, client);
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect(Serial, net, client);
  }

  if(millis()-reportTimer >= REPORT_FREQ){
    reportTimer=millis();
    client.publish(String(MQTT_ID)+"/report", String(analogRead(A0)));
  }

  if(digitalRead(INPUT_BTN) && millis()-alarmTimer >= MAX_ALARM_FREQ){    
    alarmTimer = millis();
    client.publish(String(MQTT_ID)+"/alarm", "Warning!");
    delay(500);
  }
}