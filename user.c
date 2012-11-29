#include "user.h"
#include "spi_ide.h"
#include "delays.h"
#include "HardwareProfile.h"
#include <fct_ide.h>
#include <user_interface.h>
#include <stdio.h>
#include <string.h>

/** V A R I A B L E S ********************************************************/
volatile struct chbits{
						unsigned spi:1; 
						unsigned tim0:1; 
						unsigned int1:1; 
						unsigned tim1:1; 
						unsigned mech:1; 
						unsigned first:1; 
						unsigned nodisc:1; 
						unsigned bit7:1;
		
					}flag ;

volatile struct flagspi{
						unsigned bit0:1;
						unsigned bit1:1;
						unsigned info:1;
						unsigned aux:1;
						unsigned bit4:1;
						unsigned bit5:1;
						unsigned ready:1;
						unsigned bit7:1;

					}flagspi ;




#pragma udata gpr7
ram unsigned char TOC[1024];
#pragma udata

#pragma udata gpr2
ram volatile DataMSF	EndAddrMSF;
ram volatile DataMSF CurrentRelAddrMSF;
ram volatile DataMSF CurrentAbsAddrMSF;
#pragma udata

#pragma udata gpr3
volatile   DATA_SPI        dataDAC;
volatile   DATA_SPI        dataSRC;
volatile   DATA_DISPLAY    dataDSPY1;
volatile   DATA_DISPLAY    dataDSPY2;
volatile   DATA_DISPLAY    dataDSPY3;
volatile   DATA_DISPLAY    dataDSPY4;
volatile   DATA_DISPLAY    dataDSPY5;
volatile   DATA_DISPLAY    dataBlank;
volatile   DATA_DISPLAY    dataREAD;

volatile   DATA_DISPLAY    dataDSPY1_info;
volatile   DATA_DISPLAY    dataDSPY2_info;
volatile   DATA_DISPLAY    dataDSPY3_info;
volatile   DATA_DISPLAY    dataDSPY4_info;
volatile   DATA_DISPLAY    dataDSPY5_info;
#pragma udata

#pragma udata gpr5
char keypad;
long trameok;
DATA_PACKET     product_id;
int CDStatus;
int TrackToPlay;
int NumbOfTrack;
unsigned char MuteState, RightVol, LeftVol, AudioStatus;
unsigned char TimeoutEN;
char buffer[20];
int length;
#pragma udata


/** P R I V A T E  P R O T O T Y P E S ***************************************/
unsigned char ProcessIrCode(long *);
void EjectLoad(void);
void LoadTOCInfo(void);
void HandleSIRSC(void);
void UpdateCurrentMSF(void);
void PlayPause(void);
void NextTrack(void);
void PreviousTrack(void);
void VolumeUp(void);
void VolumeDown(void);
void Mute(unsigned char );
void SetAuxIn(void);
unsigned char ConvertDigit4(unsigned char );
unsigned char ConvertDigit2(unsigned char );
/*****************************************************************************/
void InitMCP23S17(void)
{   
	
        S_DISPLAY = 1;
	S_DISPLAY = 0;
	spi_out(0x40);
	spi_out(0x00);
	spi_out(0xE0);
        spi_out(0xF0);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0xF0);
        spi_out(0x00);
        spi_out(0xF0);
        spi_out(0x00);
        spi_out(0xF0);
        spi_out(0x08);
        spi_out(0x08);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x1F);
        spi_out(0x00);
	S_DISPLAY = 1;

        S_DISPLAY = 1;
	S_DISPLAY = 0;
	spi_out(0x42);
	spi_out(0x00);
	spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x08);
        spi_out(0x08);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
	S_DISPLAY = 1;

        S_DISPLAY = 1;
	S_DISPLAY = 0;
	spi_out(0x44);
	spi_out(0x00);
	spi_out(0xF0);//0x00
        spi_out(0xFF);//0x01
        spi_out(0x00);//0x02
        spi_out(0x00);//0x03
        spi_out(0x00);//0x04
        spi_out(0x0F);//0x05
        spi_out(0x00);//0x06
        spi_out(0x0F);//0x07
        spi_out(0x00);//0x08
        spi_out(0x0F);//0x09
        spi_out(0x08);//0x0A
        spi_out(0x08);//0x0B
        spi_out(0x00);//0x0C
        spi_out(0x00);//0x0D
        spi_out(0x00);//0x0E
        spi_out(0x00);//0x0F
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
        spi_out(0x00);
	S_DISPLAY = 1;

        /*
        S_DISPLAY = 1;
	S_DISPLAY = 0;
	spi_out(0x45);
	spi_out(0x00);
	spi_in(&dataDSPY1._byte[4]);
	spi_in(&dataDSPY1._byte[5]);
        spi_in(&dataDSPY1._byte[6]);
	spi_in(&dataDSPY1._byte[7]);
        spi_in(&dataDSPY1._byte[8]);
	spi_in(&dataDSPY1._byte[9]);
        spi_in(&dataDSPY1._byte[10]);
	spi_in(&dataDSPY1._byte[11]);
        spi_in(&dataDSPY1._byte[12]);
	spi_in(&dataDSPY1._byte[13]);
        spi_in(&dataDSPY1._byte[14]);
	spi_in(&dataDSPY1._byte[15]);
        spi_in(&dataDSPY1._byte[16]);
	spi_in(&dataDSPY1._byte[17]);
        spi_in(&dataDSPY1._byte[18]);
	spi_in(&dataDSPY1._byte[19]);
        spi_in(&dataDSPY1._byte[20]);
	spi_in(&dataDSPY1._byte[21]);
        spi_in(&dataDSPY1._byte[22]);
        spi_in(&dataDSPY1._byte[23]);
        spi_in(&dataDSPY1._byte[24]);
        spi_in(&dataDSPY1._byte[25]);
	S_DRCV = 1;
        S_DRCV = 1;
        */

}

