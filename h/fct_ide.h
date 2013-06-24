#ifndef FCT_IDE_H
#define FCT_IDE_H

#include "user_interface.h"

unsigned char Mech_Stat(DATA_IDE );
unsigned char Eject(DATA_IDE );
unsigned char Load(DATA_IDE );
unsigned char Read_TOC(unsigned char *, DATA_IDE );
unsigned char Play_MSF(unsigned char, unsigned char *, DATA_IDE );
unsigned char Play_MSF_address(unsigned char *, unsigned char *, DATA_IDE );
unsigned char Read_AbsMSF_SubCh(unsigned char *, DATA_IDE );
unsigned char Read_RelMSF_SubCh(unsigned char *, DATA_IDE );
unsigned char F_Scan(unsigned char *, DATA_IDE );
unsigned char R_Scan(unsigned char *, DATA_IDE );
unsigned char Stop(DATA_IDE);
unsigned char Pause(DATA_IDE);
unsigned char Resume(DATA_IDE);
unsigned char INQUIRY(unsigned char *, DATA_IDE );

#endif  //FCT_IDE_H