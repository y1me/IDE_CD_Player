#ifndef DELAY_SW_H
#define DELAY_SW_H

/**************** delay define ****************/
#define Fcy  40000000

#define Delay50uS_count   50
#define Delay100uS_count  100
#define Delay200uS_count  200
#define Delay400uS_count  400

#define Delay_1mS_Cnt	  1000
#define Delay_2mS_Cnt	  2000
#define Delay_3mS_Cnt	  3000
#define Delay_5mS_Cnt	  5000
#define Delay_15mS_Cnt 	  15000
#define Delay_50mS_Cnt 	  200
#define Delay_100mS_Cnt   400
#define Delay_200mS_Cnt   800
#define Delay_250mS_Cnt   1000
#define Delay_300mS_Cnt   1200
#define Delay_500mS_Cnt   2000
#define Delay_1S_Cnt	  4000


/***************** DELAY FUNCTIONS PROTOYPES *******************/
void Delay( unsigned int delay_count );
void Delay_Us( unsigned int delayUs_count );

#endif // DELAY_SW_H

