/* ZUNO Communication with arduino
Daniel Boeber
*/

#include "zunoserial.h"

/*
ZUNOSERIAL::ZUNOSERIAL(void (*cb)(char * opt, double * var)) {
  Serial.begin(9600);
  _cb = NULL;
  _cb = cb;
}
*/

ZUNOSERIAL::ZUNOSERIAL() {
  Serial2.begin(9600);
}

bool ZUNOSERIAL::read(void) {
  while (Serial2.available()) {
    inChar = Serial2.read();
    if (Message == false && inChar == '%') {
      Message = true;
      counter = 0;
      continue;
    }
    if (Message == true) {
      if (inChar == '&') {
        Message = false;
        string_decode(_string, _values, &_option);
        string_clear();
        //_cb(&_option, _values);   
        return true;
        //continue;
      }
      _string[counter] = inChar;
      counter ++; 
    }
  }
}

char* ZUNOSERIAL::get_option_ptr() {
  return &_option;
}

double* ZUNOSERIAL::get_values_ptr() {
  return _values;
}

int ZUNOSERIAL::a2i(const char *s) {
  int sign=1;
  if(*s == '-'){
    sign = -1;
    s++;
  }
  int num=0;
  while(*s){
    num=((*s)-'0')+num*10;
    s++;   
  }
  return num*sign;
}

void ZUNOSERIAL::string_decode(char * input, double * output, char * option_var) {
  char str_value[20];
  int strings_count;
  int value_count;
  int str_length = strlen(input);
  
  for (int j=0;j<19;j++){
    str_value[j] = 0;
  }
  for (int i = 0;i<=str_length;i++) {
    if (i == 0) {
      *option_var = *(input+i);
      strings_count = 0;
      value_count = 0;
      continue;
    }  
    if (i == 1) {
      //prüfung ob auswahl gesetzt (1. stelle)
      //diese stelle sollte ein ":" sein, else return false?
      continue;
    }
    if ((*(input+i)) == ':' || i == str_length){
      strings_count = 0;
      *(output+value_count) = a2i(str_value);
      for (int j=0;j<19;j++){
        str_value[j] = 0;
      }
      value_count++;
    } else {   
      str_value[strings_count] = *(input+i);
      strings_count++;
    }  
  }
}

void ZUNOSERIAL::string_clear(void) {
  for (int j=0;j<32;j++){
    _string[j] = 0;
  }
}

