//------------------------------------------------------------------------------
// Description: initializes all of the processor pins and ports
//
// Zachary Sharp
// Oct 2016
// Built with IAR Embedded Workbench V(6.50.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include  "msp430.h"
#include  "functions.h"

void Init_Ports() {
  Init_Port1(); 
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ();
}

void Init_Port1() {
  // --------------------------------------------------------------------------
  // Configure Port 1
  // V_DETECT_R                  (0x01) // Voltage from Right Detector
  // V_DETECT_L                  (0x02) // Voltage from Left Detector
  // LCD_BACKLIGHT               (0x04) // Control Signal for IR_LED
  // V_THUMB                     (0x08) // Voltage from Thumb Wheel
  // SPI_CS_LCD                  (0x10) // LCD Chip Select
  // RESET_LCD                   (0x20) // LCD Reset
  // SIMO_B                      (0x40) // SPI mode - slave in/master out USCI_B0
  // SOMI_B                      (0x80) // SPI mode - slave out/master in of USCI_B0
  // --------------------------------------------------------------------------
  
  P1SEL0 = ALL_SEL; // P1 set as I/0
  P1SEL1 = ALL_SEL; // P1 set as I/0
  P1DIR = ALL_DIR; // Set P1 direction to input
  
  P1SEL0 |= V_DETECT_R; // V_DETECT_R selected
  P1SEL1 |= V_DETECT_R; // V_DETECT_R selected

  P1SEL0 |= V_DETECT_L; // V_DETECT_L selected
  P1SEL1 |= V_DETECT_L; // V_DETECT_L selected
  
  P1SEL0 &=~LCD_BACKLIGHT; // LCD_BACKLIGHT GPI/O selected
  P1SEL1 &=~LCD_BACKLIGHT; // LCD_BACKLIGHT GPI/O selected
  P1OUT &=~ LCD_BACKLIGHT ; // LCD_BACKLIGHT Port Pin set low
  P1DIR |= LCD_BACKLIGHT ; // Set LCD_BACKLIGHT direction to output
  
  P1SEL0 |= V_THUMB; // V_THUMB selected
  P1SEL1 |= V_THUMB; // V_THUMB selected
  
  P1SEL0 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
  P1SEL1 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
  P1OUT |= SPI_CS_LCD; // SPI_CS_LCD Port Pin set high
  P1DIR |= SPI_CS_LCD; // Set SPI_CS_LCD output direction
  
  P1SEL0 &= ~RESET_LCD; // RESET_LCD GPI/O selected
  P1SEL1 &= ~ RESET_LCD; // RESET_LCD GPI/O selected
  P1OUT &= ~ RESET_LCD; // RESET_LCD Port Pin set low
  P1DIR |= RESET_LCD; // Set RESET_LCD output direction
  
  P1SEL0 &= ~SIMO_B; // SIMO_B selected
  P1SEL1 |= SIMO_B; // SIMO_B selected
  P1DIR |= SIMO_B; // SIMO_B set to Output
 
  P1SEL0 &= ~SOMI_B; // SOMI_B is used on the LCD
  P1SEL1 |= SOMI_B; // SOMI_B is used on the LCD
  P1OUT |= SOMI_B; // SOMI_B Port Pin set for Pull-up
  P1DIR &= ~SOMI_B; // SOMI_B set to Input
  P1REN |= SOMI_B; // Enable pullup resistor
//-----------------------------------------------------------------------------
}

