
#ifndef twi_h
    #define twi_h
    
    #define START_OK 	0x08
    #define START_REP	0x10
    #define ADRRW_OK	0x18
    #define ADRRW_ERR	0x20
    #define SEND_OK		0x28
    #define SEND_ERR	0x30
    #define ADRRR_OK	0x40
    #define ADRRR_ERR	0x48
    #define REC_OK		0x50
    #define REC_ERR		0x58
    
    #define	SIZE_BUFFER_I2C	10
    
    uint8_t buffer_I2C[SIZE_BUFFER_I2C];

#endif