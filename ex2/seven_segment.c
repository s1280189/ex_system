#include "system.h"
#include "io.h"

int main()
{
int sw, hex;
while (1){
sw = IORD_8DIRECT(PIO_SW_BASE,0);
switch (sw) {
case 0x10: hex = 0x40; break;
case 0x11: hex = 0x79; break;
case 0x12: hex = 0x24; break;
case 0x13: hex = 0x30; break;
case 0x14: hex = 0x19; break;
case 0x15: hex = 0x12; break;
case 0x16: hex = 0x02; break;
case 0x17: hex = 0x58; break;
case 0x18: hex = 0x00; break;
case 0x19: hex = 0x10; break;
case 0x1A: hex = 0x08;  break;// write your code
case 0x1B: hex = 0x03; break;// write your code here
case 0x1C: hex = 0x46;break;// write your code here
case 0x1D: hex = 0x21;break;// write your code here
case 0x1E: hex = 0x06;break;// write your code here
case 0x1F: hex = 0x0e;break;// write your code here
default: hex = 0xff; break;
}
IOWR_8DIRECT(PIO_HEX_BASE, 0, hex);
}
return 0;
}


