#include "grbl.h"
#include "twi.h"

void I2C_Init(void)
{
    //set SCL to 400kHz
    TWSR = 0x00;
    TWBR = 0x0C;
    //enable TWI
    TWCR = (1<<TWEN);
}

//start condition
void TWIStart(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

//stop condition
void TWIStop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

//write over I2C
void TWIWrite(uint8_t u8data)
{
    TWDR = u8data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

/*
//read byte with ACK
uint8_t TWIReadACK(void)
{
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
  while ((TWCR & (1<<TWINT)) == 0);
  return TWDR;
}

//read byte with NACK
uint8_t TWIReadNACK(void)
{
  TWCR = (1<<TWINT)|(1<<TWEN);
  while ((TWCR & (1<<TWINT)) == 0);
  return TWDR;
}

*/

//get status of I2C
uint8_t TWIGetStatus(void)
{
    uint8_t status;
    //mask status
    status = TWSR & 0xF8;
    return status;
}



uint8_t I2CWriteByte(uint8_t u8addr, uint8_t* buffer_I2C, uint8_t size)
{
	int i = 0; 

    TWIStart();
    if (TWIGetStatus() != START_OK)
        return 0;
    //select devise and send A2 A1 A0 address bits
    u8addr = u8addr << 1;
    TWIWrite(u8addr);
    //send the data
    for ( i=0 ; i<=size-1 ; i++){
        TWIWrite(buffer_I2C[i]);
    }
    TWIStop();
}