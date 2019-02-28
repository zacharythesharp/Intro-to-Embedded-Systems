//------------------------------------------------------------------------------
//  Description: This file contains the Main Routine - "While" Operating System
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

// -----------------------------------------------------------------------------
char ip_string_1[NINE];
char ip_string_2[NINE];

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
// transmit receive globals
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;

extern volatile unsigned int usb_rx_ring_wr_A1;
extern volatile unsigned int usb_rx_ring_rd_A1;
extern volatile unsigned int usb_tx_ring_wr_A1;
extern volatile unsigned int usb_tx_ring_rd_A1;

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[LARGE_RING_SIZE];
extern volatile char USB_Char_Rx_A1[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx_A1[LARGE_RING_SIZE];
// -----------------------------------------------------------------------------

void add_byte_A0(char c)
{
  USB_Char_Tx[usb_tx_ring_wr++] = c;
  if(usb_tx_ring_wr >= SMALL_RING_SIZE) 
  {
    usb_tx_ring_wr = INITIAL; 
  }
}

void add_byte_A1(char c)
{
  USB_Char_Tx_A1[usb_tx_ring_wr_A1++] = c;
  if(usb_tx_ring_wr_A1 >= SMALL_RING_SIZE) 
  {
    usb_tx_ring_wr_A1 = INITIAL; 
  }
}

void string_transmit_A0(char *array)
{
  while(*array != '\0')
  {
    add_byte_A0(*array);
    array++;
  }
  add_byte_A0('\n');
  add_byte_A0('\x0D');
}

void string_transmit_A1(char *array)
{
  while(*array != '\0')
  {
    add_byte_A1(*array);
    array++;
  }

}

void add_byte_A0_now(char c)
{
  while(!(UCTXIFG & UCA0IFG));
  UCA0TXBUF = c;
}

void add_byte_A1_now(char c)
{
  while(!(UCTXIFG & UCA1IFG));
  UCA1TXBUF = c;
}

void string_transmit_A0_now(char *array)
{
  while(*array != '\0')
  {
    add_byte_A0_now(*array);
    array++;
  }
  add_byte_A0('\n');
  add_byte_A0('\x0D');
}

void string_transmit_A1_now(char *array)
{
  while(*array != '\0')
  {
    add_byte_A1_now(*array);
    array++;
  }
}

//# ip_ipaddr = ???.???.???.???
void display_ip(char *a) // gets and updates the IP address and puts it on the display
{
  int Display_ip_bool = FALSE;
  
  if (/*a[ZERO] == '#' &&*/ a[THREE] == 'i' && a[FOUR] == 'p') {
    Display_ip_bool = TRUE;
  }
  
  if (Display_ip_bool) {
    Display_ip_bool = FALSE;
    Five_msec_Delay(SHORT_DELAY);
  
    for (int i = ZERO; i <= SEVEN; i++) {
      ip_string_1[i] = a[i+FIFTEEN];
    }
    ip_string_1[EIGHT] = ZERO;
  
    for (int i = ZERO; i <= SEVEN; i++) {
      ip_string_2[i] = a[i+TWENTY_3];
    }
    ip_string_2[EIGHT] = ZERO;
  
    display_1 = ip_string_1;
    display_2 = ip_string_2;
  
    Display_Process();
  }
}
