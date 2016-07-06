/* 
 *  LibUse
 *  https://github.com/arkhipenko/TaskScheduler
 *  https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTlib
 */
 
#define _TASK_SLEEP_ON_IDLE_RUN
#define _NODE_DEVICE

#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22
#define FTPIN 0   // moisture sensor analog pin

#include <TaskScheduler.h>
#include "DHT.h"
#include "zunonode.h"

ZUNONODE transport;
DHT dht(DHTPIN, DHTTYPE);
Scheduler runner;

// Callback methods prototypes
void dht_send(); //dht send
void ft_send(); //moisture sensor send
//intervall check task wenn änderung, dann senden


Task t1(5000, TASK_FOREVER, &dht_send, &runner, true);  //adding task to the chain on creation
Task t2(2000, TASK_FOREVER, &ft_send, &runner, true);  //adding task to the chain on creation


void dht_send() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Read temperature as Celsius (the default)
  //float hic = dht.computeHeatIndex(t, h, false);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("failed read dht!");
    return;
  }
  
  transport.set_values(1, (t*100));
  transport.set_values(2, (h*100));
  transport.send_values('A');
}
void ft_send() {
  float sensorValue = analogRead(FTPIN);
  sensorValue = ((1024-sensorValue) / 1024) * 100;
  
  transport.set_values(1, sensorValue);
  transport.send_values('B');
}

void setup() {
  Serial.begin(9600);
  Serial.println("zuno dht node v2");
  dht.begin();
  
  delay(5000);
  runner.startNow();
}

void loop() {
  runner.execute();
}
