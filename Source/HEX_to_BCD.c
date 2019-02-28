//------------------------------------------------------------------------------
// Description: HEX to BCD Conversion
//
// Zachary Sharp
// Oct 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile int display_change;

//------------------------------------------------------------------------------ 


void HEXtoBCD(int hex_value, char *buffer){

  int value;
  buffer[INDEX_0] = '0';
  buffer[INDEX_1] = '0';
  buffer[INDEX_2] = '0';
  if (hex_value > LIMIT_1000){
    hex_value = hex_value - INCREMENT_1000;
    buffer[INDEX_0] = '1';
  }
  value = BASE_0;
  while (hex_value > LIMIT_99){
    hex_value = hex_value - INCREMENT_100;
    value = value + INCREMENT_1;
    buffer[INDEX_1] = CONVERSION + value;
  }
  value = BASE_0;
  while (hex_value > LIMIT_9){
    hex_value = hex_value - INCREMENT_10; 
    value = value + INCREMENT_1; 
    buffer[INDEX_2] = CONVERSION + value;

}

  buffer[INDEX_3] = CONVERSION + hex_value;
  
  // display_change = DISPLAY_CHANGE_TRUE;
}
//******************************************************************************

void betterHEXtoBCD(unsigned int hex_value, char* buffer)
{
  buffer[HEX_SIZE_5] = '\0'; // NULL TERMINATOR
  
  for(int i = INITIAL; i < HEX_SIZE_5; i++)
  {
    buffer[i] = '0';
  }
  
  unsigned int j = INITIAL;
  while(hex_value >= TEN_K)
  {
    buffer[j]++;
    hex_value -= TEN_K;
  }
  j++;
  
  while(hex_value >= ONE_K)
  {
    buffer[j]++;
    hex_value -= ONE_K;
  }
  j++;
  
  while(hex_value >= ONE_HUN)
  {
    buffer[j]++;
    hex_value -= ONE_HUN;
  }
  j++;
  
  while(hex_value >= ONE_TEN)
  {
    buffer[j]++;
    hex_value -= ONE_TEN;
  }
  j++;
  
  while(hex_value >= ONE)
  {
    buffer[j]++;
    hex_value -= ONE;
  }
}

//------------------------------------------------------------------------------