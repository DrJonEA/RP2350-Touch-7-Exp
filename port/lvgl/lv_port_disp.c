/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include "pio_rgb.h"
#include "bsp_st7262.h"
#include "rp_pico_alloc.h"

#define MY_DISP_HOR_RES (800)
#define MY_DISP_VER_RES (480)


static lv_color_t *buf_1;
static lv_color_t *buf_2;

static lv_area_t last_area;

static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/

static void disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
    bsp_display_interface_t *display_if = (bsp_display_interface_t *)drv->user_data;
#if 1
    display_if->flush_dma(NULL, NULL);
#else

    uint16_t *framebuffer = pio_rgb_get_free_framebuffer();
    
    lv_color_t *color_last_p = (color_p == buf_1) ? buf_2 : buf_1;


    uint16_t full_width = (last_area.x2 - last_area.x1) + 1;
    uint16_t full_height = (last_area.y2 - last_area.y1) + 1;

    for (size_t i = 0; i < full_height; i++)
    {
        for (size_t j = 0; j < full_width; j++)
        {
            framebuffer[(i + last_area.y1) * MY_DISP_HOR_RES + j + last_area.x1] = lv_color_to16(color_last_p[i * full_width + j]);
        }
    }

    full_width = (area->x2 - area->x1) + 1;
    full_height = (area->y2 - area->y1) + 1;

    for (size_t i = 0; i < full_height; i++)
    {
        for (size_t j = 0; j < full_width; j++)
        {
            framebuffer[(i + area->y1) * MY_DISP_HOR_RES + j + area->x1] = lv_color_to16(color_p[i * full_width + j]);
        }
    }

    display_if->flush_dma(NULL, NULL);
    drv->draw_buf->buf1 = color_last_p;
    // 保存上一帧
    memcpy(&last_area, area, sizeof(lv_area_t));
    // lv_disp_flush_ready(drv);
#endif
}


static void disp_flush_done(void)
{
    lv_disp_flush_ready(&disp_drv);
}

void lv_port_disp_init(void)
{
    bsp_display_interface_t *display_if;
    pio_rgb_info_t rgb_info;
    rgb_info.width = MY_DISP_HOR_RES;
    rgb_info.height = MY_DISP_VER_RES;
    rgb_info.transfer_size = MY_DISP_HOR_RES * 80;
    rgb_info.pclk_freq = BSP_LCD_PCLK_FREQ;
    rgb_info.mode.double_buffer = true;
    rgb_info.mode.enabled_transfer = true;
    rgb_info.mode.enabled_psram = true;
    rgb_info.framebuffer1 = rp_mem_malloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(uint16_t));
    rgb_info.framebuffer2 = rp_mem_malloc(MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(uint16_t));
    rgb_info.transfer_buffer1 = malloc(rgb_info.transfer_size * sizeof(uint16_t));
    rgb_info.transfer_buffer2 = malloc(rgb_info.transfer_size * sizeof(uint16_t));
    rgb_info.dma_flush_done_cb = disp_flush_done;

    bsp_display_info_t display_info;
    display_info.width = MY_DISP_HOR_RES;
    display_info.height = MY_DISP_VER_RES;
    display_info.brightness = 100;
    display_info.dma_flush_done_cb = NULL;
    display_info.user_data = &rgb_info;

    bsp_display_new_st7262(&display_if, &display_info);
    display_if->init();

    static lv_disp_draw_buf_t draw_buf_dsc_1;
#if 1
    lv_disp_draw_buf_init(&draw_buf_dsc_1, rgb_info.framebuffer2, rgb_info.framebuffer1, MY_DISP_HOR_RES * MY_DISP_VER_RES);   /*Initialize the display buffer*/
#else 
    buf_1 = malloc(MY_DISP_HOR_RES * 20 * sizeof(lv_color_t));
    buf_2 = malloc(MY_DISP_HOR_RES * 20 * sizeof(lv_color_t));
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 20);   /*Initialize the display buffer*/
#endif
    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/


    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;
    disp_drv.user_data = display_if;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_1;

    /*Required for Example 3)*/
#if 1 
    disp_drv.full_refresh = 1;
#endif 
    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}


#endif
