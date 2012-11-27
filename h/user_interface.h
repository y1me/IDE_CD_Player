#ifndef USER_INT_H
#define USER_INT_H


/** S T R U C T U R E S ******************************************************/
typedef union DATA_PACKET
{
    unsigned char byte[64];  //For byte access
    
    struct 
    {
        unsigned char Device_Type;
        unsigned char RMB_MSB;

        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;

        unsigned char Vend_Id0;
		unsigned char Vend_Id1;
        unsigned char Vend_Id2;
		unsigned char Vend_Id3;
        unsigned char Vend_Id4;
		unsigned char Vend_Id5;
        unsigned char Vend_Id6;
		unsigned char Vend_Id7;

        unsigned char Prod_Id0;
		unsigned char Prod_Id1;
        unsigned char Prod_Id2;
		unsigned char Prod_Id3;
        unsigned char Prod_Id4;
		unsigned char Prod_Id5;
        unsigned char Prod_Id6;
		unsigned char Prod_Id7;
        unsigned char Prod_Id8;
		unsigned char Prod_Id9;
        unsigned char Prod_Id10;
		unsigned char Prod_Id11;
        unsigned char Prod_Id12;
		unsigned char Prod_Id13;
        unsigned char Prod_Id14;
		unsigned char Prod_Id15;

        unsigned char Prod_Rev0;
		unsigned char Prod_Rev1;
        unsigned char Prod_Rev2;
		unsigned char Prod_Rev3;
    };

} DATA_PACKET;

typedef union DATA_SPI
{
    unsigned char _byte[SPI_DATA_SIZE];  //For byte access

    struct
    {
        unsigned char DataToWrite;
        unsigned char DataRead;
        unsigned char DataWrite;
        unsigned char CSTiming;
    };

} DATA_SPI;

typedef union DATA_DISPLAY
{
    unsigned char _byte[DISPLAY_DATA_SIZE];  //For byte access

    struct
    {
        unsigned char DataToWrite;
        unsigned char DataRead;
        unsigned char DataWrite;
        unsigned char CSTiming;
    };

} DATA_DISPLAY;
/** P U B L I C  P R O T O T Y P E S *****************************************/


#endif //PICDEM_FS_DEMO_H
