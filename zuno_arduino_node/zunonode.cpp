/*  ZUNO Communication with arduino
 *  Daniel Boeber
 */

#include "zunonode.h"

ZUNONODE::ZUNONODE() {
  
  _inString = "";
  _values_count = sizeof(_values) / sizeof(float);
  
}

void ZUNONODE::set_values(int pos, float value) {
  
  int index = pos;
  
  if (index > 4) {
    index = 4;    
  }
  if (index < 1) {
    index = 1;    
  }
  _values[index-1] = value;
  
}

void ZUNONODE::send_values(char funktion) {
    
  _inString += "%";
  _inString += funktion;
  _inString += ":";
  
  for (int i=0;i<_values_count;i++) {
    if (_values[i] > 0) {
      _inString += (int) _values[i];
      _inString += ":";
      _values[i] = 0;
    }
  }
  
  _inString += "&";
  
  Serial.print(_inString);
  
  _inString = "";
  for (int j=0;j<_values_count;j++){
    _values[j] = 0;
  }
  
}
void ZUNONODE::clear_values(void) {
  
  for (int j=0;j<_values_count;j++){
    _values[j] = 0;
  }
  
}

SENSOR::SENSOR(void) {

  _number_of_values = 4;
  
  _counter_tests = 0;
  for (int i = 0; i < 4; i++) {
    _old_values[i] = 0;
  }
}

bool SENSOR::test_value(int value_index, float * value, float dif) {
  //Serial.println(sizeof(_old_values));
  if (value_index > _number_of_values) {
    value_index = _number_of_values;
  }
  
  if (*value > _old_values[value_index-1] + dif || *value < _old_values[value_index-1] - dif) {
    _old_values[value_index-1] = *value;
    _counter_tests = 0;
    return true;
  } else {
    return false;
  }
  
}

bool SENSOR::test_counter(int tests) {
  
  if (_counter_tests > tests) {
    _counter_tests = 0;
    return true;
  } else {
    _counter_tests++;
    return false;
  }
   
}

