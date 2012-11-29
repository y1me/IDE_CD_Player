#include <p18f6722.h>
#include <pic_init.h>
#include <HardwareProfile.h>
#include <interface_register.h>
#include <user_interface.h>
#include <delays.h>
#include <fct_ide.h>
#include <spi_ide.h>
#include <user.h>


#pragma config OSC = HSPLL, WDT = OFF, LVP = OFF//, XINST = OFF



#pragma udata gpr1
extern volatile struct chbits{
						unsigned spi:1; 
						unsigned tim0:1; 
						unsigned int1:1; 
						unsigned tim1:1; 
						unsigned mech:1; 
						unsigned first:1; 
						unsigned nodisc:1; 
						unsigned bit7:1;
		
					}flag ;
extern volatile struct flagspi{
						unsigned bit0:1;
						unsigned bit1:1;
						unsigned info:1;
						unsigned aux:1;
						unsigned bit4:1;
						unsigned bit5:1;
						unsigned ready:1;
						unsigned bit7:1;

					}flagspi ;
#pragma udata


extern volatile DATA_SPI        dataDAC;
extern volatile DATA_SPI        dataSRC;
extern volatile DATA_DISPLAY    dataDSPY1;
extern volatile DATA_DISPLAY    dataDSPY2;
extern volatile DATA_DISPLAY    dataDSPY3;
extern volatile DATA_DISPLAY    dataDSPY4;
extern volatile DATA_DISPLAY    dataDSPY5;
extern volatile DATA_DISPLAY    dataBlank;
extern volatile DATA_DISPLAY    dataREAD;

extern volatile	DATA_DISPLAY    dataDSPY1_info;
extern volatile	DATA_DISPLAY    dataDSPY2_info;
extern volatile	DATA_DISPLAY    dataDSPY3_info;
extern volatile	DATA_DISPLAY    dataDSPY4_info;
extern volatile	DATA_DISPLAY    dataDSPY5_info;

volatile DATA_DISPLAY    p_dataDSPY;

extern char keypad;
extern long trameok;
char keypad_log[3];
volatile long trame_capt;
volatile long count_IR;
volatile long count_IR_BIT;
volatile unsigned long start_IR_MSB, start_IR_LSB;
volatile int count_spi;
volatile int count_info;
unsigned char *p_spi;


void int_flag_high  (void);
void int_flag_low (void);

#pragma code high_vector=0x8
void interrupt_vector_high (void)
{
	_asm GOTO int_flag_high _endasm
}
#pragma code

#pragma code low_vector=0x18
void interrupt_vector_low (void)
{
	_asm GOTO int_flag_low _endasm
}
#pragma code

