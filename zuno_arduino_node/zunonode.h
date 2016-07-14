/* ZUNO Communication with arduino
Daniel Boeber
*/

#ifndef ZUNO_NODE_H
#define ZUNO_NODE_H

#include "Arduino.h"

typedef void (*event_cb_t)(char opt, double * var);

class ZUNONODE {
  
  public:
  
    ZUNONODE();
    void send_values(char funktion); //send command und float values an zuno via serial-string
    void set_values(int pos, float value);
    void clear_values(void);
    
  private:
  
    String _inString = "";    // string to hold input
    float _values[4] = {0,0,0,0};
    int _values_count;
        
};

class SENSOR {
  
  public:
  
    SENSOR(void);
    bool test_value(int value_index, float * value, float dif); //returns true if value changes to dif
    bool test_counter(int tests = 100); //returns true if runs number of tests
    
  private:

    int _number_of_values;
    int _counter_tests;
    float _old_values[4];
        
};

#endif
