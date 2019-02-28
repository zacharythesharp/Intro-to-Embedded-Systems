//------------------------------------------------------------------------------
void parsing_string(char *array);
void display_ip(char *a);

int char_to_int(char c);

void move_F(int time);
void move_B(int time);
void move_R(int time);
void move_L(int time);

void add_byte_A0_now(char c);
void add_byte_A1_now(char c);
void string_transmit_A0(char *array);
void string_transmit_A1(char *array);
void string_transmit_A0_now(char *array);
void string_transmit_A1_now(char *array);
void add_byte_A0(char c);
void add_byte_A1(char c);

int process_string(char* string);
void commands(int choice);
void Init_Serial_UCA1(void);
void Init_Serial_UCA0(void);

void betterHEXtoBCD(unsigned int x, char* buffer);

void Init_Timer_A1(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);

void calibrate();
void waiting();
void circling();
void turning();
void intercepting();
void switch_menu();

void ADC_Process(void);
void HEXtoBCD(int hex_value, char *buffer);
void Init_ADC(void);
void find_direction();
void find_direction_1();

// Function prototypes main
void main(void);
void Init_Conditions(void);
void Init_Timers(void);
void Display_Process(void);

// timers.c
void Five_msec_Delay(unsigned int fivemsec);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
__interrupt void TIMER2_B1_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);

void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);

void grab_a_character(void);
int wait_for_character(void);
void menu(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

//void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);

// Project 4 Functions
void one_sec_pause();
void forward();
void reverse();
void clockwise();
void counterclockwise();

