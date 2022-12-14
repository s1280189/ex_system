#include "system.h"
#include "io.h"
#include "sys/alt_stdio.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
int main(){
alt_up_pixel_buffer_dma_dev *pixel_buf_dev;
alt_putstr("Hello from Nios II!\n");
pixel_buf_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
if(pixel_buf_dev==NULL)
alt_putstr("Error: could not poen pixel buffer device \n");
else
alt_putstr("Opened pixel buffer device \n");
/* clear and dra
 * w */
alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dev, 0);
alt_up_pixel_buffer_dma_draw_box(pixel_buf_dev, 0, 0,159,119,0xF800,0);
alt_up_pixel_buffer_dma_draw_box(pixel_buf_dev, 160, 0,319,119,0x07D0,0);
alt_up_pixel_buffer_dma_draw_box(pixel_buf_dev, 0,120,159,239,0x07D0,0);
alt_up_pixel_buffer_dma_draw_box(pixel_buf_dev, 160,120,319,239,0x001F,0);
/* Event loop never exits. */
while (1);
return 0;
}