void Init_Port2() {
  // --------------------------------------------------------------------------
  // Configure Port 2
  // USB_TXD                    (0x01) // USB transmission
  // USB_RXD                    (0x02) // USB receive
  // SPI_SCK                    (0x04) // spy bus
  // UNKNOWN_08                 (0x08) // not currently in use
  // UNKNOWN_10                 (0x10) // not currently in use
  // CPU_TXD                    (0x20) // CPU transmission
  // CPU_RXD                    (0x40) // CPU receive
  // UNKNOWN_80                 (0x80) // not currently in use
  // --------------------------------------------------------------------------
  
  P2SEL1 = ALL_SEL; // P2 I/O set
  P2SEL0 = ALL_SEL; // P2 I/O set
  P2DIR = ALL_DIR; // P2 direction set
  P2OUT = ALL_OUT; // P2 output set
  
  P2SEL1 |= USB_TXD; // functionality selected
  P2SEL0 &=~USB_TXD; // functionality selected
  P2OUT &=~USB_TXD; //
  
  P2SEL1 |= USB_RXD; // functionality selected
  P2SEL0 &=~USB_RXD; // functionality selected
  P2REN &=~USB_RXD; // pull-up resistor disabled
  P2OUT &=~USB_RXD; //
  
  P2SEL1 |= SPI_SCK; // functionality selected
  P2SEL0 &=~SPI_SCK; // functionality selected
  P2OUT |= SPI_SCK; //
  
  P2SEL1 &=~UNKNOWN_08; // unused
  P2SEL0 &=~UNKNOWN_08; //
  P2REN &=~UNKNOWN_08; //
  P2OUT &=~UNKNOWN_08; //
  P2DIR &=~UNKNOWN_08; // direction = input
  
  P2SEL1 &=~UNKNOWN_10; // unused
  P2SEL0 &=~UNKNOWN_10; //
  P2REN &=~UNKNOWN_10; //
  P2OUT &=~UNKNOWN_10; //
  P2DIR &=~UNKNOWN_10; // direction = input
  
  P2SEL1 |= CPU_TXD; // functionality selected
  P2SEL0 &=~CPU_TXD; // functionality selected
  P2OUT &=~CPU_TXD; //
  
  P2SEL1 |= CPU_RXD; // functionality selected
  P2SEL0 &=~CPU_RXD; // functionality selected
  P2REN &=~CPU_RXD; // pull-up resistor disabled
  P2OUT &=~CPU_RXD; //
  
  P2SEL1 &=~UNKNOWN_80; // unused
  P2SEL0 &=~UNKNOWN_80; //
  P2REN &=~UNKNOWN_80; //
  P2OUT &=~UNKNOWN_80; //
  P2DIR &=~UNKNOWN_80; // direction = input
}

void Init_Port3() {
  // --------------------------------------------------------------------------
  // Configure Port 3
  // X_PIN              (0x01) // accelerometer variable
  // Y_PIN              (0x02) // accelerometer variable
  // Z_PIN              (0x04) // accelerometer variable
  // IR_LED             (0x08) // IR_LED
  // R_FORWARD          (0x10) // Right motor forward
  // L_FORWARD          (0x20) // Left motor forward
  // R_REVERSE          (0x40) // Right motor reverse
  // L_REVERSE          (0x80) // Left motor reverse
  // --------------------------------------------------------------------------
  
  P3SEL0 = ALL_SEL; // P3 I/O set
  P3SEL1 = ALL_SEL; // P3 I/O set
  P3DIR = ALL_DIR; // P3 direction set
  P3OUT = ALL_OUT; // P3 Output set
  
  P3SEL1 &=~X_PIN; // functionality selected
  P3SEL0 &=~X_PIN; // functionality selected
  P3DIR &=~X_PIN; // direction = input
  P3REN &=~X_PIN; // pull-up resistor disabled
  
  P3SEL1 &=~Y_PIN; // functionality selected
  P3SEL0 &=~Y_PIN; // functionality selected
  P3DIR &=~Y_PIN; // direction = input
  P3REN &=~Y_PIN; // pull-up resistor disabled
  
  P3SEL1 &=~Z_PIN; // functionality selected
  P3SEL0 &=~Z_PIN; // functionality selected
  P3DIR &=~Z_PIN; // direction = input
  P3REN &=~Z_PIN; // pull-up resistor disabled
  
  P3SEL1 &=~ IR_LED; // functionality selected
  P3SEL0 &=~ IR_LED; // functionality selected
  P3DIR |= IR_LED; // direction = output
  
  // R_FORWARD (TB1.1) select bits updated for PWM
  P3SEL1 &=~R_FORWARD; // functionality selected
  P3SEL0 |= R_FORWARD; // functionality selected
  P3DIR |= R_FORWARD; // direction = output
  
  // R_REVERSE (TB2.1) select bits updated for PWM
  P3SEL1 &=~R_REVERSE; // functionality selected
  P3SEL0 |= R_REVERSE; // functionality selected
  P3DIR |= R_REVERSE; // direction = output
  
  // L_FORWARD (TB1.2) select bits updated for PWM
  P3SEL1 &=~L_FORWARD; // functionality selected
  P3SEL0 |= L_FORWARD; // functionality selected
  P3DIR |= L_FORWARD; // direction = output
  
  // L_REVERSE (TB2.2) select bits updated for PWM
  P3SEL1 &=~L_REVERSE; // functionality selected
  P3SEL0 |= L_REVERSE; // functionality selected
  P3DIR |= L_REVERSE; // direction = output
}

