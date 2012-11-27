#include "HardwareProfile.h"
#include <p18f6722.h>

extern volatile struct chbits{
						unsigned spi:1; 
						unsigned bit1:1; 
						unsigned bit2:1; 
						unsigned bit3:1; 
						unsigned bit4:1; 
						unsigned bit5:1; 
						unsigned bit6:1; 
						unsigned bit7:1;
		
					}flag ;

void spi_out(unsigned char data)
{
	flag.spi = 0; 
	SPI_BUFF = data;
	while(flag.spi != 1);
	flag.spi = 0;
}

void spi_in(unsigned char *data)
{
	flag.spi = 0; 
	SPI_BUFF = 0x00;
	while(flag.spi != 1);
	flag.spi = 0;
	*data = SPI_BUFF;	
}