//------------------------------------------------------------------------------
// Description: contains all of the initialization functions
//
//
// Zachary Sharp
// Sept 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Global Variables
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

//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
void Init_Conditions(void)
{
// Interrupts are disabled by default, enable them.
  enable_interrupts();
  display_1 = &display_line_1[0];
  display_2 = &display_line_2[0];
  display_3 = &display_line_3[0];
  display_4 = &display_line_4[0];
}

//------------------------------------------------------------------------------
// Displays the output
//------------------------------------------------------------------------------
void Display_Process(void){

  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}

//------------------------------------------------------------------------------
// Configure ADC10_B
//------------------------------------------------------------------------------
void Init_ADC(void)
{
  ADC10CTL0 = RESET_STATE;                 // Clear ADC10CTL0
  ADC10CTL0 |= ADC10SHT_2;                 // 16 ADC clocks
  ADC10CTL0 &=~ ADC10MSC;                  // Single sequence 
  ADC10CTL0 |= ADC10ON;                    // ADC ON - Core enabled
  
  ADC10CTL1 = RESET_STATE;                 // Clear ADC10CTL1
  ADC10CTL1 |= ADC10SHS_0;                 // ADC10SC bit
  ADC10CTL1 |= ADC10SHP;                   // SAMPCON signal sourced from sampling timer
  ADC10CTL1 &=~ ADC10ISSH;                 // The sample-input signal is not inverted
  ADC10CTL1 |= ADC10DIV_0;                 // ADC10_B clock divider - Divide by 1
  ADC10CTL1 |= ADC10SSEL_0;                // MODCLK
  ADC10CTL1 |= ADC10CONSEQ_0;              // Single-channel, single conversion
  
  ADC10CTL2 = RESET_STATE;                 // Clear ADC10CTL2
  ADC10CTL2 |= ADC10DIV_0;                 // Pre-divide by 1
  ADC10CTL2 |= ADC10RES;                   // 10-bit resolution
  ADC10CTL2 &=~ ADC10DF;                   // Binary unsigned
  ADC10CTL2 &=~ ADC10SR;                   // supports up to approximately 200 ksps
  
  ADC10MCTL0 = RESET_STATE;                // Clear ADC10MCTL0
  ADC10MCTL0 |= ADC10SREF_0;               // V(R+) = AVCC and V(R-) = AVSS
  ADC10MCTL0 |= ADC10INCH_3;               // Channel A3 Thumb Wheel
  ADC10IE |= ADC10IE0;                     // Enable ADC conversion complete interrupt
}