void InitSRC4392(void)
{   
	//config receiv
	
	RST_DRCV = 1;
	Delay10TCYx(3); //wait 1탎*x
	RST_DRCV = 0;
	Delay10TCYx(3); //wait 1탎*x
	RST_DRCV = 1;
	Delay10KTCYx(10);//wait 1ms*x
	
	// config power_on perif
	S_DRCV = 0;
	spi_out(0x01);
	spi_out(0x00); //dummy
	spi_out(0x33);
	S_DRCV = 1;
	
	// config RCV Ctr Reg 1
	S_DRCV = 0;
	spi_out(0x0D);
	spi_out(0x00);//dummy
	spi_out(0x08);
	S_DRCV = 1;
	
	// config RCV Ctr Reg 2
	S_DRCV = 0;
	spi_out(0x0E);
	spi_out(0x00);//dummy
	spi_out(0x01);
	S_DRCV = 1;
	
	// config RCV PLL1 Ctr Reg 1
	S_DRCV = 0;
	spi_out(0x0F);
	spi_out(0x00);//dummy
	spi_out(0x22);
	S_DRCV = 1;
	
	// config RCV PLL1 Ctr Reg 2
	S_DRCV = 0;
	spi_out(0x10);
	spi_out(0x00);//dummy
	spi_out(0x00);
	S_DRCV = 1;
	
	// config RCV PLL1 Ctr Reg 3
	S_DRCV = 0;
	spi_out(0x11);
	spi_out(0x00);//dummy
	spi_out(0x00);
	S_DRCV = 1;
	
	//lecture registre 0x11
	/*
	S_DRCV = 0;
	spi_out(0x81);
	spi_out(0x00);//dummy
	spi_in(&test);
	S_DRCV = 1;
	*/	
	//fin config RCV
	
	//config SRC
	// config SRC Ctr Reg 1
	S_DRCV = 0;
	spi_out(0x2D);
	spi_out(0x00);//dummy
	spi_out(0x06);
	S_DRCV = 1;
	
	// config SRC Ctr Reg 2
	S_DRCV = 0;
	spi_out(0x2E);
	spi_out(0x00);//dummy 
	spi_out(0x04);
	S_DRCV = 1;
	
	// config SRC Ctr Reg 2
	S_DRCV = 0;
	spi_out(0x2F);
	spi_out(0x00);//dummy
	spi_out(0x00);
	S_DRCV = 1;
	//fin config SRC
	
	//config PORTA
	// config PORTA Ctr Reg 1
	S_DRCV = 0;
	spi_out(0x03);
	spi_out(0x00);//dummy
	spi_out(0x3F);
	S_DRCV = 1;
	
	// config PORTA Ctr Reg 2
	S_DRCV = 0;
	spi_out(0x04);
	spi_out(0x00);//dummy
	spi_out(0x00);
	S_DRCV = 1;
	//fin config PORTA
	//fin config receiv
}

void InitPCM1792(void)
{  
	//config DAC
	
	RST_DAC = 1;
	Delay10TCYx(3); //wait 1탎*x
	RST_DAC = 0;
	Delay10TCYx(3); //wait 1탎*x
	RST_DAC = 1;
	Delay10KTCYx(10);//wait 1ms*x
	
	RightVol = 201;
	LeftVol = 201;
	// config DAC Reg 16
	S_DAC = 0;
	spi_out(0x10);
	spi_out(LeftVol);
	S_DAC = 1;
	
	// config DAC Reg 17
	S_DAC = 0;
	spi_out(0x11);
	spi_out(RightVol);
	S_DAC = 1;
	
	// config DAC Reg 18
	S_DAC = 0;
	spi_out(0x12);
	spi_out(0xA0);
	S_DAC = 1;
}

