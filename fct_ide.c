#include <p18f6722.h>
#include <HardwareProfile.h>
#include <interface_register.h>
#include "user.h"
#include "user_interface.h"

unsigned char Mech_Stat(DATA_IDE dataide)  //reset CD drive
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0xBD;
	dataide.cmd9 = 0x08;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd12)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
	dataide.i = 0;
	dataide.test = 0xAA;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		if (dataide.test == 0x51 || dataide.test == 0x50)
		{
			Write_command(0xA0);
			dataide.test = 0xAA;
			dataide.j = 0;
			while (dataide.test != 0x58)
                        {
                            dataide.j++;
                            dataide.test = Read_Status();
                            if (dataide.j == Nb_Retry) return 3;
                        }
			
			dataide.ptest = &dataide.cmd0;
			while(dataide.ptest < &dataide.cmd12)
			{
				Write_Data(dataide.ptest);
				*dataide.ptest++;
				*dataide.ptest++;
			}
		}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}

	dataide.ptest = &dataide.data0;
	dataide.i = 0;
	while(((dataide.test & 0x08) == 0x08) && (dataide.i != 12) )
	{
		Read_Data(dataide.ptest);
		*dataide.ptest++;
		*(dataide.ptest+1) = *(dataide.ptest-1);
		*(dataide.ptest-1) = *dataide.ptest;
		*dataide.ptest = *(dataide.ptest+1);
		*dataide.ptest++;
		dataide.i++;
		dataide.test = Read_Status();
	}

	if ((dataide.data0  != 0x00) && ((dataide.data1 & 0xE0) != 0x00)) dataide.test = 2; //erreur  mecanisme non prés
	else 	if ((dataide.data1 & 0xF0) == 0x00) dataide.test = 0; // mecanisme fermé
			else if ((dataide.data1 & 0xF0) == 0x10) dataide.test = 1; // mecanisme ouvert
				else dataide.test = 3; // erreur inconnu
	return dataide.test;
 }


unsigned char Eject(DATA_IDE dataide)  //reset CD drive
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x1B;
	dataide.cmd4 = 0x02;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
	if (dataide.test == 0x51)	return 0;
	else return 1;
}

unsigned char Load(DATA_IDE dataide)  //reset CD drive
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x1B;
	dataide.cmd4 = 0x03;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
	if (dataide.test == 0x51)	return 0;
	else return 1;
}

unsigned char Read_TOC(unsigned char *data, DATA_IDE dataide )  //read TOC
{
        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x43;
	dataide.cmd1 = 0x02;
	dataide.cmd2 = 0x00;
	dataide.cmd7 = 0x10;
	dataide.cmd8 = 0x00;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.test == 0x48) dataide.test = 0x58;
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
	dataide.i = 0;
	dataide.test = 0xAA;
	while ((dataide.test != 0x58))
	{
		dataide.i++;
		if (dataide.test == 0x51 || dataide.test == 0x50)
		{
			Write_command(0xA0);
			dataide.test = 0xAA;
			dataide.j = 0;
			while ( dataide.test != 0x58 )
                        {
                            dataide.j++;
                            dataide.test = Read_Status();
                            if (dataide.j == Nb_Retry) return 2;
                        }
			
			dataide.ptest = &dataide.cmd0;
			while(dataide.ptest < &dataide.cmd13)
			{
				Write_Data(dataide.ptest);
				*dataide.ptest++;
				*dataide.ptest++;
			}
		}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 2;
	}

	

	dataide.i = 0;
	while( (dataide.test & 0x08) == 0x08 )
	{
		Read_Data(data);
		*data++;
		*(data+1) = *(data-1);
		*(data-1) = *data;
		*data = *(data+1);
		*data++;
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == 1000) return 1;
	}
	return 0;
}


unsigned char Play_MSF(unsigned char Track, unsigned char *TOC_start, DATA_IDE dataide)  //play cd track to the end of cd
{

	dataide.end_track = *(TOC_start + 3);

	if (Track > dataide.end_track) return 1;

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x47;
	dataide.cmd3 = *(TOC_start + 9 + (Track -1)*8);
	dataide.cmd4 = *(TOC_start + 10 + (Track -1)*8);
	dataide.cmd5 = *(TOC_start + 11 + (Track -1)*8);
	dataide.cmd6 = *(TOC_start + 9 + dataide.end_track*8);
	dataide.cmd7 = *(TOC_start + 10 + dataide.end_track*8);
	dataide.cmd8 = *(TOC_start + 11 + dataide.end_track*8);
	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
	if (dataide.test == 0x51)	return 2;
	else return 0;
}

