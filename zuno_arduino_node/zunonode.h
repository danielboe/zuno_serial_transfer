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

#endif
