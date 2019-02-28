//------------------------------------------------------------------------------
//  Description: This file contains the interrupt for UCA1
//
//  Jim Carlson
//  Jan 2016
//
//  Updated by Zach Sharp
//  Nov 2016
//  Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

// Globals
extern volatile unsigned int usb_rx_ring_wr_A1;
extern volatile char USB_Char_Rx_A1[SMALL_RING_SIZE];

//------------------------------------------------------------------------------ 
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{

  unsigned int temp; 
  switch(__even_in_range(UCA1IV,CASE_8))
  {

    case CASE_0:                               // Vector 0 - No interrupt
      break;

    case CASE_2:                               // Vector 2 - RXIFG
      temp = usb_rx_ring_wr_A1;
      USB_Char_Rx_A1[temp] = UCA1RXBUF;   // RX -> USB_Char_Rx_A1 character
      
      if (++usb_rx_ring_wr_A1 >= (SMALL_RING_SIZE))
      { 
        usb_rx_ring_wr_A1 = BEGINNING;    // Circular buffer back to beginning
      }
      break;
    
    case CASE_4:                               // Vector 4 - TXIFG
      break;
      
  default: break;
  }
}