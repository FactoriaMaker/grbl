
#include "grbl.h"
#include "current.h"

bool i2c_flag = 0;

void current_init(){

	uint8_t data[2];

	if(!i2c_flag){
		I2C_Init();
		i2c_flag = 1;
	}

	//Write Wiper 1 X Axis
	data[0] = 0x10;
	data[1] = wiper_calc(settings.current_x);
	I2CWriteByte(0x2C,data,2);

	//Write Wiper 2 Y Axis
	data[0] = 0x60;
	data[1] = wiper_calc(settings.current_y);
	I2CWriteByte(0x2C,data,2);

	//Write Wiper 3 Z Axis
	data[0] = 0x70;
	data[1] = wiper_calc(settings.current_z);
	I2CWriteByte(0x2C,data,2);
    
	//Activate Resistors
	data[0] = 0x43;
	data[1] = 0xFF;
	I2CWriteByte(0x2C,data,2);
	data[0] = 0xA3;
	data[1] = 0xFF;
	I2CWriteByte(0x2C,data,2);

}

uint8_t wiper_calc(float current) {
	float error=0;
	error = (float)(-243.56*(pow(current,2)) + 643.69*current - 79.71);
	current = current + error*0.001;
	return (uint8_t)(12.313*(pow(current,2)) + 18.898*current + 4.2377);
}