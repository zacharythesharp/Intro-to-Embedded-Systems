//------------------------------------------------------------------------------
//  Description: HAndles the case processing from an input interface
//
//  Updated by Zach Sharp
//  Nov 2016
//  Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern char *display_1;
extern int volatile Iot_Reset_Counter;
extern int volatile Iot_Reset_Flag;
extern int IOT_Echo;
extern int find_line;
extern int left_black;
extern int right_black;
extern int left_white;
extern int right_white;
extern int left_avg;
extern int right_avg;
extern int follow_line;

int unlock = FALSE;
//char test[5] = "test";

int process_string(char* string)
{
  int value = INITIAL;
  // ----------------------------------------------
  
  // ..
  if (string[ZERO] == '.' && string[ONE] == '.') { 
    value = CASE_1;
  }  
    
  // .F
  else if (string[ZERO] == '.' && string[ONE] == 'F') { 
    value = CASE_2;
  }  
     
  // .S
  else if (string[ZERO] == '.' && string[ONE] == 'S') { 
    value = CASE_3;
  } 
    
  // .I
  else if (string[ZERO] == '.' && string[ONE] == 'I') {
    value = CASE_4;
  }
  
  // .Q #22
  else if (string[ZERO] == '.' && string[ONE] == 'Q') {
    value = CASE_5;
  }
  
  // .W #23
  else if (string[ZERO] == '.' && string[ONE] == 'W') {
    value = CASE_6;
  }
  
  // .E #26
  else if (string[ZERO] == '.' && string[ONE] == 'E') {
    value = CASE_7;
  }
  
  //.R #27
  else if (string[ZERO] == '.' && string[ONE] == 'R') {
    value = CASE_8;
  }
  
  // .T #28
  else if (string[ZERO] == '.' && string[ONE] == 'T') {
    value = CASE_9;
  }
  
  // .Y #33 all the internet SSID info
  else if (string[ZERO] == '.' && string[ONE] == 'Y') {
    value = CASE_10;
  }
  
  // IN
  else if (string[ZERO] == 'I' && string[ONE] == 'N') {
    value = CASE_11;
  }
  
  // CL
  else if (string[ZERO] == 'C' && string[ONE] == 'L') {
    value = CASE_12;
  }
  
  // IP
  else if (string[ZERO] == 'I' && string[ONE] == 'P') {
    value = CASE_13;
  }
  
  else if (string[ZERO] == 'G' && string[ONE] == 'O') {
    value = CASE_14;
  }
  
  // direction + # (duration)
  // ex: W2, S4, A1, D7 etc
  else if (string[ZERO] == '_') {
    unlock = TRUE;
  }
  // if unlock -----------------------------------------------------------------
  if (unlock) {
    unlock = FALSE;  
    int time = char_to_int(string[TWO]); // need to convert to an int
      
    if (string[ONE] == 'W') { // forward
      Iot_Reset_Counter = INITIAL; // resets clock counter when command is received
      move_F(time);
    }
    else if (string[ONE] == 'S') { // backward
      Iot_Reset_Counter = INITIAL; // resets clock counter when command is received
      move_B(time);
    }
    else if (string[ONE] == 'A') { // left
      Iot_Reset_Counter = INITIAL; // resets clock counter when command is received
      move_L(time);
    }
    else if (string[ONE] == 'D') { // right
      Iot_Reset_Counter = INITIAL; // resets clock counter when command is received
      move_R(time);
    }
    else if (string[ONE] == 'G') {
      Iot_Reset_Counter = INITIAL; // resets clock counter when command is received
      find_line = TRUE;  
      left_avg = (left_black + left_white) / TWO;
      right_avg = (right_black + right_white) / TWO;
    }
    else if(string[ONE] == 'H') {
      Iot_Reset_Counter = INITIAL; // resets clock counter when command is received
      find_line = FALSE;
      follow_line = FALSE;
      TB1CCR1 = PWM_00_PRC;
      TB1CCR2 = PWM_00_PRC;
    }
      
  } // end big if
  // ---------------------------------------------------------------------------
      
  return value;
}