void InitDSPY(void)
{
        dataDSPY1.DataToWrite = 8;
        dataDSPY1.DataRead = 0;
        dataDSPY1.DataWrite = 0;
        dataDSPY1._byte[4] = 0x40;
        dataDSPY1._byte[5] = 0x12;
        dataDSPY1._byte[6] = 0xFE;// supply digit
        dataDSPY1._byte[7] = 0x00;// switch & diode
        dataDSPY1._byte[8] = 0x42;
        dataDSPY1._byte[9] = 0x12;
        dataDSPY1._byte[10] = 0xEE;//digit 1/4
        dataDSPY1._byte[11] = 0xE4;//digit 2/2

        dataDSPY2.DataToWrite = 8;
        dataDSPY2.DataRead = 0;
        dataDSPY2.DataWrite = 0;
        dataDSPY2._byte[4] = 0x40;
        dataDSPY2._byte[5] = 0x12;
        dataDSPY2._byte[6] = 0xFD;// supply digit
        dataDSPY2._byte[7] = 0x00;// switch & diode
        dataDSPY2._byte[8] = 0x42;
        dataDSPY2._byte[9] = 0x12;
        dataDSPY2._byte[10] = 0xCD;//digit 2/4
        dataDSPY2._byte[11] = 0x5A;//digit 1/2

        dataDSPY3.DataToWrite = 8;
        dataDSPY3.DataRead = 0;
        dataDSPY3.DataWrite = 0;
        dataDSPY3._byte[4] = 0x40;
        dataDSPY3._byte[5] = 0x12;
        dataDSPY3._byte[6] = 0xF7;// supply digit
        dataDSPY3._byte[7] = 0x00;// switch & diode
        dataDSPY3._byte[8] = 0x42;
        dataDSPY3._byte[9] = 0x12;
        dataDSPY3._byte[10] = 0xEF;//digit 3/4
        dataDSPY3._byte[11] = 0x45;

        dataDSPY4.DataToWrite = 8;
        dataDSPY4.DataRead = 0;
        dataDSPY4.DataWrite = 0;
        dataDSPY4._byte[4] = 0x40;
        dataDSPY4._byte[5] = 0x12;
        dataDSPY4._byte[6] = 0x0F;// supply digit
        dataDSPY4._byte[7] = 0x00;// switch & diode
        dataDSPY4._byte[8] = 0x42;
        dataDSPY4._byte[9] = 0x12;
        dataDSPY4._byte[10] = 0x95;//digit 4/4
        dataDSPY4._byte[11] = 0xA2;

        dataDSPY5.DataToWrite = 8;
        dataDSPY5.DataRead = 0;
        dataDSPY5.DataWrite = 0;
        dataDSPY5._byte[4] = 0x40;
        dataDSPY5._byte[5] = 0x12;
        dataDSPY5._byte[6] = 0xFB;// supply digit
        dataDSPY5._byte[7] = 0x00;// switch & diode
        dataDSPY5._byte[8] = 0x42;
        dataDSPY5._byte[9] = 0x12;
        dataDSPY5._byte[10] = 0xFF;//digit dp/4
        dataDSPY5._byte[11] = 0x22;

        dataDSPY1_info.DataToWrite = 8;
        dataDSPY1_info.DataRead = 0;
        dataDSPY1_info.DataWrite = 0;
        dataDSPY1_info._byte[4] = 0x40;
        dataDSPY1_info._byte[5] = 0x12;
        dataDSPY1_info._byte[6] = 0xFE;// supply digit
        dataDSPY1_info._byte[7] = 0x00;// switch & diode
        dataDSPY1_info._byte[8] = 0x42;
        dataDSPY1_info._byte[9] = 0x12;
        dataDSPY1_info._byte[10] = 0xEE;//digit 1/4
        dataDSPY1_info._byte[11] = 0xE4;//digit 2/2

        dataDSPY2_info.DataToWrite = 8;
        dataDSPY2_info.DataRead = 0;
        dataDSPY2_info.DataWrite = 0;
        dataDSPY2_info._byte[4] = 0x40;
        dataDSPY2_info._byte[5] = 0x12;
        dataDSPY2_info._byte[6] = 0xFD;// supply digit
        dataDSPY2_info._byte[7] = 0x00;// switch & diode
        dataDSPY2_info._byte[8] = 0x42;
        dataDSPY2_info._byte[9] = 0x12;
        dataDSPY2_info._byte[10] = 0xCD;//digit 2/4
        dataDSPY2_info._byte[11] = 0x5A;//digit 1/2

        dataDSPY3_info.DataToWrite = 8;
        dataDSPY3_info.DataRead = 0;
        dataDSPY3_info.DataWrite = 0;
        dataDSPY3_info._byte[4] = 0x40;
        dataDSPY3_info._byte[5] = 0x12;
        dataDSPY3_info._byte[6] = 0xF7;// supply digit
        dataDSPY3_info._byte[7] = 0x00;// switch & diode
        dataDSPY3_info._byte[8] = 0x42;
        dataDSPY3_info._byte[9] = 0x12;
        dataDSPY3_info._byte[10] = 0xEF;//digit 3/4
        dataDSPY3_info._byte[11] = 0x45;

        dataDSPY4_info.DataToWrite = 8;
        dataDSPY4_info.DataRead = 0;
        dataDSPY4_info.DataWrite = 0;
        dataDSPY4_info._byte[4] = 0x40;
        dataDSPY4_info._byte[5] = 0x12;
        dataDSPY4_info._byte[6] = 0x0F;// supply digit
        dataDSPY4_info._byte[7] = 0x00;// switch & diode
        dataDSPY4_info._byte[8] = 0x42;
        dataDSPY4_info._byte[9] = 0x12;
        dataDSPY4_info._byte[10] = 0x95;//digit 4/4
        dataDSPY4_info._byte[11] = 0xA2;

        dataDSPY5_info.DataToWrite = 8;
        dataDSPY5_info.DataRead = 0;
        dataDSPY5_info.DataWrite = 0;
        dataDSPY5_info._byte[4] = 0x40;
        dataDSPY5_info._byte[5] = 0x12;
        dataDSPY5_info._byte[6] = 0xFB;// supply digit
        dataDSPY5_info._byte[7] = 0x00;// switch & diode
        dataDSPY5_info._byte[8] = 0x42;
        dataDSPY5_info._byte[9] = 0x12;
        dataDSPY5_info._byte[10] = 0xFF;//digit dp/4
        dataDSPY5_info._byte[11] = 0x22;

        dataBlank.DataToWrite = 8;
        dataBlank.DataRead = 0;
        dataBlank.DataWrite = 0;
        dataBlank._byte[4] = 0x40;
        dataBlank._byte[5] = 0x12;
        dataBlank._byte[6] = 0xFF;// supply digit
        dataBlank._byte[7] = 0x00;// switch & diode
        dataBlank._byte[8] = 0x42;
        dataBlank._byte[9] = 0x12;
        dataBlank._byte[10] = 0xFF;//digit dp/4
        dataBlank._byte[11] = 0xFF;

        dataREAD.DataToWrite = 8;
        dataREAD.DataRead = 0;
        dataREAD.DataWrite = 0;
        dataREAD._byte[4] = 0x45;
        dataREAD._byte[5] = 0x0E;
        dataREAD._byte[6] = 0x00;
        dataREAD._byte[7] = 0x00;
        dataREAD._byte[8] = 0x45;
        dataREAD._byte[9] = 0x10;
        dataREAD._byte[10] = 0x00;
        dataREAD._byte[11] = 0x00;
}
 
