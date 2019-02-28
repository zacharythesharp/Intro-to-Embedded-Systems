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

// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
char led_smclk;

// Initialized Globals
volatile unsigned int five_msec_count = INITIAL_COUNT; // starts at 0
volatile int display_change = DISPLAY_CHANGE_FALSE;    // int for false (0)

// Globals used for LCD text display
extern char display_line_1[TEXT_LENGTH];
extern char display_line_2[TEXT_LENGTH];
extern char display_line_3[TEXT_LENGTH];
extern char display_line_4[TEXT_LENGTH];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;

int volatile SW1_pressed = FALSE;
int volatile SW2_pressed = FALSE;
// -----------------------------------------------------------------------------
// transmit receive globals
int index = INITIAL;
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

int volatile baudrate = INITIAL;
// -----------------------------------------------------------------------------

char adc_char[BASE_ARRAY_SIZE];    // holds thumb wheel value data
char L_char[BASE_ARRAY_SIZE];      // holds left detector value data
char R_char[BASE_ARRAY_SIZE];      // holds right detector value data

extern unsigned volatile int ADC_Thumb; // A3 Channel
extern unsigned volatile int L_Detect;  // A1 Channel
extern unsigned volatile int R_Detect;  // A0 Channel

extern int menu_case;

// Line following globals
unsigned int L_White = INITIAL;     // low values
unsigned int L_Black = INITIAL;     // high values
unsigned int R_White = INITIAL;     // low values
unsigned int R_Black = INITIAL;     // high values

// Project 7 Globals
unsigned int sent_number = INITIAL;
unsigned int rec_number = INITIAL;
int ready = FALSE;                  // ready to transmit
int first_bit = TRUE;               // receiving upper_bit value

// Project 8 Globals
int pc_communication = FALSE;
char command[FIFTY];
char pc_command[FIFTY];
int move_command = FALSE;
int pc_sent_command = FALSE;
int sent_command = FALSE;
int IOT_Echo = FALSE;
char parsing[ONE_HUN];  // for Scanning, SSID, and IP
int parsing_bool = FALSE;

// P9 Globals
int left_black;
int right_black;
int left_white;
int right_white;
int left_avg;
int right_avg;
int find_line = FALSE;
int follow_line = FALSE;
extern int volatile Iot_Reset_Flag;
extern int volatile IP_Display_Flag;
extern char ip_string_1[NINE];
extern char ip_string_2[NINE];

