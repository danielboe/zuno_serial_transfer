/* 
 *  LibUse
 *  https://github.com/arkhipenko/TaskScheduler
 *  https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTlib
 */
 
#define _TASK_SLEEP_ON_IDLE_RUN

#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22
#define FTPIN 0   // moisture sensor analog pin
#define TRIGGER_PIN  12 //ultraschall distanz
#define ECHO_PIN     11 //ultraschall distanz
#define MAX_DISTANCE 200 //ultraschall distanz

#include <TaskScheduler.h>
#include "DHT.h"
#include "zunonode.h"
#include <NewPing.h>

ZUNONODE transport;
DHT dht(DHTPIN, DHTTYPE);
Scheduler runner;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

SENSOR temp;
//SENSOR sonic;
//SENSOR moist;

// Callback methods prototypes
void dht_send(); //dht send
void ft_send(); //moisture sensor send
void sonic_send(); //sonic distance sensor send
//intervall check task wenn änderung, dann senden

Task t1(1000, TASK_FOREVER, &dht_send, &runner, true);  //adding task to the chain on creation
Task t2(2000, TASK_FOREVER, &ft_send, &runner, true);  //adding task to the chain on creation
Task t3(2000, TASK_FOREVER, &sonic_send, &runner, true);  //adding task to the chain on creation

void dht_send() {
  float h = dht.readHumidity(true);
  float t = dht.readTemperature(false,true);  // Read temperature as Celsius (the default)
  //float hic = dht.computeHeatIndex(t, h, false);
 /*Serial.print("loop:");
  Serial.println(temp.test_counter(100));
  Serial.print("h: ");
  Serial.println(temp.test_value(1, &h, 0.5));
  Serial.print("t: ");
  Serial.println(temp.test_value(2 , &t, 0.5));*/
    
  if (isnan(h) || isnan(t)) {
    Serial.println("error");
    return;
    }  // Check if any reads failed and exit early (to try again).

  if (temp.test_counter(20)  || temp.test_value(1, &h, 0.5) || temp.test_value(2, &t, 0.5)) {
    transport.set_values(1, (t*100));
    transport.set_values(2, (h*100));
    transport.send_values('A');
  }
}
void ft_send() {
  float sensorValue = analogRead(FTPIN);
  sensorValue = ((1024-sensorValue) / 1024) * 100;
  
  transport.set_values(1, sensorValue);
 // transport.send_values('B');
}
void sonic_send() {
  float uS = sonar.ping_cm();
  
  transport.set_values(1, uS);
  //transport.send_values('C');
}

int freeRam () {
   extern int __heap_start, *__brkval; 
   int v; 
   return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void setup() {
  Serial.begin(9600);
  Serial.println("zuno dht node v2");
  dht.begin();
  
  delay(2000);
  runner.startNow();
}

void loop() {
  //Serial.println(freeRam());
  runner.execute();
}
