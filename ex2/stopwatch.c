#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_up_avalon_character_lcd.h"
#include "altera_up_avalon_character_lcd_regs.h"

// The period of 50 MHz is 20ns.
// 20ns * 50M = 1s
#define TIMER_PERIOD (50000000-1)

// An integer for recording the current split number is recorded.
int split;

// An array consisting of 4 integers and represents the elapsed time.
// count[0]: 0/10 seconds - 9/10 seconds
// count[2],count[1]: 00 seconds - 59 seconds
// count[3]: 0 minutes - 9 minutes
int count[4];

////////////////////////////////////////////////////
// You do not have to modify the following three functions
////////////////////////////////////////////////////
int num2hexsig(int num);
void button_interrupt();
void displayLCD(char *first, char *second);

////////////////////////////////////////////////////
// You have to modify the following three functions
////////////////////////////////////////////////////
void incsplit();
void reset_and_start();
void inccount();

int main()
{
	/////////////////////////////////////
	// Initialization
	/////////////////////////////////////
	split = 0;
	for(int i = 0 ; i < 4 ; i++)
		count[i] = 0;

	/////////////////////////////////////
	// Setup for timer module
	/////////////////////////////////////

	// Set interrupt function
	alt_ic_isr_register( TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, inccount, (void *) 0, (void *) 0 );
	// Set timer period to 50M (1 second)
	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, TIMER_PERIOD & 0x0000ffff);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, TIMER_PERIOD >> 16);
	// Set ITO, CONT flag and START flag to 1
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, ALTERA_AVALON_TIMER_CONTROL_ITO_MSK 
					 | ALTERA_AVALON_TIMER_CONTROL_CONT_MSK 
					 |ALTERA_AVALON_TIMER_CONTROL_START_MSK );

	/////////////////////////////////////
	// Setup for KEYs (Push buttons)
	/////////////////////////////////////

	// Capture the interrupt from Keys that set to 1
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_KEY_BASE, 0xF);
	// Clear the capture information
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_KEY_BASE, 0x0);
	// Set interrupt function
	alt_ic_isr_register( PIO_KEY_IRQ_INTERRUPT_CONTROLLER_ID, PIO_KEY_IRQ, button_interrupt, (void *) 0, (void *) 0 );

	while (1);

	return 0;
}

// num is converted to the signals for seven-segment LEDs
int num2hexsig(int num){
	int hex;

	switch (num) {
	case 0x0: hex = 0x40; break;
	case 0x1: hex = 0x79; break;
	case 0x2: hex = 0x24; break;
	case 0x3: hex = 0x30; break;
	case 0x4: hex = 0x19; break;
	case 0x5: hex = 0x12; break;
	case 0x6: hex = 0x02; break;
	case 0x7: hex = 0x58; break;
	case 0x8: hex = 0x00; break;
	case 0x9: hex = 0x10; break;
	case 0xA: hex = 0x08; break;
	case 0xB: hex = 0x03; break;
	case 0xC: hex = 0x46; break;
	case 0xD: hex = 0x21; break;
	case 0xE: hex = 0x06; break;
	case 0xF: hex = 0x0e; break;
	default: hex = 0xff; break;
	}

	return hex;
}

// The function to be called when an interrupt from KEYs is captured
void button_interrupt(){

	int button;
	button = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_KEY_BASE);

	switch (button) {
	case 0x1: // KEY0
		reset_and_start();
		break;
	case 0x2: // KEY1
		break;
	case 0x4: // KEY2
		break;
	case 0x8: // KEY3
		incsplit();
		break;
	default:
		break;
	}

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_KEY_BASE, 0x0);
	button = 0;
}

// The strings of first and second are displayed on the first and second row
// of the character LCD.
void displayLCD(char *first, char *second){

	alt_up_character_lcd_dev * char_lcd_dev;

	// Open the Character LCD port named as "character_lcd_0"
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");

	// Initialize the character display
	alt_up_character_lcd_init (char_lcd_dev);

	// Write the string of "first" in the first row
	alt_up_character_lcd_string(char_lcd_dev, first);

	// Move cursor to the begging of the second row
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);

	// Write the string of "second" in the second row
	alt_up_character_lcd_string(char_lcd_dev, second);

}

// The value of split is incremented. The initial value of split is 1,
// and the next of 9 is 1.
// The display of the character LCD is updated based on split number
// and split time.
void incsplit(){

	//displayLCD("", "S1 1:23:4");
	char str1[10] = "S0 0:00:0", str2[10] = "S0 0:00:0";
	inccount();
	str1[1] = '0'+split;
	str1[3] = '0'+count[3];
	str1[5] = '0'+count[2];
	str1[6] = '0'+count[1];
	str1[8] = '0'+count[0];
	strcpy(str2, str1);

	displayLCD(str1, str2);
	if(split==9)split=0;
	else split++;
}

// counter and split are reset to 0. The display of the character LCD is clear.
void reset_and_start(){

	displayLCD("","S0 0:00:0");
	count[0]=0;
	count[1]=0;
	count[2]=0;
	count[3]=0;
	split=0;

}

// count is incremented by 1/10 second every 1/10 second.
void inccount(){
	count[0]++;
	if(count[0]==9){
		count[0]=0;
		count[1]++;
		if(count[1]==9){
			count[1]=0;
			count[2]++;
			if(count[2]==5){
				count[2]=0;
				count[3]++;
				if(count[3]==9){
					count[3]=0;
				}
			}
		}
	}

	// Reset TO of timer module
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
	// Display the digit of count[1] in HEX1
    IOWR_8DIRECT(PIO_HEX1_BASE, 0, num2hexsig(count[0]));
    IOWR_8DIRECT(PIO_HEX1_BASE, 0, num2hexsig(count[1]));
    IOWR_8DIRECT(PIO_HEX1_BASE, 0, num2hexsig(count[2]));
    IOWR_8DIRECT(PIO_HEX1_BASE, 0, num2hexsig(count[3]));




}

