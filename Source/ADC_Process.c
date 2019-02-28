//------------------------------------------------------------------------------
// Description: 
//
// Zachary Sharp
// Oct 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void ADC_Process(void)
{
  while (ADC10CTL1 & BUSY);         // Wait if ADC10 core is active
  ADC10CTL0 |= ADC10ENC + ADC10SC;  // Start next sample.
}