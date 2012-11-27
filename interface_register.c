#include "HardwareProfile.h"
#include <p18f6722.h>
#include "delays.h"

void Reset_Hard(void)  //reset CD drive
{
	CS0 = 0;
	CS1 = 0;
	DA0 = 1;
	DA1 = 1;
	DA2 = 1;
	DMACK =1;
	DIOR =1;
	DIOW =1;

	RST = 1;
	Delay10KTCYx(2);//wait 1ms*x
	RST = 0;
	Delay10TCYx(100); //wait 1탎*x
	RST = 1;
	Delay10KTCYx(10);//wait 1ms*x
}
unsigned char Read_Error(void)  //read error register
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;

	CS0 = 0;
	CS1 = 1;
	DA2 = 0;
	DA1 = 0;
	DA0 = 1;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;


	return temp;
}

unsigned char Read_Sect_Count(void)  //read sector count
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 0;
	DA1 = 1;
	DA0 = 0;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;

	return temp;
}

void Write_Sect_Count(unsigned char data)  //write sector count
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 0; 
	DA1 = 1;
	DA0 = 0;

	DIOW =1;
	PORT_DBUS_L = data;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}

unsigned char Read_Sect_Number(void)  //read sector number
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;

	DIOR = 1;
	CS0 = 0;
	CS1 = 1;
	DA2 = 0;
	DA1 = 1;
	DA0 = 1;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;

	return temp;
}

void Write_Sect_Number(unsigned char data)  //write sector number
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 0;
	DA1 = 1;
	DA0 = 1;

	DIOW =1;
	PORT_DBUS_L = data;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}

unsigned char Read_Status(void)  //read status register
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;

	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 1;
	DA0 = 1;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;

	return temp;
}

unsigned char Read_Alt_status(void)  //read Alternate status register
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;

	CS0 = 1;
	CS1 = 0;
	DA2 = 1;
	DA1 = 1;
	DA0 = 0;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;

	return temp;
}

void Write_command(unsigned char command)  //write command register
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;

	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 1;
	DA0 = 1;

	DIOW =1;
	PORT_DBUS_L = command;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;

}

unsigned char Read_Cyl_high(void)  //read Cylinder high register
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 0;
	DA0 = 1;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;

	return temp;
}

void Write_Cyl_high(unsigned char data)  //write Cylinder high register
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 0;
	DA0 = 1;

	DIOW =1;
	PORT_DBUS_L = data;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}

unsigned char Read_Cyl_low(void)  //read Cylinder low register
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 0;
	DA0 = 0;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;

	return temp;
}

void Write_Cyl_low(unsigned char data)  //write Cylinder low register
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 0;
	DA0 = 0;

	DIOW =1;
	PORT_DBUS_L = data;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}

void Read_Data(unsigned char *pdata)  //read data register
{
	//unsigned int temp = 0;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;

	DIOR =1;

	CS0 = 0;
	CS1 = 1;
	DA2 = 0;
	DA1 = 0;
	DA0 = 0;

	DIOR =0;
	Delay1TCY(); //wait 0.1탎
	*(pdata+1) = PORT_DBUS_L;
	*pdata = PORT_DBUS_H;
	CS0 = 0;
	CS1 = 0;
	DIOR =1;

}

void Write_Data(unsigned char *pdata)  //write data register
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;

	CS0 = 0;
	CS1 = 1;
	DA2 = 0;
	DA1 = 0;
	DA0 = 0;

	DIOW =1;
	PORT_DBUS_L = *pdata;
	PORT_DBUS_H = *(pdata + 1);
	DIOW =0;
	Delay1TCY(); //wait 0.1탎*x
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}

void Write_Dev_Ctr(unsigned char data)  //write  Device Control register
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;
	CS0 = 1;
	CS1 = 0;
	DA2 = 1;
	DA1 = 1;
	DA0 = 0;

	DIOW =1;
	PORT_DBUS_L = data;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}

unsigned char Read_Dev_Head(void)  //read Device Head register
{
	unsigned char temp;
	TRIS_DBUS_L = INPUT_PORT;
	TRIS_DBUS_H = INPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 1;
	DA0 = 0;

	DIOR =1;
	Delay10TCYx(1); //wait 1탎*x
	DIOR =0;
	Delay1TCY(); //wait  0.1탎
	temp = PORT_DBUS_L;
	DIOR =1;
	CS0 = 0;
	CS1 = 0;

	return temp;
}

void Write_Dev_Head(unsigned char data)  //write Device Head register
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 1;
	DA1 = 1;
	DA0 = 0;

	DIOW =1;
	PORT_DBUS_L = data;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}

void Write_Features(unsigned char data)  //read Features register
{
	TRIS_DBUS_L = OUTPUT_PORT;
	TRIS_DBUS_H = OUTPUT_PORT;
	CS0 = 0;
	CS1 = 1;
	DA2 = 0;
	DA1 = 0;
	DA0 = 1;

	DIOW =1;
	PORT_DBUS_L = data;
	Delay10TCYx(1); //wait 1탎*x
	DIOW =0;
	Delay1TCY(); //wait 0.1탎
	DIOW =1;
	CS0 = 0;
	CS1 = 0;
}