//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
// Macros:  
//   ALWAYS                       (1) // Integer value for true
//   DELAY                       (50) // time delay 50ms
//   OFFSET_0                     (0) // LCD screen offset 0
//   OFFSET_2                     (2) // LCD screen offset 2
//   OFFSET_3                     (3) // LCD screen offset 3
//   OFFSET_4                     (4) // LCD screen offset 4
//
//------------------------------------------------------------------------------
void main()
{
  
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System
  Init_Conditions();                        //
  Init_Timers();                            // Initialize Timers
  Five_msec_Delay(DELAY);                   // DELAY = 50 --> 250ms
  Init_LCD();                               // Initialize LCD
  Init_ADC();                               // Initialize ADC criteria
  Init_Serial_UCA0();                       // Initialize serial port A0
  Init_Serial_UCA1();                       // Initialize serial port A1
  PJOUT |= IOT_RESET;

// Sets initial display
  display_1 = ip_string_1;
  posL1 = OFFSET_0;
  display_2 = ip_string_2;
  posL2 = OFFSET_0;
  display_3 = L_char;
  posL3 = OFFSET_0;
  display_4 = R_char;
  posL4 = OFFSET_0;
  Display_Process();
    
// begins the Detector ADC interrupt sequence that continuously runs
  ADC_Process();   
  
// initialize command array
  command[INITIAL] = INITIAL;
  pc_command[INITIAL] = INITIAL;
  parsing[INITIAL] = INITIAL;  // for Scanning, SSID, and IP

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------ 
  int command_index = INITIAL; // index for commands
  int pc_command_index = INITIAL;
  int parsing_index = INITIAL;
  
  while(ALWAYS)                                 // Can the Operating system run
  {     
    // Detector Values stuff
   HEXtoBCD(R_Detect, L_char);         // convert value
   HEXtoBCD(L_Detect, R_char);         // convert value
    
    // iot reset parameter
    if (Iot_Reset_Flag)
    {
      Iot_Reset_Flag = FALSE;
      PJOUT &=~ IOT_RESET;
      Five_msec_Delay(TEN);
      PJOUT |= IOT_RESET; 
      string_transmit_A0("HW Reset");
    }
    
    // IP redisplay parameter
    if (IP_Display_Flag)
    {
      IP_Display_Flag = FALSE;
      string_transmit_A1_now("AT+S.STS=ip_ipaddr\x0D"); // get ip address
    }
    
    // -------------------------------------------------------------------------
    //char USB_Char_Rx[SMALL_RING_SIZE];
    //char USB_Char_Tx[LARGE_RING_SIZE];
    //char USB_Char_Rx_A1[SMALL_RING_SIZE];
    //char USB_Char_Tx_A1[LARGE_RING_SIZE];
    // -------------------------------------------------------------------------
    // A0 reception
    
    int read_rx0 = usb_rx_ring_rd;               // used in the following if to avoid volatile warning
    int write_rx0 = usb_rx_ring_wr;
    if (read_rx0 != write_rx0) 
    {
      pc_communication = TRUE;
      char received_byte = USB_Char_Rx[usb_rx_ring_rd];
      add_byte_A0(received_byte);
      
      if (received_byte != '\x0D')  // add character to command array if not new line
      {
        command[command_index] = received_byte;
        command_index++;
        command[command_index] = INITIAL;  // sets last index value = to null terminator
      }
      
      if (received_byte == '\x0D')  // handles new lines with enter
      {
        add_byte_A0('\n');
        sent_command = TRUE;
      }
      
      if(++usb_rx_ring_rd >= SMALL_RING_SIZE)          // go back to the beginning of ring
      {
        usb_rx_ring_rd = INITIAL;           
      }
    }
    // -------------------------------------------------------------------------
    if (sent_command)
    {
      command_index = INITIAL;     // reset command index
      sent_command = FALSE;
      int choice = process_string(command);
      commands(choice);
      command[INITIAL] = INITIAL;  // resets command string
    }
    // -------------------------------------------------------------------------
    
    // A0 transmission
    int read_tx0 = usb_tx_ring_rd;
    int write_tx0 = usb_tx_ring_wr;
    if (read_tx0 != write_tx0 && pc_communication)
    {
      while(!(UCTXIFG & UCA0IFG));  
      UCA0TXBUF = USB_Char_Tx[usb_tx_ring_rd];
      
      if(++usb_tx_ring_rd >= SMALL_RING_SIZE)          // go back to the beginning of ring
      {
        usb_tx_ring_rd = INITIAL;           
      }
    }
    
    // A1 reception
    int read_rx1 = usb_rx_ring_rd_A1;
    int write_rx1 = usb_rx_ring_wr_A1;
    if (read_rx1 != write_rx1) 
    { 
      pc_communication = TRUE;
      char received_byte = USB_Char_Rx_A1[usb_rx_ring_rd_A1];
      
       if (IOT_Echo)
      {
        add_byte_A0_now(received_byte);
      }
      
      // for parsing
      if (received_byte != '\x0D' && received_byte != '\n') {
        parsing[parsing_index] = received_byte;
        parsing_index++;
        parsing[parsing_index] = INITIAL;
      }
      if (received_byte == '\x0D') {
        // parsing_bool = TRUE;
        display_ip(parsing);
        parsing_index = INITIAL;
        parsing[INITIAL] = INITIAL; 
      }
      
      
      //-----------------------------------
      if(received_byte == '_') {
        pc_sent_command = TRUE;
      }
      
      if(pc_sent_command) {
        pc_command[pc_command_index] = received_byte;
        pc_command_index++;
        pc_command[pc_command_index] = INITIAL;
      }
      //---------------------------------------
      if (received_byte == '\x0D') {
        move_command = TRUE;
      }
      
      if(++usb_rx_ring_rd_A1 >= SMALL_RING_SIZE)          // go back to the beginning of ring
      {
        usb_rx_ring_rd_A1 = INITIAL;           
      }
    }
    //------------
    if (move_command) {
      pc_command_index = INITIAL;     // reset command index
      move_command = FALSE;
      pc_sent_command = FALSE;
      
      int choice = process_string(pc_command);
      // commands(choice);
      pc_command[INITIAL] = INITIAL;  // resets command string
    }
    
    
    //------------
    // A1 transmission
    int read_tx1 = usb_tx_ring_rd_A1;
    int write_tx1 = usb_tx_ring_wr_A1;
    if (read_tx1 != write_tx1 && pc_communication)
    {
      while(!(UCTXIFG & UCA1IFG));  
      UCA1TXBUF = USB_Char_Tx_A1[usb_tx_ring_rd_A1];
      
      if(++usb_tx_ring_rd_A1 >= SMALL_RING_SIZE)          // go back to the beginning of ring
      {
        usb_tx_ring_rd_A1 = INITIAL;           
      }
    }
   
    // -------------------------------------------------------------------------
    // Switch 1 Pressed, sets the dark values
    if (SW1_pressed)                            
    {
      left_black = L_Detect;
      right_black = R_Detect;
      SW1_pressed = FALSE;
    }
      
    // Switch 2 Pressed, sets the light values
    if (SW2_pressed)                            
    {
      left_white = L_Detect;
      right_white = R_Detect;
      SW2_pressed = FALSE;
    } 
    // -------------------------------------------------------------------------
    // motion conditionals for all movement
    // TB1CCR1 // right forward
    // TB2CCR1 // right reverse
    // TB1CCR2 // left forward
    // TB2CCR2 // left reverse
    if (find_line) {
      TB1CCR1 = ONE_K;
      TB1CCR2 = ONE_K;
      
      if (L_Detect > left_avg || R_Detect > right_avg)
      {
        TB1CCR1 = PWM_00_PRC;
        TB1CCR2 = PWM_00_PRC;
        find_line = FALSE;
        follow_line = TRUE;
      }
    }
    if (follow_line) {
    
      if(L_Detect > left_avg && R_Detect > right_avg) {
        TB1CCR1 = PWM_00_PRC;
        TB1CCR2 = PWM_00_PRC;
        
        TB1CCR1 = PWM_60_PRC;
        TB1CCR2 = PWM_60_PRC;
      }
      
      if(L_Detect > left_avg && R_Detect < right_avg) {
        TB1CCR1 = PWM_00_PRC;
        TB1CCR2 = PWM_00_PRC;
        
        TB1CCR1 = PWM_60_PRC;
      }
      
      if(L_Detect < left_avg && R_Detect > right_avg) {
        TB1CCR1 = PWM_00_PRC;
        TB1CCR2 = PWM_00_PRC;
        
        TB1CCR2 = PWM_60_PRC;
      }
      
    }
    // -------------------------------------------------------------------------
    if (display_change)
    {
      Display_Process();
      // Five_msec_Delay(DELAY / MULTIPLY_2);  // short delay
      display_change = DISPLAY_CHANGE_FALSE;   // set display change back to false
    } 
  }
}



