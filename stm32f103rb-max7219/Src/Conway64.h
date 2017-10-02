/*
 * Conway.h
 *
 *  Created on: 29-Sep-2017
 *      Author: mahesh
 */

#ifndef CONWAY64_H_
#define CONWAY64_H_

#include <stdint.h>
#include "cmsis_os.h"

class MAX7219;

class Conway64 {
public:
	Conway64(SPI_HandleTypeDef* hSPI);
	virtual ~Conway64();

	// initialize
	void init();

	// add glider with top left cell at (i, j)
	void addGlider(int i, int j);

	// update simulation
	void update();

	// render to LED grid
	void render();

	// test init SPI
	void testInit();

	// test SPI
	void test();

private:

	uint8_t _grid[8][8];

	MAX7219* _max7219;

	osThreadId _conwayTaskHandle;
};

#endif /* CONWAY64_H_ */
