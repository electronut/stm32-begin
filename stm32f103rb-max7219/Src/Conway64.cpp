/*
 * Conway.cpp
 *
 *  Created on: 29-Sep-2017
 *      Author: mahesh
 */

#include "MAX7219.h"

#include "Conway64.h"

// The Conway Task function
void conwayTaskFunc(void const * arg)
{
	// that's the way the C++ wind blows...
	Conway64* conway = const_cast<Conway64*>(static_cast<const Conway64*>(arg));

	conway->testInit();

	for(;;)
	{
		conway->test();

		osDelay(250);
	}
}

Conway64::Conway64(SPI_HandleTypeDef* hSPI)
{
	// create MAX7129
	_max7219 = new MAX7219(hSPI);
}

Conway64::~Conway64() {
	delete _max7219;
}

// initialize
void Conway64::init()
{
	// create Conway task
	osThreadDef(conwayTask, conwayTaskFunc, osPriorityNormal, 0, 128);
	_conwayTaskHandle = osThreadCreate(osThread(conwayTask), this);
}

// test init SPI
void Conway64::testInit()
{
	_max7219->power(true);
	_max7219->setIntensity(5);
	_max7219->setScanLimit(7);

	for (int i = 1 ; i <= 8; i++) {
		_max7219->sendPacket(static_cast<MAX7129_REG>(i), 0);
	}
}

void Conway64::addGlider(int i, int j) {
}

void Conway64::update()
{

}

void Conway64::render()
{

}

// test SPI
void Conway64::test()
{
	for (int j = 1 ; j <= 8; j++) {
		for (int i = 0 ; i < 8; i++) {
			_max7219->sendPacket(static_cast<MAX7129_REG>(j), 1 << i);
			osDelay(100);
		}
	}
}
