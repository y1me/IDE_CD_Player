#ifndef FCT_IDE_H
#define FCT_IDE_H




unsigned char Mech_Stat(void);
unsigned char Eject(void);
unsigned char Load(void);
unsigned char Read_TOC(unsigned char *);
unsigned char Play_MSF(unsigned char , unsigned char *);
unsigned char Read_AbsMSF_SubCh(unsigned char *);
unsigned char Read_RelMSF_SubCh(unsigned char *);
unsigned char F_Scan(unsigned char *);
unsigned char R_Scan(unsigned char *);
unsigned char Stop(void);
unsigned char Pause(void); 
unsigned char Resume(void); 
unsigned char INQUIRY(unsigned char *);


#endif  //FCT_IDE_H