void HandleSIRSC(void)
{
    switch ( keypad )
        {
            case 1:
                trameok = KEY1;
                keypad = 0;
            break;

            case 2:
                trameok = KEY9;
                keypad = 0;
            break;

            case 4:
                trameok = KEY10;
                keypad = 0;
            break;

            case 8:
                trameok = KEY11;
                keypad = 0;
            break;

            case 16:
                trameok = KEY3;
                keypad = 0;
            break;

            case 32:
                trameok = KEY6;
                keypad = 0;
            break;

            case 64:
                trameok = KEY5;
                keypad = 0;
            break;

            case 128:
                trameok = KEY7;
                keypad = 0;
            break;

            default:
                keypad = keypad;
        }

    if (ProcessIrCode(&trameok) == 1) trameok = 0;
}

unsigned char ProcessIrCode(long *trameToProcess)
{		

	switch ( *trameToProcess )
		{
			case KEY1:
                            if (!flagspi.aux)   EjectLoad();
                        return 1;

			break;

			case KEY7:
                            if (!flagspi.aux)   PlayPause();
                        return 1;
			break;

			case KEY9:
                            if (!flagspi.aux)
                            {
				Stop();
                                //Mute
                                dataDAC.DataToWrite = 2;
                                dataDAC.DataRead = 0;
                                dataDAC.DataWrite = 0;
                                dataDAC.CSTiming = 2;
                                dataDAC._byte[4] = 0x12;
                                dataDAC._byte[5] = 0xA1;

				TrackToPlay = 1;
				CDStatus = STOP;
                                dataDSPY2_info._byte[11] = D_void;//digit 1/2 V
                                dataDSPY1_info._byte[11] = D_void;//digit 2/2 o
                                dataDSPY1_info._byte[10] = d_s;//digit 1/4 l
                                dataDSPY2_info._byte[10] = d_t;//digit 2/4
                                dataDSPY3_info._byte[10] = d_o;//digit 3/4
                                dataDSPY4_info._byte[10] = d_p;//digit 4/4
                                dataDSPY5_info._byte[10] = d_void;//digit dp/4
                                flagspi.info = 1;
                            }
                            return 1;
			break;

			case KEY10:
                            if (!flagspi.aux)   NextTrack();
                            return 1;
			break;

			case KEY11:
                            if (!flagspi.aux)   PreviousTrack();
                            return 1;
			break;

			case KEY4:
                            if(!MuteState)
                            {
                                Mute(MuteState);
                                MuteState = 1;
                            }
                            else
                            {
                                Mute(MuteState);
                                MuteState = 0;
                            }
                            return 1;
			break;

			case KEY6:
                            VolumeDown();
                            return 1;
			break;

			case KEY5:
                            VolumeUp();
                            return 1;
			break;

                        case KEY2:
                            //if (!flagspi.aux)   INQUIRY(&product_id.Device_Type);
                            return 1;
                        break;

                        case KEY3:
                            SetAuxIn();
                            return 1;
                        break;

			default: 
                            *trameToProcess = *trameToProcess;
                        return 0;
		}
return 0;
}

void EjectLoad(void)
{   
	if ( Mech_Stat() == 1 )
	{
            Load();
            flag.mech = 1;
            CDStatus = STOP;
            TrackToPlay = 1;
            dataDSPY2._byte[11] = D_void;//digit 1/2 r
            dataDSPY1._byte[11] = D_void;//digit 2/2 e
            dataDSPY1._byte[10] = d_r;//digit 1/4 a
            dataDSPY2._byte[10] = d_e;//digit 2/4 d
            dataDSPY3._byte[10] = d_a;//digit 3/4 c
            dataDSPY4._byte[10] = d_d;//digit 4/4 d
            dataDSPY5._byte[10] = d_void;//digit dp/4
            LoadTOCInfo();
	}
	else 
	{
            Eject();
            flag.mech = 0;
            flag.nodisc = 1;
            dataDSPY2._byte[11] = D_void;//digit 1/2 r
            dataDSPY1._byte[11] = D_void;//digit 2/2 e
            dataDSPY1._byte[10] = d_o;//digit 1/4 a
            dataDSPY2._byte[10] = d_p;//digit 2/4 d
            dataDSPY3._byte[10] = d_e;//digit 3/4 c
            dataDSPY4._byte[10] = d_n;//digit 4/4 d
            dataDSPY5._byte[10] = d_void;//digit dp/4
            //Mute
            dataDAC.DataToWrite = 2;
            dataDAC.DataRead = 0;
            dataDAC.DataWrite = 0;
            dataDAC.CSTiming = 2;
            dataDAC._byte[4] = 0x12;
            dataDAC._byte[5] = 0xA1;
	}
}

