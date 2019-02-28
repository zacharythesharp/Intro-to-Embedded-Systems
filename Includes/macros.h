// Required defines
#define ZERO                   (0)
#define ONE                    (1)
#define TWO                    (2)
#define THREE                  (3)
#define FOUR                   (4)
#define FIVE                   (5)
#define SIX                    (6)
#define SEVEN                  (7)
#define EIGHT                  (8)
#define NINE                   (9)
#define TEN                   (10)
#define TWELVE                (12)
#define FIFTEEN               (15)
#define TWENTY_3              (23)
#define FIFTY                 (50)
#define ARRAY_SIZE_6           (6)
#define ONE                    (1)
#define ONE_TEN               (10)
#define ONE_HUN              (100)
#define ONE_K               (1000)
#define TEN_K              (10000)
#define HEX_SIZE_5             (5)
#define HEX_9600          (0x4911)  
#define HEX_115200        (0x0451)
#define CLEAR_0x            (0x00)
#define BAUD_115200            (4)
#define BAUD_9600             (52)
#define TRANSMIT_SIZE          (9)
#define RATE_9600              (0)
#define RATE_115200            (1)
#define INITIAL                (0)
#define CLEAR                  (0)
#define MULTIPLY_2             (2)
#define MULTIPLY_3             (3)
#define LARGE_RING_SIZE       (32)
#define SMALL_RING_SIZE       (16)
#define BEGINNING              (0)

// PWM Duty Cycle Macros
#define WHEEL_PERIOD          (1500) //
#define PWM_00_PRC            (WHEEL_PERIOD * 0.0)
#define PWM_35_PRC            (WHEEL_PERIOD * .35)
#define PWM_40_PRC            (WHEEL_PERIOD * .40)
#define PWM_45_PRC            (WHEEL_PERIOD * .45)
#define PWM_50_PRC            (WHEEL_PERIOD * .50)
#define PWM_55_PRC            (825)
#define PWM_60_PRC            (600)
#define PWM_65_PRC            (WHEEL_PERIOD * .65)
#define PWM_70_PRC            (WHEEL_PERIOD * .70)
#define PWM_75_PRC            (WHEEL_PERIOD * .75)

// In the event the universe no longer exists, this bit will reset
#define ALWAYS                   (1)
#define CNTL_STATE_INDEX         (3) // Control States
#define SW1                   (0x01) // Switch 1
#define SW2                   (0x02) // Switch 2
#define CNTL_STATE_INDEX         (3)

// interrupts
#define  TA0CCR0_INTERVAL    (12500) // 8,000,000 --> every 50ms
#define  TA0CCR1_INTERVAL     (1250)  // 5ms value
// #define  TA0CCR2_INTERVAL (12500)

#define  DEBOUNCE_FALSE          (0)
#define  DEBOUNCE_TRUE           (1)
#define  MAX_DEBOUNCE_COUNT      (4)

#define LONG_DELAY             (215)
#define DIVISOR                  (2)
#define SHORT_DELAY             (10)
#define PRC25_1024             (256)
#define PRC50_1024             (512)
#define PRC75_1024             (768)
#define INNER_CASE_0          (0x00) 
#define INNER_CASE_1          (0x01)
#define INNER_CASE_2          (0x02)
#define CASE_0                   (0)
#define CASE_1                   (1)
#define CASE_2                   (2)
#define CASE_3                   (3)
#define CASE_4                   (4)
#define CASE_5                   (5)
#define CASE_6                   (6)
#define CASE_7                   (7)
#define CASE_8                   (8)
#define CASE_9                   (9)
#define CASE_10                 (10)
#define CASE_11                 (11)
#define CASE_12                 (12)
#define CASE_13                 (13)
#define CASE_14                 (14)
#define CASE_16                 (16)
#define MAX_CASE                (14)

// LCD
#define LCD_HOME_L1	        0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0

//Main.c Macros
#define TEXT_LENGTH             (11)
#define DELAY                   (50)
#define DISPLAY_CHANGE_FALSE     (0)
#define DISPLAY_CHANGE_TRUE      (1)

// LCD Offset Display Macros for posL#
#define OFFSET_0                 (0)
#define OFFSET_1                 (1)
#define OFFSET_2                 (2)
#define OFFSET_3                 (3)
#define OFFSET_4                 (4)

//Timers.c Macros
// also used in main.c, interrupts_timers.c, interrupt_ports.c
#define INITIAL_COUNT            (0)

// Movement.c macros
#define ONE_SEC_DELAY          (200)
#define HALF_SEC_DELAY         (100)

//------------------------------------------------------------------------------
#define RESET_STATE              (0)
#define BASE_ARRAY_SIZE          (5)
#define INITIAL_CONDITION     (0x00)
#define INDEX_0                  (0)
#define INDEX_1                  (1)
#define INDEX_2                  (2)
#define INDEX_3                  (3)
#define CONVERSION            (0x30)
#define BASE_0                   (0)
#define INCREMENT_1              (1)
#define INCREMENT_10            (10)
#define INCREMENT_100          (100)
#define INCREMENT_1000        (1000)
#define LIMIT_1000            (1000)
#define LIMIT_9                  (9)
#define LIMIT_99                (99)
#define TRUE                     (1)
#define FALSE                    (0)
#define LIMIT_175              (175)

//Port Macros
#define ALL_SEL               (0x00) 
#define ALL_OUT               (0x00)
#define ALL_DIR               (0x00)

//Port 1
#define V_DETECT_R            (0x01) // Voltage from Right Detector
#define V_DETECT_L            (0x02) // Voltage from Left Detector
#define LCD_BACKLIGHT         (0x04) // Control Signal for IR_LED
#define V_THUMB               (0x08) // Voltage from Thumb Wheel
#define SPI_CS_LCD            (0x10) // LCD Chip Select
#define RESET_LCD             (0x20) // LCD Reset
#define SIMO_B                (0x40) // SPI mode - slave in/master out USCI_B0
#define SOMI_B                (0x80) // SPI mode - slave out/master in of USCI_B0

//Port 2
#define USB_TXD               (0x01) // 
#define USB_RXD               (0x02) // 
#define SPI_SCK               (0x04) // 
#define UNKNOWN_08            (0x08) // 
#define UNKNOWN_10            (0x10) // 
#define CPU_TXD               (0x20) // 
#define CPU_RXD               (0x40) // 
#define UNKNOWN_80            (0x80) // 

//Port 3
#define X_PIN                 (0x01) // 
#define Y_PIN                 (0x02) // 
#define Z_PIN                 (0x04) // 
#define IR_LED                (0x08) //
#define R_FORWARD             (0x10) // 
#define L_FORWARD             (0x20) // 
#define R_REVERSE             (0x40) // 
#define L_REVERSE             (0x80) // 

//Port 4
#define SW1                   (0x01) // Switch 1
#define SW2                   (0x02) // Switch 2 

//Port J
#define IOT_WAKEUP            (0x01) // 
#define IOT_FACTORY           (0x02) // 
#define IOT_STA_MINIAP        (0x04) // 
#define IOT_RESET             (0x08) //

