/*
 * Widgets.cpp
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#include "Widgets.h"
#include <cstdio>

const char * Widgets::xTopMap[] = {"1", "2", "3", "4", "5" };


Widgets::Widgets() {

}

Widgets::~Widgets() {
	// TODO Auto-generated destructor stub
}



void Widgets::init() {

	 /*Create tileview*/
	xTV = lv_tileview_create(lv_scr_act());
	lv_obj_set_scrollbar_mode(xTV,  LV_SCROLLBAR_MODE_OFF);

	initTile1();
}

void Widgets::initTile1() {

	/*Tile1: */
	xTile1 = lv_tileview_add_tile(xTV, 0, 0,  LV_DIR_ALL);
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);

	lv_style_init(&xLabelSt);
	lv_style_set_text_font(&xLabelSt, &lv_font_montserrat_32);
	lv_style_set_text_color(
			&xLabelSt,
			lv_color_make(0, 0x40, 0x40));


	pDrJonLbl = lv_label_create(xTile1);
	lv_label_set_long_mode(pDrJonLbl, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
	lv_label_set_text(pDrJonLbl, "DrJonEA");
	lv_obj_set_width(pDrJonLbl, hor);
	lv_obj_set_style_text_align(pDrJonLbl, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_align(pDrJonLbl, LV_ALIGN_CENTER,  0, 0);
	lv_obj_add_style(pDrJonLbl , &xLabelSt,  LV_PART_MAIN);

	//pBracketTop = lv_btnmatrix_create(xTile1);
	l//v_btnmatrix_set_map(pBracketTop, xTopMap);
	//lv_obj_align(pBracketTop, LV_ALIGN_CENTER, 0, 0);
	//lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);

}