void PlayPause(void)
{   
    if ( Mech_Stat() == 1 )
    {
        //Mute
        dataDAC.DataToWrite = 2;
        dataDAC.DataRead = 0;
        dataDAC.DataWrite = 0;
        dataDAC.CSTiming = 2;
        dataDAC._byte[4] = 0x12;
        dataDAC._byte[5] = 0xA1;

        Load();
        LoadTOCInfo();
        flag.mech = 1;
        CDStatus = STOP;
        TrackToPlay = 1;
    }

    if (!flag.nodisc)
    {
        switch ( CDStatus )
            {
            case  STOP:
                Play_MSF(TrackToPlay, &TOC[0]);
                CDStatus = PLAY;
                //Sound
                dataDAC.DataToWrite = 2;
                dataDAC.DataRead = 0;
                dataDAC.DataWrite = 0;
                dataDAC.CSTiming = 2;
                dataDAC._byte[4] = 0x12;
                dataDAC._byte[5] = 0xA0;

                dataDSPY2_info._byte[11] = D_void;//digit 1/2 V
                dataDSPY1_info._byte[11] = D_void;//digit 2/2 o
                dataDSPY1_info._byte[10] = d_p;//digit 1/4 l
                dataDSPY2_info._byte[10] = d_l;//digit 2/4
                dataDSPY3_info._byte[10] = d_a;//digit 3/4
                dataDSPY4_info._byte[10] = d_y;//digit 4/4
                dataDSPY5_info._byte[10] = d_void;//digit dp/4
                flagspi.info = 1;
            break;

            case  PLAY:
                Pause();
                CDStatus = PAUSE;
                //Mute
                dataDAC.DataToWrite = 2;
                dataDAC.DataRead = 0;
                dataDAC.DataWrite = 0;
                dataDAC.CSTiming = 2;
                dataDAC._byte[4] = 0x12;
                dataDAC._byte[5] = 0xA1;

                dataDSPY2_info._byte[11] = D_void;//digit 1/2 V
                dataDSPY1_info._byte[11] = D_p;//digit 2/2 o
                dataDSPY1_info._byte[10] = d_a;//digit 1/4 l
                dataDSPY2_info._byte[10] = d_u;//digit 2/4
                dataDSPY3_info._byte[10] = d_s;//digit 3/4
                dataDSPY4_info._byte[10] = d_e;//digit 4/4
                dataDSPY5_info._byte[10] = d_void;//digit dp/4
                flagspi.info = 1;
            break;

            case  PAUSE:
                //Resume();
                Play_MSF_address(&CurrentAbsAddrMSF, &TOC[0]);
                CDStatus = PLAY;
                //Sound
                dataDAC.DataToWrite = 2;
                dataDAC.DataRead = 0;
                dataDAC.DataWrite = 0;
                dataDAC.CSTiming = 2;
                dataDAC._byte[4] = 0x12;
                dataDAC._byte[5] = 0xA0;

                dataDSPY2_info._byte[11] = D_void;//digit 1/2 V
                dataDSPY1_info._byte[11] = D_void;//digit 2/2 o
                dataDSPY1_info._byte[10] = d_p;//digit 1/4 l
                dataDSPY2_info._byte[10] = d_l;//digit 2/4
                dataDSPY3_info._byte[10] = d_a;//digit 3/4
                dataDSPY4_info._byte[10] = d_y;//digit 4/4
                dataDSPY5_info._byte[10] = d_void;//digit dp/4
                flagspi.info = 1;
            break;
            }
    }
}

void NextTrack(void)
{   
	if ( flag.mech && !flag.nodisc)
	{	
		if ( (EndAddrMSF.track - 1) > TrackToPlay )	TrackToPlay += 1;

		else	TrackToPlay = 1;
                
		if (CDStatus != STOP)
		{
			Play_MSF(TrackToPlay, &TOC[0]);
			CDStatus = PLAY;
		}
                else
                {
                    sprintf (buffer, "%u", TrackToPlay);
                    if(strlen (buffer) == 2)
                    {
                        dataDSPY2_info._byte[11] = ConvertDigit2(buffer[0]);//digit 1/2
                        dataDSPY1_info._byte[11] = ConvertDigit2(buffer[1]);//digit 2/2
                    }
                    else
                    {
                        dataDSPY2_info._byte[11] = D_0;//digit 1/2
                        dataDSPY1_info._byte[11] = ConvertDigit2(buffer[0]);//digit 2/2
                    }
                    dataDSPY1_info._byte[10] = d_void;//digit 1/4 s
                    dataDSPY2_info._byte[10] = d_void;//digit 2/4 c
                    dataDSPY3_info._byte[10] = d_void;//digit 3/4 o
                    dataDSPY4_info._byte[10] = d_void;//digit 4/4 k
                    dataDSPY5_info._byte[10] = d_pp;//digit dp/4
                    flagspi.info = 1;
                }
	}
}
void PreviousTrack(void)
{   
	if ( flag.mech && !flag.nodisc)
	{
		if (CDStatus != STOP)
		{
                    if ( CurrentRelAddrMSF.min == 0 && CurrentRelAddrMSF.sec < 3 )
                    {
                            if ( TrackToPlay == 1 )	TrackToPlay = EndAddrMSF.track - 1;
                            else	TrackToPlay -= 1;
                            Play_MSF(TrackToPlay, &TOC[0]);
                            CDStatus = PLAY;

                    }
                    else
                    {
                            Play_MSF(TrackToPlay, &TOC[0]);
                            CDStatus = PLAY;
                    }
		}
		else
		{
                    if ( TrackToPlay == 1 )	TrackToPlay = EndAddrMSF.track - 1;
                    else	TrackToPlay -= 1;
                    sprintf (buffer, "%u", TrackToPlay);
                    if(strlen (buffer) == 2)
                    {
                        dataDSPY2_info._byte[11] = ConvertDigit2(buffer[0]);//digit 1/2
                        dataDSPY1_info._byte[11] = ConvertDigit2(buffer[1]);//digit 2/2
                    }
                    else
                    {
                        dataDSPY2_info._byte[11] = D_0;//digit 1/2
                        dataDSPY1_info._byte[11] = ConvertDigit2(buffer[0]);//digit 2/2
                    }
                    dataDSPY1_info._byte[10] = d_void;//digit 1/4 s
                    dataDSPY2_info._byte[10] = d_void;//digit 2/4 c
                    dataDSPY3_info._byte[10] = d_void;//digit 3/4 o
                    dataDSPY4_info._byte[10] = d_void;//digit 4/4 k
                    dataDSPY5_info._byte[10] = d_pp;//digit dp/4
                    flagspi.info = 1;
		}
	
	}
}

