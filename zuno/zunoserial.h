/* ZUNO Communication with arduino
Daniel Boeber
*/

#ifndef ZUNO_SERIAL_H
#define ZUNO_SERIAL_H

#include "Arduino.h"

//typedef void (*event_cb_t)(char * opt, double * var);

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
