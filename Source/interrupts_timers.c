//------------------------------------------------------------------------------
// Description: Contains the TIMER interrupts and firing mechanics
//
// Zachary Sharp
// Sept 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Global variables
int volatile Iot_Reset_Counter = INITIAL;
int volatile Iot_Reset_Flag = FALSE;
int volatile IP_Display_Counter = INITIAL;
int volatile IP_Display_Flag = FALSE;
int volatile display_change_counter = INITIAL;
int volatile switch1_debounce_count = INITIAL_COUNT;     // initial count of 0
int volatile switch1_debounce_enabled = DEBOUNCE_FALSE;  // int value of false
int volatile switch2_debounce_count = INITIAL_COUNT;     // initial count of 0
int volatile switch2_debounce_enabled = DEBOUNCE_FALSE;  // int value of false
extern volatile int display_change; 

// Global Variable externed from main
extern volatile unsigned int five_msec_count;

//------------------------------------------------------------------------------
// TimerA1 Interrupts
//
// Macros:
//------------------------------------------------------------------------------
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
  
  Iot_Reset_Counter++;
  IP_Display_Counter++;
  display_change_counter++;
  if (Iot_Reset_Counter > 200)
  {
    Iot_Reset_Counter = INITIAL;
    Iot_Reset_Flag = TRUE;
  }
  if (IP_Display_Counter > 50)
  {
    IP_Display_Counter = INITIAL;
    IP_Display_Flag = TRUE;
  }
  if (display_change_counter > 3)
  {
    display_change = TRUE;
    display_change_counter = INITIAL;
  }
 
  TA1CCR0 += 12500;
}

//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
//
// Macros:
//   MAX_DEBOUNCE_COUNT                    (4) //
//   INITIAL_COUNT                         (0) //
//   DEBOUNCE_FALSE                        (0) // 
//------------------------------------------------------------------------------
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void) 
{
  //-------------------------
  // switch 1 debounce timing
  if (switch1_debounce_enabled)
  {
    switch1_debounce_count++;
    if (switch1_debounce_count == MAX_DEBOUNCE_COUNT)
    {
      switch1_debounce_enabled = DEBOUNCE_FALSE; // done debouncing
      P4IE |= SW1;                               // SW1 interrupt Enabled
      P4IFG &=~ SW1;                             // IFG SW1 cleared
    }
  }
  
  //-------------------------
  // switch 2 debounce timing
  if (switch2_debounce_enabled)
  {
    switch2_debounce_count++;
    if (switch2_debounce_count == MAX_DEBOUNCE_COUNT)
    {
      switch2_debounce_enabled = DEBOUNCE_FALSE; // done debouncing
      P4IE |= SW2;                               // SW2 interrupt Enabled
      P4IFG &=~ SW2;                             // IFG SW2 cleared
    }
  }
  
  //-------------------------------------------
  // execute once all switch debouncing is done
  if (switch1_debounce_enabled == DEBOUNCE_FALSE && switch2_debounce_enabled == DEBOUNCE_FALSE)
  {
    TA0CCTL0 &=~ CCIE;          // disable 50ms timer interrupt
    //P1OUT |= LCD_BACKLIGHT;     // turn on the backlight
  }
   
  TA0CCR0 += TA0CCR0_INTERVAL;  // Add Offset to TACCR0
}

//------------------------------------------------------------------------------
// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
//
// Macros:
//   CASE_2                                  (2) // case denoter 2
//   MAX_CASE                               (14) //
//------------------------------------------------------------------------------
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void) 
{
  switch(__even_in_range(TA0IV, MAX_CASE)) 
  {
    // case 0: break;                 // no interrupt
    case CASE_2:                           // CCR1 not used
     five_msec_count++;               // increment the 5ms counter
     TA0CCR1 += TA0CCR1_INTERVAL;     // Add Offset to TACCR1
     default: break;                  // break case  
  }
}
