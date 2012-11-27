#include "delay_sw.h"




/************************************************************************
*						DELAY FUNCTIONS									*
************************************************************************/
unsigned int temp_count;

void Delay( unsigned int delay_count ) 
{
	temp_count = delay_count +1;
	asm volatile("outer: dec _temp_count");	
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");
	asm volatile("repeat #4000" );	
	asm volatile("nop");
	asm volatile("repeat #4200" );	
	asm volatile("nop");
	asm volatile("bra outer");
	asm volatile("done:");
}
void Delay_Us( unsigned int delayUs_count ) //FCy=40MHz, delay = delayUs_count*1µs + 500ns
{
	temp_count = delayUs_count +1;
	asm volatile("outer1: dec _temp_count");	
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done1");
	asm volatile("repeat #4" );	
	asm volatile("nop");
	asm volatile("repeat #2" );	
	asm volatile("nop");
	asm volatile("bra outer1");
	asm volatile("done1:");
}	


/****************************************************************************/
/****************************************************************************/

