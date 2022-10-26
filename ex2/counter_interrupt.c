#include "system.h"
#include "altera_avalon_timer_regs.h"
#include "io.h"

#include "sys/alt_irq.h"
#define TIMER_PERIOD (50000000-1)
int cnt = 0;
int sw = 0;
int hex = 0;
void count ( void* context )
{
	if(sw==0x01 || sw==0x03 || sw==0x07)cnt=0;
	else if(sw>=0x02){
		if(sw==0x06){
			if(cnt==0)cnt=9;
			else cnt--;
		}
		else if(sw==0x02){
			if(cnt==9)cnt=0;
			else cnt++;
		}
	}
// Reset TO

	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);

}

int main()
{
// Set interrupt function
alt_ic_isr_register( TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
TIMER_0_IRQ, count, (void *) 0, (void *) 0 );
// Set timer period to 50M (1 second)
IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE,
TIMER_PERIOD & 0x0000ffff);
IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE,
TIMER_PERIOD >> 16);
// Set ITO, CONT flag and START flag to 1
IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
ALTERA_AVALON_TIMER_CONTROL_ITO_MSK |
ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
|ALTERA_AVALON_TIMER_CONTROL_START_MSK );

while(1){
sw = IORD_8DIRECT(PIO_SW_BASE,0);
switch ( cnt ) {
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
default: hex = 0xff; break;
}
IOWR_8DIRECT(PIO_HEX_BASE, 0, hex);
IOWR_8DIRECT(PIO_LEDG_BASE, 0, sw);

}

return 0;
}