void LoadTOCInfo(void)
{ 
	long i=0,k=1;
	
        dataDSPY2._byte[11] = D_void;//digit 1/2 r
        dataDSPY1._byte[11] = D_void;//digit 2/2 e
        dataDSPY1._byte[10] = d_r;//digit 1/4 a
        dataDSPY2._byte[10] = d_e;//digit 2/4 d
        dataDSPY3._byte[10] = d_a;//digit 3/4 c
        dataDSPY4._byte[10] = d_d;//digit 4/4 d
        dataDSPY5._byte[10] = d_void;//digit dp/4
	
	while( k !=0 && i < 50 )
	{
		k = Read_TOC(&TOC[0]);
		i++;
	}
	if( TOC[2] == 1 )
	{
	flag.nodisc = 0;
	NumbOfTrack = TOC[3];
	k = NumbOfTrack;
	k *= 8;
	k += 9;
	EndAddrMSF.min = TOC[k];
	EndAddrMSF.sec = TOC[k+1];
	EndAddrMSF.frame = TOC[k+2];
	EndAddrMSF.track = NumbOfTrack + 1;
	}
	else flag.nodisc = 1;
	
	if (flag.nodisc)
	{
            dataDSPY2._byte[11] = D_n;//digit 1/2 n
            dataDSPY1._byte[11] = D_o;//digit 2/2 o
            dataDSPY1._byte[10] = d_d;//digit 1/4 d
            dataDSPY2._byte[10] = d_i;//digit 2/4 i
            dataDSPY3._byte[10] = d_s;//digit 3/4 s
            dataDSPY4._byte[10] = d_c;//digit 4/4 c
            dataDSPY5._byte[10] = d_void;//digit dp/4
	}
	else
	{
            dataDSPY2_info._byte[11] = D_d;//digit 1/2 d
            dataDSPY1_info._byte[11] = D_i;//digit 2/2 i
            dataDSPY1_info._byte[10] = d_s;//digit 1/4 s
            dataDSPY2_info._byte[10] = d_c;//digit 2/4 c
            dataDSPY3_info._byte[10] = d_o;//digit 3/4 o
            dataDSPY4_info._byte[10] = d_k;//digit 4/4 k
            dataDSPY5_info._byte[10] = d_void;//digit dp/4

            flagspi.info = 1;
	}

}

void UpdateCurrentMSF(void)
{ 
	if (flag.tim0)
	{
		flag.tim0 = 0;
		if ( flag.mech )
		{	
			AudioStatus = Read_AbsMSF_SubCh(&CurrentAbsAddrMSF.track);
			Read_RelMSF_SubCh(&CurrentRelAddrMSF.track);			
			if (CDStatus == PLAY)
			{	
				TrackToPlay = CurrentRelAddrMSF.track;
				if (AudioStatus == 0x13 || AudioStatus == 0x14 || AudioStatus == 0x15)
				{
					Stop();
					TrackToPlay = 1;
					CDStatus = STOP;
				}
			}

		}
	}

}

void VolumeUp(void)
{
    if(RightVol == 255)
    {
        RightVol = 255;
        LeftVol = 255;

        dataDSPY2_info._byte[11] = D_v;//digit 1/2 V
        dataDSPY1_info._byte[11] = D_o;//digit 2/2 o
        dataDSPY1_info._byte[10] = d_l;//digit 1/4 l
        dataDSPY2_info._byte[10] = d_m;//digit 2/4 m
        dataDSPY3_info._byte[10] = d_a;//digit 3/4 a
        dataDSPY4_info._byte[10] = d_x;//digit 4/4 x
        dataDSPY5_info._byte[10] = d_void;//digit dp/4
    }
    else
    {
	RightVol += 3;
	LeftVol += 3;
    }
        dataDAC.DataToWrite = 4;
        dataDAC.DataRead = 0;
        dataDAC.DataWrite = 0;
        dataDAC.CSTiming = 2;
        dataDAC._byte[4] = 0x10;
        dataDAC._byte[5] = LeftVol;
        dataDAC._byte[6] = 0x11;
        dataDAC._byte[7] = RightVol;

    sprintf (buffer, "%u", RightVol);

    if(strlen (buffer) == 2)
    {
        dataDSPY2_info._byte[11] = D_v;//digit 1/2 V
        dataDSPY1_info._byte[11] = D_o;//digit 2/2 o
        dataDSPY1_info._byte[10] = d_l;//digit 1/4 l
        dataDSPY2_info._byte[10] = d_0;//digit 2/4 0
        dataDSPY3_info._byte[10] = ConvertDigit4(buffer[0]);//digit 3/4
        dataDSPY4_info._byte[10] = ConvertDigit4(buffer[1]);//digit 4/4
        dataDSPY5_info._byte[10] = d_void;//digit dp/4
    }
    else
    {
        if (RightVol != 255)
        {
            dataDSPY2_info._byte[11] = D_v;//digit 1/2 V
            dataDSPY1_info._byte[11] = D_o;//digit 2/2 o
            dataDSPY1_info._byte[10] = d_l;//digit 1/4 l
            dataDSPY2_info._byte[10] = ConvertDigit4(buffer[0]);//digit 2/4
            dataDSPY3_info._byte[10] = ConvertDigit4(buffer[1]);//digit 3/4
            dataDSPY4_info._byte[10] = ConvertDigit4(buffer[2]);//digit 4/4
            dataDSPY5_info._byte[10] = d_void;//digit dp/4
        }
    }
		
    flagspi.info = 1;
}

