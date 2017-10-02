/*
 * MAX7219.cpp
 *
 *  Created on: 29-Sep-2017
 *      Author: mahesh
 */

#include "MAX7219.h"

MAX7219::MAX7219(SPI_HandleTypeDef* hSPI)
	:_hSPI(hSPI)
{
	// TODO Auto-generated constructor stub

}

MAX7219::~MAX7219() {
	// TODO Auto-generated destructor stub
}

// send 16 bit data packet
void MAX7219::sendPacket(MAX7129_REG reg, uint8_t data)
{
	// CS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

	//uint16_t packet = (reg << 8) | data;
	uint8_t packet[2];
	packet[0] = reg;
	packet[1] = data;

	HAL_SPI_Transmit(const_cast<SPI_HandleTypeDef*>(_hSPI), (uint8_t*)&packet, 2, 100);

	// CS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

}

void MAX7219::power(bool on)
{
	uint8_t val = on? 1 : 0;
	sendPacket(eMAX7129_REG_Shutdown, val);
}

void MAX7219::setIntensity(uint8_t val)
{
	sendPacket(eMAX7129_REG_Intensity, val & 0xf);
}

void MAX7219::setScanLimit(uint8_t dig)
{
	sendPacket(eMAX7129_REG_ScanLimit, dig & 0x7);
}

// set "pixel" - LED at (i, j)
void MAX7219::setPixel(uint8_t i, uint8_t j)
{
	i = i & 8;
	j = j & 8;

}
// turn all LEDs off
void MAX7219::clear()
{

}
