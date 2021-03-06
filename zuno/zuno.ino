
#include "zunoserial.h"

ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE);
ZUNO_SETUP_CHANNELS(ZUNO_SENSOR_MULTILEVEL_TEMPERATURE(getterTemperature),ZUNO_SENSOR_MULTILEVEL_HUMIDITY(getterHum),ZUNO_SENSOR_MULTILEVEL_MOISTURE(getterFt),ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_DISTANCE, SENSOR_MULTILEVEL_SCALE_PERCENTAGE_VALUE, SENSOR_MULTILEVEL_SIZE_ONE_BYTE, SENSOR_MULTILEVEL_PRECISION_ZERO_DECIMALS, getterUs));

//global values from input
byte lastTemperatureValue = 256;
byte lastHumValue = 256;
byte lastFtValue = 256;
byte lastUsValue = 256;

//ZUNOSERIAL serialcom(message_use);
ZUNOSERIAL serialcom;


void setup() {
  //serialcom.setCallback(message_use);
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  if (serialcom.read()) {
    message_use();
  }
}

void message_use() {

  char * opts = serialcom.get_option_ptr();
  double * vars = serialcom.get_values_ptr();
    
  if (*opts == 'A') {
    lastTemperatureValue = (*(vars+0)/100) + 256;
    lastHumValue = (*(vars+1)/100) + 256;
  }
  if (*opts == 'B') {
    lastFtValue = *(vars+0) + 256;
  }
  if (*opts == 'C') {
    lastUsValue = *(vars+0) + 256;
  }
}

byte getterTemperature(void) {
  return lastTemperatureValue;
}
byte getterHum(void) {
  return lastHumValue;
}
byte getterFt(void) {
  return lastFtValue;
}
byte getterUs(void) {
  return lastUsValue;
}