void Init_Port4() {
  //---------------------------------------------------------------------------
  // Configure PORT 4
  // Port 4 has only two pins
  // Port 4 Pins
  // SW1 (0x01) // Switch 1
  // SW2 (0x02) // Switch 2 
  //---------------------------------------------------------------------------

  P4SEL0 = ALL_SEL;  // P4 set as I/0
  P4SEL1 = ALL_SEL; // P4 set as I/0
  P4DIR = ALL_DIR;  // Set P4 direction to input
  P4OUT = ALL_OUT;

  // SW1
  P4SEL0 &= ~SW1; // SW1 set as I/0
  P4SEL1 &= ~SW1; // SW1 set as I/0
  P4OUT |= SW1; // Configure pullup resistor
  P4DIR &= ~SW1; // Direction = input
  P4REN |= SW1; // Enable pullup resistor
  P4IES |= SW1;  // SW1 Hi/Lo edge interrupt
  
  P4IFG &=~ SW1; // IFG SW1 cleared
  P4IE |= SW1;   // SW1 interrupt Enabled
  
  // SW2
  P4SEL0 &= ~SW2; // SW2 set as I/0
  P4SEL1 &= ~SW2; // SW2 set as I/0
  P4OUT |= SW2; // Configure pullup resistor
  P4DIR &= ~SW2; // Direction = input
  P4REN |= SW2; // Enable pullup resistor
  P4IES |= SW2; // SW2 Hi/Lo edge interrupt
  
  P4IFG &=~ SW2; // IFG SW2 cleared
  P4IE |= SW2;   // SW2 interrupt Enabled
  //---------------------------------------------------------------------------
}

void Init_PortJ() {
  // --------------------------------------------------------------------------
  // Configure Port J
  // IOT_WAKEUP              (0x01) // 
  // IOT_FACTORY             (0x02) // 
  // IOT_STA_MINIAP          (0x04) // 
  // IOT_RESET               (0x08) //
  // --------------------------------------------------------------------------
  
  PJSEL1 = ALL_SEL; // PJ I/O set
  PJSEL0 = ALL_SEL; // PJ I/O set
  PJOUT = ALL_OUT; // PJ output set
  
  PJSEL1 &=~IOT_WAKEUP; //
  PJSEL0 &=~IOT_WAKEUP; //
  PJOUT &=~IOT_WAKEUP; //
  PJDIR |= IOT_WAKEUP; // direction = output
  
  PJSEL1 &=~IOT_FACTORY; //
  PJSEL0 &=~IOT_FACTORY; //
  PJOUT &=~IOT_FACTORY; //
  PJDIR |= IOT_FACTORY; // direction = output
  
  PJSEL1 &=~IOT_STA_MINIAP; //
  PJSEL0 &=~IOT_STA_MINIAP; //
  PJOUT |= IOT_STA_MINIAP; //
  PJDIR |= IOT_STA_MINIAP; // direction = output
  
  PJSEL1 &=~IOT_RESET; //
  PJSEL0 &=~IOT_RESET; //
  PJOUT &=~IOT_RESET; //
  PJDIR |= IOT_RESET; // direction = output
}