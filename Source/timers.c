//------------------------------------------------------------------------------
// Description: designated timer functions and processes 
//              with interrupt implementations
//
// Zachary Sharp
// Sept 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Global Variables externed in main
extern volatile unsigned int five_msec_count;
unsigned int right_reverse_rate;
unsigned int right_forward_rate;
unsigned int left_reverse_rate;
unsigned int left_forward_rate;

//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
void Init_Timers()
{
    Init_Timer_A0(); //
    Init_Timer_A1(); //
//  Init_Timer_B0(); //
    Init_Timer_B1(); //
    Init_Timer_B2(); //  
}

//------------------------------------------------------------------------------
// timer A0 initialization sets up both A0_0 and A0_1 - A0_2
// Arguments:
//   NONE
// Macros:
//
//------------------------------------------------------------------------------
void Init_Timer_A0()
{
  TA0CTL = TASSEL__SMCLK;            // SMCLK source
  TA0CTL |= TACLR;                   // resets TA0R, clock divider, count direction
  TA0CTL |= MC__CONTINOUS;           // continuous up
  TA0CTL |= ID__4;                   // divide clock by 4
  TA0CTL &= ~TAIE;                   // disable overflow interrupt 
  TA0CTL &= ~TAIFG;                  // clear overflow interrupt flag
  
  TA0EX0 = TAIDEX_7;                 // divide clock by additional 8
  
  TA0CCR0 = TA0CCR0_INTERVAL;        // CCR0 
  TA0CCTL0 &=~ CCIE;                 // CCR0 disable interrupt
  
  TA0CCR1 = TA0CCR1_INTERVAL;        // CCR1
  TA0CCTL1 &=~ CCIE;                 // CCR1 disable interrupt

  // TA0CCR2 = TA0CCR2_INTERVAL;     // CCR2
  // TA0CCTL2 |= CCIE;               // CCR2 enable interrupt
}

// Timers used for resetting internet and updating display IP
void Init_Timer_A1()
{
  TA1CTL = TASSEL__SMCLK;            // SMCLK source
  TA1CTL |= TACLR;                   // resets TA0R, clock divider, count direction
  TA1CTL |= MC__CONTINOUS;           // continuous up
  TA1CTL |= ID__8;                   // divide clock by 8
  TA1CTL &= ~TAIE;                   // disable overflow interrupt 
  TA1CTL &= ~TAIFG;                  // clear overflow interrupt flag
  
  TA1EX0 = TAIDEX_7;                 // divide clock by additional 8
  
  // TIMER FOR HARDWARE RESET
  TA1CCR0 = TA0CCR0_INTERVAL;                   // CCR0: every 100ms (using a counter method)
                                     // max counter size will = 200 = 20 seconds
  TA1CCTL0 |= CCIE;                  // CCR0 enable interrupt
  
  // TIMER FOR FEX VALUE DISPLAY UPDATE
  // TA1CCR1 = 31250;        // CCR1
  // TA1CCTL1 |= CCIE;                 // CCR1 enable interrupt

  // TA0CCR2 = TA0CCR2_INTERVAL;     // CCR2
  // TA0CCTL2 |= CCIE;               // CCR2 enable interrupt 
}

//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
//------------------------------------------------------------------------------
void Init_Timer_B1(void) 
{   

TB1CTL = TBSSEL__SMCLK;                          // SMCLK
TB1CTL |= MC_1;                                  // Up Mode
TB1CTL |= TBCLR;                                 // Clear TAR

right_forward_rate = FALSE;                      // set right forward off
right_reverse_rate = FALSE;                      // set right reverse off

TB1CCR0 = WHEEL_PERIOD;                          // PWM Period
TB1CCTL1 = OUTMOD_7;                             // CCR1 Reset/Set
TB1CCR1 = right_forward_rate;                    // P3.4 Right Forward PWM cycle
TB1CCTL2 = OUTMOD_7;                             // CCR2 Reset/Set
TB2CCR1 = right_reverse_rate;                    // P3.6 Right Reverse PWM cycle

}

//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Left Side
//------------------------------------------------------------------------------
void Init_Timer_B2(void) 
{   

TB2CTL = TBSSEL__SMCLK;                          // SMCLK
TB2CTL |= MC_1;                                  // Up Mode
TB2CTL |= TBCLR;                                 // Clear TAR

left_forward_rate = FALSE;                       // set right forward off
left_reverse_rate = FALSE;                       // set right reverse off

TB2CCR0 = WHEEL_PERIOD;                          // PWM Period
TB2CCTL1 = OUTMOD_7;                             // CCR1 Reset/Set
TB1CCR2 = left_forward_rate;                     // P3.5 Left Forward PWM cycle
TB2CCTL2 = OUTMOD_7;                             // CCR2 Reset/Set
TB2CCR2 = left_reverse_rate;                     // P3.7 Left Reverse PWM cycle

}

//------------------------------------------------------------------------------
// Five ms delay function that uses interrupts to delay
// Arguments:
//   unsigned int fivemsec - value that indicates multiple of 5 ms
//
// Macros:
//   INITIAL_COUNT                   (0) // starting counter value of zero
//------------------------------------------------------------------------------
void Five_msec_Delay(unsigned int fivemsec) 
{
  five_msec_count = INITIAL_COUNT; // zero (0)
 
  TA0CCR1 = TA0CCR1_INTERVAL + TA0R; // update the next value to fire interrupt
  TA0CCTL1 |= CCIE;      // enable interrupt
  
  while (five_msec_count < fivemsec)
  {
    // every count of five_msec_count = 5ms
  }
  TA0CCTL1 &=~ CCIE;    // disable interrupt
}
