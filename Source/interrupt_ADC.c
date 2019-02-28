//------------------------------------------------------------------------------
// Description: ADC interrupt function
//
// Zachary Sharp
// Oct 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

unsigned volatile int ADC_Thumb; // A3 Channel
unsigned volatile int L_Detect;  // A1 Channel
unsigned volatile int R_Detect;  // A0 Channel

volatile int Channel_ADC = INITIAL_CONDITION; // inner switch statement channel condition

//------------------------------------------------------------------------------ 
// ADC10 interrupt service routine   
// ADC_Right_Detector;              // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector;               // A01 ADC10INCH_1 - P1.1
// ADC_Thumb;                       // A03 ADC10INCH_3 - P1.3
// ADC_Temp;                        // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat;                         // A11 ADC10INCH_11 - Internal

#pragma vector=ADC10_VECTOR 
__interrupt void ADC10_ISR(void) {

  switch(__even_in_range(ADC10IV,CASE_12)) {

    case CASE_0:  break;            // No interrupt
    case CASE_2:  break;            // conversion result overflow
    case CASE_4:  break;            // conversion time overflow
    case CASE_6:  break;            // ADC10HI
    case CASE_8:  break;            // ADC10LO
    case CASE_10: break;            // ADC10IN
    case CASE_12: 
      
      // Need this to change the ADC10INCH_x value.
      ADC10CTL0 &=~ ADC10ENC;   // Turn off the ENC bit of the ADC10CTL0
      switch (Channel_ADC++){

      case INNER_CASE_0:
      ADC10MCTL0 = ADC10INCH_1; // Next channel A1
      R_Detect = ADC10MEM0;     // Current Channel result for A0 
      break;

      case INNER_CASE_1:
      ADC10MCTL0 = ADC10INCH_3; // Next channel A3
      L_Detect = ADC10MEM0;     // Current Channel result for A1
      break; 
      
      case INNER_CASE_2:
      ADC10MCTL0 = ADC10INCH_0; // Next channel A0
      ADC_Thumb = ADC10MEM0; // Current Channel result for A3 Channel count value needs to be set back to 0;
      Channel_ADC = INITIAL_CONDITION;
      break;
    default: break;
    }
     // Turn on the ENC bit of the ADC10CTL0
    ADC10CTL0 |= ADC10ENC + ADC10SC;  // Start next sample.
    break;

    default: break;
  } 
}

//-----------------------------------------------------------------------------