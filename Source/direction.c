//------------------------------------------------------------------------------
//  Description: Contains the directional funcioning commands
//
//  Updated by Zach Sharp
//  Nov 2016
//  Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern char display_line_1[TEXT_LENGTH];
extern char display_line_2[TEXT_LENGTH];
extern char display_line_3[TEXT_LENGTH];
extern char display_line_4[TEXT_LENGTH];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

// TB1CCR1 // right forward
// TB2CCR1 // right reverse
// TB1CCR2 // left forward
// TB2CCR2 // left reverse

void move_F(int time) { // forward
  
  TB1CCR1 = ONE_K;// right forward
  TB1CCR2 = ONE_K;// left forward
    
  Five_msec_Delay(time*HALF_SEC_DELAY * TWO);
    
  TB1CCR1 = PWM_00_PRC;// right forward
  TB1CCR2 = PWM_00_PRC;// left forward
}

void move_B(int time) { // back
    
  TB2CCR1 = PWM_70_PRC;// right backward
  TB2CCR2 = PWM_70_PRC;// left backward
    
  Five_msec_Delay(time*HALF_SEC_DELAY * TWO);
    
  TB2CCR1 = PWM_00_PRC;
  TB2CCR2 = PWM_00_PRC;
}

void move_R(int time) { // right

  TB2CCR1 = ONE_K;// right backward
  TB1CCR2 = ONE_K;// left forward
    
  Five_msec_Delay(time*HALF_SEC_DELAY / TWO);
    
  TB2CCR1 = PWM_00_PRC;
  TB1CCR2 = PWM_00_PRC;
}

void move_L(int time) { // left

  TB1CCR1 = PWM_70_PRC;// right forward
  TB2CCR2 = PWM_70_PRC;// left back
    
  Five_msec_Delay(time*HALF_SEC_DELAY / TWO);
    
  TB1CCR1 = PWM_00_PRC;
  TB2CCR2 = PWM_00_PRC;
}

int char_to_int(char c) {
  
  if (c == '1') return ONE;
  else if (c == '2') return TWO;
  else if (c == '3') return THREE;
  else if (c == '4') return FOUR;
  else if (c == '5') return FIVE;
  else if (c == '6') return SIX;
  else if (c == '7') return SEVEN;
  else if (c == '8') return EIGHT;
  else return NINE;
  
  
}