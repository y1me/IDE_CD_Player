#include <p18f6722.h>
#include <HardwareProfile.h>
#include <interface_register.h>


unsigned char Mech_Stat(void)  //reset CD drive
{
	 unsigned int i,j;
	 unsigned char atest,test,cmd[16],data[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0xBD;
	cmd[9] = 0x08;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[12])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
	i = 0;
	test = 0xAA;
	while (test != 0x58) 
	{
		i++;
		if (test == 0x51 || test == 0x50)
		{
			Write_command(0xA0);
			test = 0xAA;
			j = 0;
			while (test != 0x58)
                        {
                            j++;
                            test = Read_Status();
                            if (j == Nb_Retry) return 3;
                        }
			
			ptest = &cmd[0];
			while(ptest < &cmd[12])
			{
				Write_Data(ptest);
				*ptest++;
				*ptest++;
			}
		}
		test = 0xAA;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}

	ptest = &data[0];
	i = 0;
	while(((test & 0x08) == 0x08) && (i != 12) )
	{
		Read_Data(ptest);
		*ptest++;
		*(ptest+1) = *(ptest-1);
		*(ptest-1) = *ptest;
		*ptest = *(ptest+1);
		*ptest++;
		i++;
		test = Read_Status();
	}

	if ((data[0]  != 0x00) && ((data[1] & 0xE0) != 0x00)) test = 2; //erreur  mecanisme non prés
	else 	if ((data[1] & 0xF0) == 0x00) test = 0; // mecanisme fermé
			else if ((data[1] & 0xF0) == 0x10) test = 1; // mecanisme ouvert
				else test = 3; // erreur inconnu
	return test;
 }


unsigned char Eject(void)  //reset CD drive
{

	 unsigned int i;
	 unsigned char test,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0x1B;
	cmd[4] = 0x02;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
		test = 0xAA;
		test = Read_Status();
	if (test == 0x51)	return 0;
	else return 1;
}

unsigned char Load(void)  //reset CD drive
{

	 unsigned int i;
	 unsigned char test,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0x1B;
	cmd[4] = 0x03;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
		test = 0xAA;
		test = Read_Status();
	if (test == 0x51)	return 0;
	else return 1;
}

unsigned char Read_TOC(unsigned char *data)  //read TOC
{
	 unsigned int i,j;
	 unsigned char test,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}
	cmd[0] = 0x43;
	cmd[1] = 0x02;
	cmd[2] = 0x00;
	cmd[7] = 0x10;
	cmd[8] = 0x00;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (test == 0x48) test = 0x58;
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
	i = 0;
	test = 0xAA;
	while ((test != 0x58)) 
	{
		i++;
		if (test == 0x51 || test == 0x50)
		{
			Write_command(0xA0);
			test = 0xAA;
			j = 0;
			while ( test != 0x58 )
                        {
                            j++;
                            test = Read_Status();
                            if (j == Nb_Retry) return 2;
                        }
			
			ptest = &cmd[0];
			while(ptest < &cmd[13])
			{
				Write_Data(ptest);
				*ptest++;
				*ptest++;
			}
		}
		test = 0xAA;
		test = Read_Status();
                if (i == Nb_Retry) return 2;
	}

	

	i = 0;
	while( (test & 0x08) == 0x08 )
	{
		Read_Data(data);
		*data++;
		*(data+1) = *(data-1);
		*(data-1) = *data;
		*data = *(data+1);
		*data++;
		i++;
		test = Read_Status();
                if (i == 1000) return 1;
	}
	return 0;
}


unsigned char Play_MSF(unsigned char Track, unsigned char *TOC_start)  //play cd track to the end of cd
{

	 unsigned int i;
	 unsigned char test,end_track,cmd[16];
	 unsigned char *ptest;

	end_track = *(TOC_start + 3);

	if (Track > end_track) return 1;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0x47;
	cmd[3] = *(TOC_start + 9 + (Track -1)*8);
	cmd[4] = *(TOC_start + 10 + (Track -1)*8);
	cmd[5] = *(TOC_start + 11 + (Track -1)*8);
	cmd[6] = *(TOC_start + 9 + end_track*8);
	cmd[7] = *(TOC_start + 10 + end_track*8);
	cmd[8] = *(TOC_start + 11 + end_track*8);
	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
		test = 0xAA;
		test = Read_Status();
	if (test == 0x51)	return 2;
	else return 0;
}


unsigned char Read_AbsMSF_SubCh(unsigned char *AMSF)  //read SubChannel
{
	 unsigned int i,j;
	 unsigned char test,cmd[16],data[18];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}
	cmd[0] = 0x42;
	cmd[1] = 0x02;
	cmd[2] = 0x40;
	cmd[3] = 0x01;
	cmd[7] = 0x10;
	cmd[8] = 0x00;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
	i = 0;
	test = 0xAA;
	while ((test != 0x58) && (i != Nb_Retry)) 
	{
		i++;
		if (test == 0x51 || test == 0x50)
		{
			Write_command(0xA0);
			test = 0xAA;
			j = 0;
			while ((test != 0x58) && (j != Nb_Retry))
                        {
                            j++;
                            test = Read_Status();
                            if (j == Nb_Retry) return 2;
                        }
			
			ptest = &cmd[0];
			while(ptest < &cmd[13])
			{
				Write_Data(ptest);
				*ptest++;
				*ptest++;
			}
		}
		test = 0xAA;
		test = Read_Status();
                if (i == Nb_Retry) return 2;
	}

	for(i=0;i<19;i++)
	{
		data[i] = 0;
	}

	i = 0;
	ptest = &data[0];
	while(((test & 0x08) == 0x08) && (i != 18) )
	{
		Read_Data(ptest);
		*ptest++;
		*(ptest+1) = *(ptest-1);
		*(ptest-1) = *ptest;
		*ptest = *(ptest+1);
		*ptest++;
		i++;
		test = Read_Status();
	}

	*AMSF = data[6];
	*(AMSF+1) = data[9];
	*(AMSF+2) = data[10];
	*(AMSF+3) = data[11];
	if (i == 1000) return 3;
	else return data[1];
}