unsigned char Play_MSF_address(unsigned char *Address, unsigned char *TOC_start, DATA_IDE dataide)  //play cd track to the end of cd
{

	dataide.end_track = *(TOC_start + 3);

	if (*Address > dataide.end_track) return 1;

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x47;
	dataide.cmd3 = *(Address + 1);
	dataide.cmd4 = *(Address + 2);
	dataide.cmd5 = *(Address + 3);
	dataide.cmd6 = *(TOC_start + 9 + dataide.end_track*8);
	dataide.cmd7 = *(TOC_start + 10 + dataide.end_track*8);
	dataide.cmd8 = *(TOC_start + 11 + dataide.end_track*8);
	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}

	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
	if (dataide.test == 0x51)	return 2;
	else return 0;
}


unsigned char Read_AbsMSF_SubCh(unsigned char *AMSF, DATA_IDE dataide)  //read SubChannel
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x42;
	dataide.cmd1 = 0x02;
	dataide.cmd2 = 0x40;
	dataide.cmd3 = 0x01;
	dataide.cmd7 = 0x10;
	dataide.cmd8 = 0x00;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
	dataide.i = 0;
	dataide.test = 0xAA;
	while ((dataide.test != 0x58) && (dataide.i != Nb_Retry))
	{
		dataide.i++;
		if (dataide.test == 0x51 || dataide.test == 0x50)
		{
			Write_command(0xA0);
			dataide.test = 0xAA;
			dataide.j = 0;
			while ((dataide.test != 0x58) && (dataide.j != Nb_Retry))
                        {
                            dataide.j++;
                            dataide.test = Read_Status();
                            if (dataide.j == Nb_Retry) return 2;
                        }
			
			dataide.ptest = &dataide.cmd0;
			while(dataide.ptest < &dataide.cmd13)
			{
				Write_Data(dataide.ptest);
				*dataide.ptest++;
				*dataide.ptest++;
			}
		}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 2;
	}

        dataide.ptest = &dataide.data0;
	for(dataide.i=0;dataide.i<19;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.i = 0;
	dataide.ptest = &dataide.data0;
	while(((dataide.test & 0x08) == 0x08) && (dataide.i != 18) )
	{
		Read_Data(dataide.ptest);
		*dataide.ptest++;
		*(dataide.ptest+1) = *(dataide.ptest-1);
		*(dataide.ptest-1) = *dataide.ptest;
		*dataide.ptest = *(dataide.ptest+1);
		*dataide.ptest++;
		dataide.i++;
		dataide.test = Read_Status();
	}

	*AMSF = dataide.data6;
	*(AMSF+1) = dataide.data9;
	*(AMSF+2) = dataide.data10;
	*(AMSF+3) = dataide.data11;
	if (dataide.i == 1000) return 3;
	else return dataide.data1;
}

unsigned char Read_RelMSF_SubCh(unsigned char *RMSF, DATA_IDE dataide)  //read SubChannel
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x42;
	dataide.cmd1 = 0x02;
	dataide.cmd2 = 0x40;
	dataide.cmd3 = 0x01;
	dataide.cmd7 = 0x10;
	dataide.cmd8 = 0x00;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
	dataide.i = 0;
	dataide.test = 0xAA;
	while ((dataide.test != 0x58) && (dataide.i != Nb_Retry))
	{
		dataide.i++;
		if (dataide.test == 0x51 || dataide.test == 0x50)
		{
			Write_command(0xA0);
			dataide.test = 0xAA;
			dataide.j = 0;
			while (dataide.test != 0x58)
                        {
                            dataide.j++;
                            dataide.test = Read_Status();
                            if (dataide.i == Nb_Retry) return 2;
                        }
			
			dataide.ptest = &dataide.cmd0;
			while(dataide.ptest < &dataide.cmd13)
			{
				Write_Data(dataide.ptest);
				*dataide.ptest++;
				*dataide.ptest++;
			}
		}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 2;
	}

        dataide.ptest = &dataide.data0;
	for(dataide.i=0;dataide.i<19;dataide.i++)
	{ 
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.i = 0;
	dataide.ptest = &dataide.data0;
	while(((dataide.test & 0x08) == 0x08) && (dataide.i != 18) )
	{
		Read_Data(dataide.ptest);
		*dataide.ptest++;
		*(dataide.ptest+1) = *(dataide.ptest-1);
		*(dataide.ptest-1) = *dataide.ptest;
		*dataide.ptest = *(dataide.ptest+1);
		*dataide.ptest++;
		dataide.i++;
		dataide.test = Read_Status();
	}

	*RMSF = dataide.data6;
	*(RMSF+1) = dataide.data13;
	*(RMSF+2) = dataide.data14;
	*(RMSF+3) = dataide.data15;
	if (dataide.i == 1000) return 3;
	else return dataide.data1;
}


