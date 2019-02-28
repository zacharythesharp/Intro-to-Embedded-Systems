//------------------------------------------------------------------------------
//  Description: This file contains the command executions
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

char c_zero[EIGHT] = "Invalid";
char c_one[NINE] = "I'm here";
char c_two[EIGHT] = "115,200";
char c_three[SIX] = "9,600";
char c_four_a[TWELVE] = "A1 to A0 ON";
char c_four_b[TWELVE] = "A1to A0 OFF";
extern int sent_command;
extern int volatile baudrate;
extern int IOT_Echo;
extern int find_line;
extern int left_black;
extern int right_black;
extern int left_white;
extern int right_white;
extern int left_avg;
extern int right_avg;

void commands(int choice)
{
  switch(choice) {
  case CASE_0: // invalid
    string_transmit_A0(c_zero);
    break;
  
  case CASE_1: // ..
    string_transmit_A0(c_one);
    break;
    
  case CASE_2: // .F
    baudrate = TRUE; // not initial, set to 115200
    //Init_Serial_UCA0();
    Init_Serial_UCA1();
    
    string_transmit_A0(c_two);
    break;
    
  case CASE_3: // .S
    baudrate = INITIAL; // initial, set to 9600
    Init_Serial_UCA0();
    Init_Serial_UCA1();
    
    add_byte_A0('\n');
    add_byte_A0('\x0D');
    
    string_transmit_A0(c_three);
    break;
    
  case CASE_4: // .I
    if (IOT_Echo) {
      IOT_Echo = FALSE;
      string_transmit_A0(c_four_b);  // echo off
    }
    
    else {
      IOT_Echo = TRUE;
      string_transmit_A0(c_four_a);  // echo on
    }
    break;
    
  case CASE_5: // sets IOT baud rate to 9600, .Q
    string_transmit_A1_now("AT+S.SCFG=console1_speed,9600\x0D");
    Five_msec_Delay(TWO*ONE_SEC_DELAY);
    string_transmit_A0("IOT @ 9600");
    
    break;
    
  case CASE_6: // .W , saves
    string_transmit_A1_now("AT&W\x0D");
    Five_msec_Delay(ONE_SEC_DELAY);
    string_transmit_A0("IOT Saved");
    Five_msec_Delay(TEN);
    break;
    
  case CASE_7: // .E , resets the OS
    string_transmit_A1_now("AT+CFUN=1\x0D");
    string_transmit_A0("OS Reset");
    Five_msec_Delay(TEN);
    break;
    
  case CASE_8: // .R , resets the hardware
    PJOUT &=~ IOT_RESET;
    Five_msec_Delay(TEN);
    PJOUT |= IOT_RESET;
    string_transmit_A0("HW Reset");
    break;
    
  case CASE_9: // .T , get mac address
    string_transmit_A1_now("AT+S.GCFG=nv_wifi_macaddr\x0D");
    break;
    
  case CASE_10: // .Y , 
    string_transmit_A1_now("AT+S.SSIDTXT=ncsu\x0D"); // set the ssid
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SSIDTXT\x0D"); // get the SSID
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SCFG=ip_hostname,ECE-306_15_D\x0D"); // set host name
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.GCFG=ip_hostname\x0D"); // get host name
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SCFG=wifi_priv_mode,0\x0D"); // set network privacy
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.GCFG=wifi_priv_mode\x0D"); // get network privacy
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SCFG=wifi_mode,1\x0D"); // set the network mode 1 = STA
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.GCFG=wifi_mode\x0D"); // get network mode
    Five_msec_Delay(TEN);
    string_transmit_A1_now("AT&W\x0D"); // save on flash memory
    Five_msec_Delay(TEN);
    string_transmit_A1_now("AT+CFUN=1\x0D"); // reset module
    Five_msec_Delay(TEN);
    // hardware reset time
    PJOUT &=~ IOT_RESET;
    Five_msec_Delay(TEN);
    PJOUT |= IOT_RESET;
    break;
    
  case CASE_11: // IN
    string_transmit_A1_now("AT+S.STS\x0D"); // display system info
    break;
    
  case CASE_12: // CL for phone hot spot connectivity
    string_transmit_A1_now("AT+S.SSIDTXT=danielo\x0D"); // set the ssid
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SSIDTXT\x0D"); // get the SSID
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SCFG=ip_hostname,ECE-306_15_D\x0D"); // set host name
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.GCFG=ip_hostname\x0D"); // get host name
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SCFG=wifi_priv_mode,2\x0D"); // set network privacy
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.GCFG=wifi_priv_mode\x0D"); // get network privacy
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.SCFG=wifi_mode,1\x0D"); // set the network mode 1 = STA
    Five_msec_Delay(FIVE);
    string_transmit_A1_now("AT+S.GCFG=wifi_mode\x0D"); // get network mode
    Five_msec_Delay(TEN);
    string_transmit_A1_now("AT+S.SCFG=wifi_wpa_psk_text,weirdingway\x0D");
    Five_msec_Delay(TEN);
    string_transmit_A1_now("AT&W\x0D"); // save on flash memory
    Five_msec_Delay(TEN);
    string_transmit_A1_now("AT+CFUN=1\x0D"); // reset module
    Five_msec_Delay(TEN);
    // hardware reset time
    PJOUT &=~ IOT_RESET;
    Five_msec_Delay(TEN);
    PJOUT |= IOT_RESET;
    break;
    
  case CASE_13: // displaying the IP address
    string_transmit_A1_now("AT+S.STS=ip_ipaddr\x0D"); // get ip address
  break;
  
  case CASE_14: // GO, find line function in main = true
    find_line = TRUE;  
    left_avg = PWM_40_PRC;//(left_black + left_white) / TWO;
    right_avg = PWM_40_PRC;//(right_black + right_white) / TWO;
  break;
   
  default:
    break;
  } // end switch

  sent_command = FALSE;
}