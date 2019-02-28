//------------------------------------------------------------------------------
//  Description: This file contains the initialization for UCA0
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
volatile char USB_Char_Rx[SMALL_RING_SIZE]; // 16
volatile char USB_Char_Tx[LARGE_RING_SIZE]; // 32
volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
extern int volatile baudrate;

void Init_Serial_UCA0(void)
{

  int i;
  for(i=INITIAL; i<SMALL_RING_SIZE;i++) 
  {
    USB_Char_Rx[i] = CLEAR_0x;
  }  
  
  usb_rx_ring_wr = BEGINNING; 
  usb_rx_ring_rd = BEGINNING;

  for(i=INITIAL; i<LARGE_RING_SIZE; i++)
  {
    USB_Char_Tx[i] = CLEAR_0x;
  }
  
  usb_tx_ring_wr = BEGINNING; 
  usb_tx_ring_rd = BEGINNING;
  
  UCA0CTLW0 = CLEAR; // clear
  UCA0CTLW0 |= UCSSEL__SMCLK;
  UCA0CTLW0 |= UCSWRST;

  // default
  if (baudrate == INITIAL) // (baudrate == 9600)
  {
    UCA0BRW = BAUD_9600;
    UCA0MCTLW = HEX_9600;
  }
  
  else // (baudrate == 115200)
  {
    UCA0BRW = BAUD_115200; 
    UCA0MCTLW = HEX_115200; 
  }
  UCA0CTL1 &= ~UCSWRST; 
  UCA0IE |= UCRXIE; 
}