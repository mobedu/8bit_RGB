#include "effects.h"

static unsigned char color_index;
volatile EffectMode_t current_effect = EFFECT_SLOW_FLASH;
unsigned char g_color_index;

// 红、蓝、绿、橙、青、紫、黄、粉红、天蓝、混白 (PIN.md 顺序)
static const unsigned char color_tbl[] = {
    255,0,0,        // 0: 红
    0,0,255,        // 1: 蓝
    0,255,0,        // 2: 绿
    255,128,0,      // 3: 橙
    0,255,255,      // 4: 青
    128,0,255,      // 5: 紫
    255,255,0,      // 6: 黄
    255,0,128,      // 7: 粉红
    0,128,255,      // 8: 天蓝
    255,255,255,    // 9: 混白
};

void effects_init(void) {
    color_index = 9;
    g_color_index = color_index;
    current_effect = EFFECT_SLOW_FLASH;
}

void effects_next_color(void) {
    if (++color_index >= 10) color_index = 0;
    g_color_index = color_index;
}

void effects_apply(RGB_t *leds) {
    unsigned char i, r, g, b;
    r = color_tbl[color_index * 3];
    g = color_tbl[color_index * 3 + 1];
    b = color_tbl[color_index * 3 + 2];
    for (i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}