void VolumeDown(void)
{ 
    if(RightVol <= 14)
    {
        RightVol = 12;
        LeftVol = 12;

        dataDSPY2_info._byte[11] = D_v;//digit 1/2 V
        dataDSPY1_info._byte[11] = D_o;//digit 2/2 o
        dataDSPY1_info._byte[10] = d_l;//digit 1/4 l
        dataDSPY2_info._byte[10] = d_m;//digit 2/4 m
        dataDSPY3_info._byte[10] = d_i;//digit 3/4 i
        dataDSPY4_info._byte[10] = d_n;//digit 4/4 n
        dataDSPY5_info._byte[10] = d_void;//digit dp/4
    }
    else
    {
	RightVol -= 3;
	LeftVol -= 3;
    }

    dataDAC.DataToWrite = 4;
    dataDAC.DataRead = 0;
    dataDAC.DataWrite = 0;
    dataDAC.CSTiming = 2;
    dataDAC._byte[4] = 0x10;
    dataDAC._byte[5] = LeftVol;
    dataDAC._byte[6] = 0x11;
    dataDAC._byte[7] = RightVol;

    sprintf (buffer, "%u", RightVol);

    if(strlen (buffer) == 2 && RightVol > 14)
    {
        dataDSPY2_info._byte[11] = D_v;//digit 1/2 V
        dataDSPY1_info._byte[11] = D_o;//digit 2/2 o
        dataDSPY1_info._byte[10] = d_l;//digit 1/4 l
        dataDSPY2_info._byte[10] = d_0;//digit 2/4 0
        dataDSPY3_info._byte[10] = ConvertDigit4(buffer[0]);//digit 3/4
        dataDSPY4_info._byte[10] = ConvertDigit4(buffer[1]);//digit 4/4
        dataDSPY5_info._byte[10] = d_void;//digit dp/4
    }
    else
    {
        if (RightVol > 14)
        {
            dataDSPY2_info._byte[11] = D_v;//digit 1/2 V
            dataDSPY1_info._byte[11] = D_o;//digit 2/2 o
            dataDSPY1_info._byte[10] = d_l;//digit 1/4 l
            dataDSPY2_info._byte[10] = ConvertDigit4(buffer[0]);//digit 2/4
            dataDSPY3_info._byte[10] = ConvertDigit4(buffer[1]);//digit 3/4
            dataDSPY4_info._byte[10] = ConvertDigit4(buffer[2]);//digit 4/4
            dataDSPY5_info._byte[10] = d_void;//digit dp/4
        }
    }
		
    flagspi.info = 1;


}

void Mute(unsigned char State)
{ 
    if (State)
    {
        dataDAC.DataToWrite = 2;
        dataDAC.DataRead = 0;
        dataDAC.DataWrite = 0;
        dataDAC.CSTiming = 2;
        dataDAC._byte[4] = 0x12;
        dataDAC._byte[5] = 0xA1;

        dataDSPY2_info._byte[11] = D_void;//digit 1/2 V
        dataDSPY1_info._byte[11] = D_void;//digit 2/2 o
        dataDSPY1_info._byte[10] = d_m;//digit 1/4 l
        dataDSPY2_info._byte[10] = d_u;//digit 2/4
        dataDSPY3_info._byte[10] = d_t;//digit 3/4
        dataDSPY4_info._byte[10] = d_e;//digit 4/4
        dataDSPY5_info._byte[10] = d_void;//digit dp/4
    }
    else
    {
        dataDAC.DataToWrite = 2;
        dataDAC.DataRead = 0;
        dataDAC.DataWrite = 0;
        dataDAC.CSTiming = 2;
        dataDAC._byte[4] = 0x12;
        dataDAC._byte[5] = 0xA0;

        dataDSPY2_info._byte[11] = D_void;//digit 1/2 V
        dataDSPY1_info._byte[11] = D_s;//digit 2/2 o
        dataDSPY1_info._byte[10] = d_o;//digit 1/4 l
        dataDSPY2_info._byte[10] = d_u;//digit 2/4
        dataDSPY3_info._byte[10] = d_n;//digit 3/4
        dataDSPY4_info._byte[10] = d_d;//digit 4/4
        dataDSPY5_info._byte[10] = d_void;//digit dp/4
    }
    flagspi.info = 1;
}

void SetAuxIn(void)
{
    if (!flagspi.aux)
    {
        Stop();
        TrackToPlay = 1;
        CDStatus = STOP;

        //Sound
        
        dataDAC.DataRead = 0;
        dataDAC.DataWrite = 0;
        dataDAC.CSTiming = 2;
        dataDAC._byte[4] = 0x12;
        dataDAC._byte[5] = 0xA0;
        dataDAC.DataToWrite = 2;

        flagspi.aux = 1; 
        dataSRC.DataRead = 0;
        dataSRC.DataWrite = 0;
        dataSRC.CSTiming = 2;
        dataSRC._byte[4] = 0x0D;
        dataSRC._byte[5] = 0x00;
        dataSRC._byte[6] = 0x09;
        dataSRC.DataToWrite = 3;

        dataDSPY2._byte[11] = D_void;//digit 1/2 n
        dataDSPY1._byte[11] = D_void;//digit 2/2 o
        dataDSPY1._byte[10] = d_a;//digit 1/4 d
        dataDSPY2._byte[10] = d_u;//digit 2/4 i
        dataDSPY3._byte[10] = d_x;//digit 3/4 s
        dataDSPY4._byte[10] = d_void;//digit 4/4 c
        dataDSPY5._byte[10] = d_void;//digit dp/4
    }
    else
    {
        //Mute
       
        dataDAC.DataToWrite = 2;
        dataDAC.DataRead = 0;
        dataDAC.DataWrite = 0;
        dataDAC.CSTiming = 2;
        dataDAC._byte[4] = 0x12;
        dataDAC._byte[5] = 0xA1;

        flagspi.aux = 0;
        dataSRC.DataToWrite = 3;
        dataSRC.DataRead = 0;
        dataSRC.DataWrite = 0;
        dataSRC.CSTiming = 2;
        dataSRC._byte[4] = 0x0D;
        dataSRC._byte[5] = 0x00;
        dataSRC._byte[6] = 0x08;

        if (!flag.mech)  EjectLoad();
        else
        {
            flag.mech = 1;
            CDStatus = STOP;
            TrackToPlay = 1;
            dataDSPY2._byte[11] = D_void;//digit 1/2 r
            dataDSPY1._byte[11] = D_void;//digit 2/2 e
            dataDSPY1._byte[10] = d_r;//digit 1/4 a
            dataDSPY2._byte[10] = d_e;//digit 2/4 d
            dataDSPY3._byte[10] = d_a;//digit 3/4 c
            dataDSPY4._byte[10] = d_d;//digit 4/4 d
            dataDSPY5._byte[10] = d_void;//digit dp/4
            LoadTOCInfo();
        }
    }

}


