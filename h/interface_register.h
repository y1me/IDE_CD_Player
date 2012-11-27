#ifndef INT_REG_H
#define INT_REG_H


void Reset_Hard(void);
unsigned char Read_Error(void);  
unsigned char Read_Sect_Count(void);
void Write_Sect_Count(unsigned char); 
unsigned char Read_Sect_Number(void);
void Write_Sect_Number(unsigned char); 
unsigned char Read_Status(void);
unsigned char Read_Alt_status(void);
void Write_command(unsigned char );
unsigned char Read_Cyl_high(void);
void Write_Cyl_high(unsigned char );
unsigned char Read_Cyl_low(void);
void Write_Cyl_low(unsigned char );
void Read_Data(unsigned char *);
void Write_Data(unsigned char *);
void Write_Dev_Ctr(unsigned char );
unsigned char Read_Dev_Head(void);
void Write_Dev_Head(unsigned char );
void Write_Features(unsigned char);

#endif  //INT_REG_H