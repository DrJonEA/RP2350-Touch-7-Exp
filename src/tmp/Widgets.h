/*
 * Widgets.h
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#ifndef EXP_LVGLDASHBOARD_SRC_WIDGETS_H_
#define EXP_LVGLDASHBOARD_SRC_WIDGETS_H_

#include "lvgl.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <cstdint>

class Widgets {
public:
	Widgets();
	virtual ~Widgets();

	void init();


private:

	void initTile1();

	// Tile 1 - Original circular animation
	lv_obj_t *xTV;
	lv_obj_t *xTile1;
	lv_style_t xStyleTile;
	lv_style_t xLabelSt;

	lv_obj_t *pDrJonLbl;
	lv_obj_t *pBracketTop;



	static const char * xTopMap[];
};

#endif /* EXP_LVGLDASHBOARD_SRC_WIDGETS_H_ */
