//------------------------------------------------------------------------------
//  Description: This file contains the initialization for UCA1
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
volatile char USB_Char_Rx_A1[SMALL_RING_SIZE];
volatile char USB_Char_Tx_A1[LARGE_RING_SIZE];
volatile unsigned int usb_rx_ring_wr_A1;
volatile unsigned int usb_rx_ring_rd_A1;
volatile unsigned int usb_tx_ring_wr_A1;
volatile unsigned int usb_tx_ring_rd_A1;
extern int volatile baudrate;

void Init_Serial_UCA1(void)
{

  int i;
  for(i=INITIAL; i<SMALL_RING_SIZE;i++) 
  {
    USB_Char_Rx_A1[i] = CLEAR_0x;
  }  
  
  usb_rx_ring_wr_A1 = BEGINNING; 
  usb_rx_ring_rd_A1 = BEGINNING;

  for(i=INITIAL; i<LARGE_RING_SIZE; i++)
  {
    USB_Char_Tx_A1[i] = CLEAR_0x;
  }
  
  usb_tx_ring_wr_A1 = BEGINNING; 
  usb_tx_ring_rd_A1 = BEGINNING;

  UCA1CTLW0 = CLEAR; // clear
  UCA1CTLW0 |= UCSSEL__SMCLK;
  UCA1CTLW0 |= UCSWRST;
  
  // default
  if (baudrate == INITIAL) // (baudrate == 9600)
  {
    UCA1BRW = BAUD_9600; 
    UCA1MCTLW = HEX_9600;
  }
  
  else // (baudrate == 115200)
  {
    UCA1BRW = BAUD_115200;  
    UCA1MCTLW = HEX_115200; 
   }
  UCA1CTL1 &= ~UCSWRST; 
  UCA1IE |= UCRXIE;
}