#pragma interruptlow int_flag_high
void int_flag_high(void)
{
        
	if(SPI_INT_F)
	{
            flag.spi = 1;
            SPI_INT_F = 0;

            if (flagspi.bit4)
            {
                PORTTEST = ~PORTTEST;
                *p_spi = SPI_BUFF;
                dataSRC.DataRead++;
                *p_spi++;

                if ( dataSRC.DataWrite < dataSRC.DataToWrite)
                {
                    //PORTTEST = ~PORTTEST;
                    SPI_BUFF = *p_spi;
                    dataSRC.DataWrite++;
                }
                else
                {
                    //PORTTEST = ~PORTTEST;
                    S_DRCV = 1;
                    dataSRC.DataToWrite = 0;
                    flagspi.bit4 = 0;
                }

            }

            if (flagspi.bit0)
            {
                *p_spi = SPI_BUFF;
                dataDAC.DataRead++;
                *p_spi++;

               
                if ((dataDAC.DataWrite & 0x01) == 0)
                //if (dataDAC.DataWrite % dataDAC.CSTiming == 0)
                {
                    S_DAC = 1;
                    S_DAC = 1;
                    S_DAC = 1;
                    S_DAC = 1;
                    S_DAC = 1;
                    S_DAC = 0;
                    S_DAC = 0;
                }
                

                if ( dataDAC.DataWrite < dataDAC.DataToWrite)
                {
                    SPI_BUFF = *p_spi;
                    dataDAC.DataWrite++;
                }
                else
                {
                    S_DAC = 1;
                    dataDAC.DataToWrite = 0;
                    flagspi.bit0 = 0;
                }
   
            }

            if (flagspi.bit1)
            {
                *p_spi = SPI_BUFF;
                p_dataDSPY.DataRead++;
                *p_spi++;

                if (p_dataDSPY.DataWrite == 4)
                //if (dataDAC.DataWrite % dataDAC.CSTiming == 0)
                {
                    S_DISPLAY = 1;
                    S_DISPLAY = 1;
                    S_DISPLAY = 1;
                    S_DISPLAY = 1;
                    S_DISPLAY = 0;
                }

                if ( p_dataDSPY.DataWrite < p_dataDSPY.DataToWrite)
                {
                    SPI_BUFF = *p_spi;
                    p_dataDSPY.DataWrite++;
                }
                else
                {
                    S_DISPLAY = 1;
                    p_dataDSPY.DataWrite = 0;
                    p_dataDSPY.DataRead = 0;
                    if(flagspi.bit5)
                    {
                        flagspi.bit5 = 0;
                        keypad_log[0] = keypad_log[1];
                        keypad_log[1] = keypad_log[2];
                        keypad_log[2] = p_dataDSPY._byte[7];
                        if(keypad_log[2] != 0 && keypad_log[1] == 0 && keypad_log[0] == 0)
                        {
                            keypad = keypad_log[2];
                        }
                    }
                    flagspi.bit1 = 0;
                }

            }

	}

    if(TIMDSPY_INT_F)
	{
            if (flagspi.info)
            {
                    count_info = 0;
                    flagspi.info = 0;
            }
            count_spi++;
            count_info++;
            switch (count_spi)
            {
                case 10:
                    if (dataDAC.DataToWrite != 0 && dataDAC.DataToWrite < 20)
                    {
                        S_DAC = 0;
                        p_spi = &dataDAC._byte[4];
                        SPI_BUFF = *p_spi;
                        dataDAC.DataWrite++;
                        flagspi.bit0 = 1;                    }
                break;

                case 14:
                    if (dataSRC.DataToWrite != 0 && dataSRC.DataToWrite < 20)
                    {
                        S_DRCV = 0;
                        p_spi = &dataSRC._byte[4];
                        PORTTEST = ~PORTTEST;
                        SPI_BUFF = *p_spi;
                        dataSRC.DataWrite++;
                        flagspi.bit4 = 1;
                    }
                break;

                case 18:
                    p_dataDSPY = dataBlank;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;
                case 19:
                    p_dataDSPY = dataDSPY1;
                    if (count_info < Time_info)	p_dataDSPY = dataDSPY1_info;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;

                case 28:
                        p_dataDSPY = dataREAD;
                        flagspi.bit5 = 1;
                        if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                        {
                            S_DISPLAY = 0;
                            p_spi = &p_dataDSPY._byte[4];
                            SPI_BUFF = *p_spi;
                            p_dataDSPY.DataWrite++;
                            flagspi.bit1 = 1;
                        }
                break;

                case 29:
                        p_dataDSPY = dataREAD;
                        flagspi.bit5 = 1;
                        p_dataDSPY._byte[4] = 0x41;
                        p_dataDSPY._byte[8] = 0x41;
                        if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                        {
                            S_DISPLAY = 0;
                            p_spi = &p_dataDSPY._byte[4];
                            SPI_BUFF = *p_spi;
                            p_dataDSPY.DataWrite++;
                            flagspi.bit1 = 1;
                        }
                break;

                case 30:
                    if (dataDAC.DataToWrite != 0 && dataDAC.DataToWrite < 20)
                    {
                        S_DAC = 0;
                        p_spi = &dataDAC._byte[4];
                        SPI_BUFF = *p_spi;
                        dataDAC.DataWrite++;
                        flagspi.bit0 = 1;                    }
                break;

                case 34:
                    if (dataSRC.DataToWrite != 0 && dataSRC.DataToWrite < 20)
                    {
                        S_DRCV = 0;
                        p_spi = &dataSRC._byte[4];
                        PORTTEST = ~PORTTEST;
                        SPI_BUFF = *p_spi;
                        dataSRC.DataWrite++;
                        flagspi.bit4 = 1;
                    }
                break;

                case 38:
                    p_dataDSPY = dataBlank;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;
                case 39:
                    p_dataDSPY = dataDSPY2;
					if (count_info < Time_info)	p_dataDSPY = dataDSPY2_info;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;

                case 50:
                    if (dataDAC.DataToWrite != 0 && dataDAC.DataToWrite < 20)
                    {
                        S_DAC = 0;
                        p_spi = &dataDAC._byte[4];
                        SPI_BUFF = *p_spi;
                        dataDAC.DataWrite++;
                        flagspi.bit0 = 1;                    }
                break;

                case 54:
                    if (dataSRC.DataToWrite != 0 && dataSRC.DataToWrite < 20)
                    {
                        S_DRCV = 0;
                        p_spi = &dataSRC._byte[4];
                        PORTTEST = ~PORTTEST;
                        SPI_BUFF = *p_spi;
                        dataSRC.DataWrite++;
                        flagspi.bit4 = 1;
                    }
                break;

                case 58:
                    p_dataDSPY = dataBlank;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;
                case 59:
                    p_dataDSPY = dataDSPY3;
					if (count_info < Time_info)	p_dataDSPY = dataDSPY3_info;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;

                case 70:
                    if (dataDAC.DataToWrite != 0 && dataDAC.DataToWrite < 20)
                    {
                        S_DAC = 0;
                        p_spi = &dataDAC._byte[4];
                        SPI_BUFF = *p_spi;
                        dataDAC.DataWrite++;
                        flagspi.bit0 = 1;                    }
                break;

                case 74:
                    if (dataSRC.DataToWrite != 0 && dataSRC.DataToWrite < 20)
                    {
                        S_DRCV = 0;
                        p_spi = &dataSRC._byte[4];
                        PORTTEST = ~PORTTEST;
                        SPI_BUFF = *p_spi;
                        dataSRC.DataWrite++;
                        flagspi.bit4 = 1;
                    }
                break;

                case 78:
                    p_dataDSPY = dataBlank;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;
                case 79:
                    p_dataDSPY = dataDSPY4;
                    if (count_info < Time_info)	p_dataDSPY = dataDSPY4_info;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;

                case 90:
                    if (dataDAC.DataToWrite != 0 && dataDAC.DataToWrite < 20)
                    {
                        S_DAC = 0;
                        p_spi = &dataDAC._byte[4];
                        SPI_BUFF = *p_spi;
                        dataDAC.DataWrite++;
                        flagspi.bit0 = 1;                    }
                break;

                case 94:
                    if (dataSRC.DataToWrite != 0 && dataSRC.DataToWrite < 20)
                    {
                        S_DRCV = 0;
                        p_spi = &dataSRC._byte[4];
                        PORTTEST = ~PORTTEST;
                        SPI_BUFF = *p_spi;
                        dataSRC.DataWrite++;
                        flagspi.bit4 = 1;
                    }
                break;

                case 98:
                    p_dataDSPY = dataBlank;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;
                case 99:
                    p_dataDSPY = dataDSPY5;
                    if (count_info < Time_info)	p_dataDSPY = dataDSPY5_info;
                    if (p_dataDSPY.DataToWrite != 0 && p_dataDSPY.DataToWrite < 20 && !flagspi.bit1)
                    {
                        S_DISPLAY = 0;
                        p_spi = &p_dataDSPY._byte[4];
                        SPI_BUFF = *p_spi;
                        p_dataDSPY.DataWrite++;
                        flagspi.bit1 = 1;
                    }
                break;


                default:
                    ;

            }
            if (count_spi == 100)           count_spi = 0;
            if (count_info >= Time_info)    count_info--;
            TIMERDSPY_REG = 0;
            TIMDSPY_INT_F = 0;
	}
        
	if(INT1_INT_F)
	{
            if (flag.bit7)
            {
                if(start_IR_MSB > 3) trame_capt |= 1;
                trame_capt = trame_capt << 1;
                count_IR_BIT++;
                if (count_IR_BIT == 32)
                {
                    trameok = trame_capt;
                    flag.bit7 = 0;
                }
            }

            count_IR = 0;
            start_IR_MSB = 0;
            start_IR_LSB = 0;
            flag.int1 = 0;
            EN_TIMIR = 1;
            INT1_INT_F = 0;
	}

        if(TIMIR_INT_F)
	{
            if (count_IR < 32)
            {
                start_IR_MSB = start_IR_MSB << 1;
                start_IR_MSB |= INPUT_IR;     
            }
            else
            {
                start_IR_LSB = start_IR_LSB << 1;
                start_IR_LSB |= INPUT_IR;      
            }
            count_IR++;
            if (count_IR > 40 && !flag.bit7)
            {
                 EN_TIMIR = 0;
                 if (start_IR_MSB < 16 && start_IR_LSB > 500)
                 {
                     flag.bit7 = 1;
                     count_IR_BIT = 0;
                     trame_capt = 0;
                 }
            }
            //if (count_IR > 40 && !flag.bit7)
		flag.tim1 = 1;
		TIMERIR_REGH = 0xF4;
		TIMERIR_REG = 0x47;
		TIMIR_INT_F = 0;
                                       

	}
}