unsigned char F_Scan(unsigned char *AMSF_start, DATA_IDE dataide)  //scan forward
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0xBA;
	dataide.cmd3 = *(AMSF_start + 1);
	dataide.cmd4 = *(AMSF_start + 2);
	dataide.cmd5 = *(AMSF_start + 3);
	dataide.cmd9 = 0x40;
	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
	dataide.test = 0xAA;
	dataide.test = Read_Status();
	dataide.end_track = 0xAA;
	dataide.end_track = Read_Error();
	if (dataide.test == 0x51)	return 1;
	else return 0;
}


unsigned char R_Scan(unsigned char *AMSF_start, DATA_IDE dataide)  //scan rewind
{
//non fonctionnel, à tester
        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0xBA;
	dataide.cmd3 = 0x10;
	dataide.cmd3 = *(AMSF_start + 1);
	dataide.cmd4 = *(AMSF_start + 2);
	dataide.cmd5 = *(AMSF_start + 3);
	dataide.cmd9 = 0x40;
	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
	dataide.test = 0xAA;
	dataide.test = Read_Status();
	dataide.end_track = 0xAA;
	dataide.end_track = Read_Error();
	if (dataide.test == 0x51)	return 1;
	else return 0;
}

unsigned char Stop(DATA_IDE dataide)  //stop play/scan
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x4E;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
	if (dataide.test == 0x51)	return 0;
	else return 1;
}

unsigned char Pause(DATA_IDE dataide)  //pause play/scan
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x4B;
	dataide.cmd8 = 0x00;
	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
	if (dataide.test == 0x51)	return 0;
	else return 1;
}

unsigned char Resume(DATA_IDE dataide)  //resume play/scan
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x4B;
	dataide.cmd8 = 0x01;
	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
	if (dataide.test == 0x51)	return 0;
	else return 1;
}


unsigned char INQUIRY(unsigned char *data, DATA_IDE dataide)  //read TOC
{

        dataide.ptest = &dataide.cmd0;
	for(dataide.i=0;dataide.i<16;dataide.i++)
	{
		*dataide.ptest = 0;
                *dataide.ptest++;
	}

	dataide.cmd0 = 0x12;
	dataide.cmd3 = 0x00;
	dataide.cmd4 = 0xFF;

	Write_command(0xA0);
	dataide.test = 0xAA;
	dataide.i = 0;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 3;
	}
	
	dataide.ptest = &dataide.cmd0;
	dataide.i = 0;
	while(dataide.ptest < &dataide.cmd13)
	{
		Write_Data(dataide.ptest);
		*dataide.ptest++;
		*dataide.ptest++;
		dataide.i++;
	}
	dataide.i = 0;
	dataide.test = 0xAA;
	while (dataide.test != 0x58)
	{
		dataide.i++;
		if (dataide.test == 0x51 || dataide.test == 0x50)
		{
			Write_command(0xA0);
			dataide.test = 0xAA;
			dataide.j = 0;
			while (dataide.test != 0x58)
                        {
                            dataide.j++;
                            dataide.test = Read_Status();
                            if (dataide.i == Nb_Retry) return 2;
                        }
			
			dataide.ptest = &dataide.cmd0;
			while(dataide.ptest < &dataide.cmd13)
			{
				Write_Data(dataide.ptest);
				*dataide.ptest++;
				*dataide.ptest++;
			}
		}
		dataide.test = 0xAA;
		dataide.test = Read_Status();
                if (dataide.i == Nb_Retry) return 2;
	}

	dataide.i = 0;
	while(((dataide.test & 0x08) == 0x08)&& (dataide.i != 64) )
	{
		Read_Data(data);
		*data++;
		*(data+1) = *(data-1);
		*(data-1) = *data;
		*data = *(data+1);
		*data++;
		dataide.i++;
		dataide.test = Read_Status();
	}
	if (dataide.i == 64) return 3;
	else return 0;
}