unsigned char Read_RelMSF_SubCh(unsigned char *RMSF)  //read SubChannel
{
	 unsigned int i,j;
	 unsigned char test,cmd[16],data[18];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}
	cmd[0] = 0x42;
	cmd[1] = 0x02;
	cmd[2] = 0x40;
	cmd[3] = 0x01;
	cmd[7] = 0x10;
	cmd[8] = 0x00;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
	i = 0;
	test = 0xAA;
	while ((test != 0x58) && (i != Nb_Retry)) 
	{
		i++;
		if (test == 0x51 || test == 0x50)
		{
			Write_command(0xA0);
			test = 0xAA;
			j = 0;
			while (test != 0x58)
                        {
                            j++;
                            test = Read_Status();
                            if (i == Nb_Retry) return 2;
                        }
			
			ptest = &cmd[0];
			while(ptest < &cmd[13])
			{
				Write_Data(ptest);
				*ptest++;
				*ptest++;
			}
		}
		test = 0xAA;
		test = Read_Status();
                if (i == Nb_Retry) return 2;
	}

	for(i=0;i<19;i++)
	{
		data[i] = 0;
	}

	i = 0;
	ptest = &data[0];
	while(((test & 0x08) == 0x08) && (i != 18) )
	{
		Read_Data(ptest);
		*ptest++;
		*(ptest+1) = *(ptest-1);
		*(ptest-1) = *ptest;
		*ptest = *(ptest+1);
		*ptest++;
		i++;
		test = Read_Status();
	}

	*RMSF = data[6];
	*(RMSF+1) = data[13];
	*(RMSF+2) = data[14];
	*(RMSF+3) = data[15];
	if (i == 1000) return 3;
	else return data[1];
}


unsigned char F_Scan(unsigned char *AMSF_start)  //scan forward
{

	 unsigned int i;
	 unsigned char test,end_track,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0xBA;
	cmd[3] = *(AMSF_start + 1);
	cmd[4] = *(AMSF_start + 2);
	cmd[5] = *(AMSF_start + 3);
	cmd[9] = 0x40;
	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
	test = 0xAA;
	test = Read_Status();
	end_track = 0xAA;
	end_track = Read_Error();
	if (test == 0x51)	return 1;
	else return 0;
}


unsigned char R_Scan(unsigned char *AMSF_start)  //scan rewind
{

	 unsigned int i;
	 unsigned char test,end_track,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0xBA;
	cmd[3] = 0x10;
	cmd[3] = *(AMSF_start + 1);
	cmd[4] = *(AMSF_start + 2);
	cmd[5] = *(AMSF_start + 3);
	cmd[9] = 0x40;
	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
	test = 0xAA;
	test = Read_Status();
	end_track = 0xAA;
	end_track = Read_Error();
	if (test == 0x51)	return 1;
	else return 0;
}

unsigned char Stop(void)  //stop play/scan
{

	 unsigned int i;
	 unsigned char test,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0x4E;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
		test = 0xAA;
		test = Read_Status();
	if (test == 0x51)	return 0;
	else return 1;
}

unsigned char Pause(void)  //pause play/scan
{

	 unsigned int i;
	 unsigned char test,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0x4B;
	cmd[8] = 0x00;
	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
		test = 0xAA;
		test = Read_Status();
	if (test == 0x51)	return 0;
	else return 1;
}

unsigned char Resume(void)  //resume play/scan
{

	 unsigned int i;
	 unsigned char test,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}

	cmd[0] = 0x4B;
	cmd[8] = 0x01;
	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
		test = 0xAA;
		test = Read_Status();
	if (test == 0x51)	return 0;
	else return 1;
}


unsigned char INQUIRY(unsigned char *data)  //read TOC
{
	 unsigned int i,j;
	 unsigned char test,cmd[16];
	 unsigned char *ptest;

	for(i=0;i<16;i++)
	{
		cmd[i] = 0;
	}
	cmd[0] = 0x12;
	cmd[3] = 0x00;
	cmd[4] = 0xFF;

	Write_command(0xA0);
	test = 0xAA;
	i = 0;
	while (test != 0x58)
	{
		i++;
		test = Read_Status();
                if (i == Nb_Retry) return 3;
	}
	
	ptest = &cmd[0];
	i = 0;
	while(ptest < &cmd[13])
	{
		Write_Data(ptest);
		*ptest++;
		*ptest++;
		i++;
	}
	i = 0;
	test = 0xAA;
	while (test != 0x58) 
	{
		i++;
		if (test == 0x51 || test == 0x50)
		{
			Write_command(0xA0);
			test = 0xAA;
			j = 0;
			while (test != 0x58)
                        {
                            j++;
                            test = Read_Status();
                            if (i == Nb_Retry) return 2;
                        }
			
			ptest = &cmd[0];
			while(ptest < &cmd[13])
			{
				Write_Data(ptest);
				*ptest++;
				*ptest++;
			}
		}
		test = 0xAA;
		test = Read_Status();
                if (i == Nb_Retry) return 2;
	}

	i = 0;
	while(((test & 0x08) == 0x08)&& (i != 64) )
	{
		Read_Data(data);
		*data++;
		*(data+1) = *(data-1);
		*(data-1) = *data;
		*data = *(data+1);
		*data++;
		i++;
		test = Read_Status();
	}
	if (i == 64) return 3;
	else return 0;
}