#pragma interruptlow int_flag_low
void int_flag_low(void)
{
	if(TIMSUB_INT_F)
	{
		flag.tim0 = 1;
		TIMERSUB_REGH = 0xB3;
		TIMERSUB_REG = 0xB4;
		TIMSUB_INT_F =0;
	}
}

//DATA_PACKET product_id;

unsigned char AMSF[4],RMSF[4];



void main(void)
{

	ram unsigned char *ptest;
	int i;


	Port_Init();
	Spi_Init();
	Timer0_Init();
	Timer1_Init();
	INT_Init();
	flag.spi = 0;
	flag.tim0 = 0;
	flag.tim1 = 0;
	flag.int1 = 0;
	flag.first = 1;
	flag.nodisc = 1;
	flag.bit7 = 0;
	flagspi.info = 0;
        flagspi.bit0 = 0;
        flagspi.aux = 0;
        flagspi.bit4 = 0;
        dataSRC.DataToWrite = 0;
	dataDAC.DataToWrite = 0;
	dataDSPY1.DataToWrite = 0;
	dataDSPY2.DataToWrite = 0;
	dataDSPY3.DataToWrite = 0;
	dataDSPY4.DataToWrite = 0;
	S_DRCV = 1;
	S_DAC = 1;
	S_DISPLAY = 1;
	count_spi = 0;
	count_info = Time_info;
	InitSRC4392();
	InitPCM1792();
	InitMCP23S17();
	Timer2_Init();
	trameok = 0;
	InitDSPY();

        PORTTEST = 0;

	for(i=0;i<2;i++)
	{
		Delay10KTCYx(0);
	}
	Reset_Hard();

	for(i=0;i<40;i++)
	{
		Delay10KTCYx(0);
	}

	while(1)
	{
		ProcessIO();
	}


}