unsigned char ConvertDigit4(unsigned char letter)
{
	switch ( letter )
		{
		case  '0':
                    return d_0;
		break;

		case  '1':
                    return d_1;
		break;

                case  '2':
                    return d_2;
		break;

                case  '3':
                    return d_3;
		break;

                case  '4':
                    return d_4;
		break;

                case  '5':
                    return d_5;
		break;

                case  '6':
                    return d_6;
		break;

                case  '7':
                    return d_7;
		break;

                case  '8':
                    return d_8;
		break;

                case  '9':
                    return d_9;
		break;

		default:
                    return 255;

		}
}

unsigned char ConvertDigit2(unsigned char letter)
{
	switch ( letter )
		{
		case  '0':
                    return D_0;
		break;

		case  '1':
                    return D_1;
		break;

                case  '2':
                    return D_2;
		break;

                case  '3':
                    return D_3;
		break;

                case  '4':
                    return D_4;
		break;

                case  '5':
                    return D_5;
		break;

                case  '6':
                    return D_6;
		break;

                case  '7':
                    return D_7;
		break;

                case  '8':
                    return D_8;
		break;

                case  '9':
                    return D_9;
		break;

		default:
                    return 255;

		}
}

void ProcessIO(void)
{   
	if(!flag.first) HandleSIRSC();

        if (flag.first)
        {
            LoadTOCInfo();
            flag.mech = 1;
            CDStatus = STOP;
            TrackToPlay = 1;
            flag.first = 0;
	}
	if (!flag.nodisc && !flagspi.aux)
        {
            UpdateCurrentMSF();

            if (CDStatus == STOP)
            {

                sprintf (buffer, "%u", NumbOfTrack);
                if(strlen (buffer) == 2)
                {
                    dataDSPY2._byte[11] = ConvertDigit2(buffer[0]);//digit 1/2
                    dataDSPY1._byte[11] = ConvertDigit2(buffer[1]);//digit 2/2
                }
                else
                {
                    dataDSPY2._byte[11] = D_0;//digit 1/2
                    dataDSPY1._byte[11] = ConvertDigit2(buffer[0]);//digit 2/2
                }

                sprintf (buffer, "%u", EndAddrMSF.min);
                if(strlen (buffer) == 2)
                {
                    dataDSPY1._byte[10] = ConvertDigit4(buffer[0]);//digit 1/4
                    dataDSPY2._byte[10] = ConvertDigit4(buffer[1]);//digit 2/4
                }
                else
                {
                    dataDSPY1._byte[10] = d_0;//digit 1/4
                    dataDSPY2._byte[10] = ConvertDigit4(buffer[0]);//digit 2/4
                }
                sprintf (buffer, "%u", EndAddrMSF.sec);
                if(strlen (buffer) == 2)
                {
                    dataDSPY3._byte[10] = ConvertDigit4(buffer[0]);//digit 3/4
                    dataDSPY4._byte[10] = ConvertDigit4(buffer[1]);//digit 4/4
                }
                else
                {
                    dataDSPY3._byte[10] = d_0;//digit 3/4
                    dataDSPY4._byte[10] = ConvertDigit4(buffer[0]);//digit 4/4
                }
                dataDSPY5._byte[10] = d_pp;//digit dp/4
            }
            else
            {
                sprintf (buffer, "%u", CurrentRelAddrMSF.track);
                if(strlen (buffer) == 2)
                {
                    dataDSPY2._byte[11] = ConvertDigit2(buffer[0]);//digit 1/2
                    dataDSPY1._byte[11] = ConvertDigit2(buffer[1]);//digit 2/2
                }
                else
                {
                    dataDSPY2._byte[11] = D_0;//digit 1/2
                    dataDSPY1._byte[11] = ConvertDigit2(buffer[0]);//digit 2/2
                }
                sprintf (buffer, "%u", CurrentRelAddrMSF.min);
                if(strlen (buffer) == 2)
                {
                    dataDSPY1._byte[10] = ConvertDigit4(buffer[0]);//digit 1/4
                    dataDSPY2._byte[10] = ConvertDigit4(buffer[1]);//digit 2/4
                }
                else
                {
                    dataDSPY1._byte[10] = d_0;//digit 1/4
                    dataDSPY2._byte[10] = ConvertDigit4(buffer[0]);//digit 2/4
                }
                sprintf (buffer, "%u", CurrentRelAddrMSF.sec);
                if(strlen (buffer) == 2)
                {
                    dataDSPY3._byte[10] = ConvertDigit4(buffer[0]);//digit 3/4
                    dataDSPY4._byte[10] = ConvertDigit4(buffer[1]);//digit 4/4
                }
                else
                {
                    dataDSPY3._byte[10] = d_0;//digit 3/4
                    dataDSPY4._byte[10] = ConvertDigit4(buffer[0]);//digit 4/4
                }
                dataDSPY5._byte[10] = d_pp;//digit dp/4
            }

        }
}
