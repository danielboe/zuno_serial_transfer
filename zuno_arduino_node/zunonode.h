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

#ifndef _NODE_DEVICE
class ZUNOSERIAL {
  public:
    ZUNOSERIAL(void);
    bool read(void); //pointer to function after receive
    char* get_option_ptr();
    double* get_values_ptr();

  private:
    
    //event_cb_t _cb;
    int Message = false; //switch between new messages
    int counter = 0; //position in string array
    char inChar = 0; //char buffer serial

    char _string[32]; //serial string after decode of stop signs
    double _values[5]; //values out of serial string
    char _option; //option flag for values (which sensor)
   
    int a2i(const char *s); //atoi() implementation
    void string_decode (char * input, double * output, char * option_var);   //convert the serial string to values and option key for value selection
    void string_clear(void);
};
#endif

#endif
