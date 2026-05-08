#ifndef SRC_BRACKET_CORNER_H_
#define SRC_BRACKET_CORNER_H_

#include "lvgl.h"

// Simple test: 100x50 solid orange rectangle
// Format: XRGB8888 (blue, green, red, reserved - little-endian)
// Orange: 0xFF9F1C = B:1C, G:9F, R:FF, X:00

// Pre-filled array with all pixels set to orange
static const uint8_t bracket_corner_data[100 * 50 * 4] = {
    // All 20000 bytes (5000 pixels * 4 bytes each)
    // Each pixel is: 0x1C, 0x9F, 0xFF, 0x00 (BGR + reserved)
    // Filling 100 rows x 50 columns
    #define ORANGE_PIXEL 0x1C, 0x9F, 0xFF, 0x00
    #define FILL_ROW ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL, ORANGE_PIXEL
    FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW,
    FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW,
    FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW,
    FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW,
    FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW, FILL_ROW
};

// Image descriptor
static const lv_img_dsc_t bracket_corner_img = {
    {
        LV_IMG_CF_TRUE_COLOR,  // cf - use TRUE_COLOR not ALPHA for now
        100,                    // w
        50,                     // h
    },
    100 * 50 * 4,              // data_size
    (const uint8_t*)bracket_corner_data  // data
};

#endif /* SRC_BRACKET_CORNER_H_ */
