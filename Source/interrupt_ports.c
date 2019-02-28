//------------------------------------------------------------------------------
// Description: Contains the SWITCH interrupts and firing mechanics
//
// Zachary Sharp
// Sept 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

// Global variables externed from interrupt_timers.c and main.c
extern int volatile switch1_debounce_count;
extern int volatile switch1_debounce_enabled;
extern int volatile switch2_debounce_count;
extern int volatile switch2_debounce_enabled;

extern int volatile SW1_pressed;
extern int volatile SW2_pressed;

extern volatile int display_change;
extern char *display_1;
extern char posL1;

//------------------------------------------------------------------------------
// Port 4 interrupt. For switches, they are disabled for the duration
// of the debounce timer. Flag is set that user space can check.
//
// Macros:
//   INITIAL_COUNT                          (0) // initial counter value of 0
//   DEBOUNCE_TRUE                          (1) // int value of true
//   OFFSET_0                               (0) // LCD screen offset of 0
//   DISPLAY_CHANGE_TRUE                    (1) // int value of true
//------------------------------------------------------------------------------
#pragma vector = PORT4_VECTOR
__interrupt void switch_interrupt(void)
{
  //-------------------
  // turn off backlight
  // P1OUT &=~ LCD_BACKLIGHT; 
  
  //------------------
  // Switch 1 Handling
  if (P4IFG & SW1) 
  {
    switch1_debounce_count = INITIAL_COUNT;   // sets counter back to 0
    switch1_debounce_enabled = DEBOUNCE_TRUE; // shows that the switch is debouncing
    
    TA0CCTL0 |= CCIE;                         // enable 50ms timer interrupt
    P4IE &=~ SW1;                             // disables SW1 interrupt
    P4IFG &=~ SW1;                            // IFG SW1 cleared
    
    SW1_pressed = TRUE;                       // switch 1 has been pressed
  }
  
  //-----------------
  //Switch 2 Handling
  if (P4IFG & SW2)
  {
    switch2_debounce_count = INITIAL_COUNT;   // sets counter back to 0
    switch2_debounce_enabled = DEBOUNCE_TRUE; // shows that the switch is debouncing
   
    TA0CCTL0 |= CCIE;                         // enable 50ms timer interrupt
    P4IE &=~ SW2;                             // disables SW2 interrupt
    P4IFG &=~ SW2;                            // IFG SW2 cleared
    
    SW2_pressed = TRUE;                       // switch 2 has been pressed
  }
}
