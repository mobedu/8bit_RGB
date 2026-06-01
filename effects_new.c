#include <sc.h>
#include "config.h"
#include "effects_new.h"
#include "ws2812.h"

// 十色定义 (RGB)
static unsigned char color_table[10][3] = {
    {255, 0, 0},     // 0: 红
    {0, 255, 0},     // 1: 绿
    {0, 0, 255},     // 2: 蓝
    {255, 255, 0},   // 3: 黄
    {255, 0, 255},   // 4: 紫
    {0, 255, 255},   // 5: 青
    {255, 128, 0},   // 6: 橙
    {255, 0, 128},   // 7: 粉
    {128, 255, 0},   // 8: 黄绿
    {255, 255, 255}  // 9: 白
};

// ========== 2. 慢闪模式（按键换色） ==========
static unsigned char slow_flash_state = 0;
static unsigned char slow_flash_counter = 0;

void slow_flash_init(void) {
    slow_flash_state = 0;
    slow_flash_counter = 0;
    unsigned char r = color_table[g_color_index][0];
    unsigned char g = color_table[g_color_index][1];
    unsigned char b = color_table[g_color_index][2];
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

void slow_flash_update(void) {
    slow_flash_counter++;
    if (slow_flash_counter < 50) return;
    slow_flash_counter = 0;

    slow_flash_state = !slow_flash_state;
    unsigned char r = slow_flash_state ? color_table[g_color_index][0] : 0;
    unsigned char g = slow_flash_state ? color_table[g_color_index][1] : 0;
    unsigned char b = slow_flash_state ? color_table[g_color_index][2] : 0;

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

// ========== 3. 快闪模式（按键换色） ==========
static unsigned char fast_flash_state = 0;
static unsigned char fast_flash_counter = 0;

void fast_flash_init(void) {
    fast_flash_state = 0;
    fast_flash_counter = 0;
    unsigned char r = color_table[g_color_index][0];
    unsigned char g = color_table[g_color_index][1];
    unsigned char b = color_table[g_color_index][2];
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

void fast_flash_update(void) {
    fast_flash_counter++;
    if (fast_flash_counter < 10) return;
    fast_flash_counter = 0;

    fast_flash_state = !fast_flash_state;
    unsigned char r = fast_flash_state ? color_table[g_color_index][0] : 0;
    unsigned char g = fast_flash_state ? color_table[g_color_index][1] : 0;
    unsigned char b = fast_flash_state ? color_table[g_color_index][2] : 0;

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

// ========== 4. 十色呼吸 ==========
static unsigned char breath_val = 0;
static signed char breath_dir = 1;
static unsigned char breath_color_idx = 0;

void breath_10color_init(void) {
    breath_val = 0;
    breath_dir = 1;
    breath_color_idx = 0;
}

void breath_10color_update(void) {
    static unsigned char counter = 0;
    counter++;
    if (counter < 2) return;
    counter = 0;

    breath_val += breath_dir * 8;

    if (breath_val >= 250) {
        breath_val = 250;
        breath_dir = -1;
    }
    else if (breath_val <= 0) {
        breath_val = 0;
        breath_dir = 1;
        breath_color_idx = (breath_color_idx + 1) % 10;
    }

    unsigned char r = (breath_val * color_table[breath_color_idx][0]) / 255;
    unsigned char g = (breath_val * color_table[breath_color_idx][1]) / 255;
    unsigned char b = (breath_val * color_table[breath_color_idx][2]) / 255;

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

// ========== 5. 慢闪幻彩 ==========
static unsigned char slow_rainbow_state = 0;
static unsigned char slow_rainbow_counter = 0;
static unsigned char slow_rainbow_color = 0;

void slow_rainbow_init(void) {
    slow_rainbow_state = 0;
    slow_rainbow_counter = 0;
    slow_rainbow_color = 0;
}

void slow_rainbow_update(void) {
    slow_rainbow_counter++;
    if (slow_rainbow_counter < 50) return;
    slow_rainbow_counter = 0;

    slow_rainbow_state = !slow_rainbow_state;
    if (!slow_rainbow_state) {
        slow_rainbow_color = (slow_rainbow_color + 1) % 10;
    }

    unsigned char r = slow_rainbow_state ? color_table[slow_rainbow_color][0] : 0;
    unsigned char g = slow_rainbow_state ? color_table[slow_rainbow_color][1] : 0;
    unsigned char b = slow_rainbow_state ? color_table[slow_rainbow_color][2] : 0;

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

// ========== 6. 快闪幻彩 ==========
static unsigned char fast_rainbow_state = 0;
static unsigned char fast_rainbow_counter = 0;
static unsigned char fast_rainbow_color = 0;

void fast_rainbow_init(void) {
    fast_rainbow_state = 0;
    fast_rainbow_counter = 0;
    fast_rainbow_color = 0;
}

void fast_rainbow_update(void) {
    fast_rainbow_counter++;
    if (fast_rainbow_counter < 10) return;
    fast_rainbow_counter = 0;

    fast_rainbow_state = !fast_rainbow_state;
    if (!fast_rainbow_state) {
        fast_rainbow_color = (fast_rainbow_color + 1) % 10;
    }

    unsigned char r = fast_rainbow_state ? color_table[fast_rainbow_color][0] : 0;
    unsigned char g = fast_rainbow_state ? color_table[fast_rainbow_color][1] : 0;
    unsigned char b = fast_rainbow_state ? color_table[fast_rainbow_color][2] : 0;

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

// ========== 7. 警示模式（红蓝快闪） ==========
static unsigned char police_new_state = 0;
static unsigned char police_new_counter = 0;

void police_new_init(void) {
    police_new_state = 0;
    police_new_counter = 0;
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 255;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}

void police_new_update(void) {
    police_new_counter++;
    if (police_new_counter < 5) return;
    police_new_counter = 0;

    police_new_state = !police_new_state;
    unsigned char r = police_new_state ? 255 : 0;
    unsigned char g = 0;
    unsigned char b = police_new_state ? 0 : 255;

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

// ========== 8. 跑马模式 ==========
#define RUNNER_COUNT 10

static unsigned char runner_pos = 0;
static unsigned char runner_state = 0;
static unsigned char runner_loop = 0;

void runner_init(void) {
    runner_pos = 0;
    runner_state = 0;
    runner_loop = 0;

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}

void runner_update(void) {
    static unsigned char counter = 0;
    counter++;
    if (counter < 3) return;
    counter = 0;

    if (runner_state == 0) {
        for (unsigned char i = 0; i < LED_COUNT; i++) {
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = 0;
        }

        unsigned char color_idx = runner_pos % 10;
        leds[runner_pos].r = color_table[color_idx][0];
        leds[runner_pos].g = color_table[color_idx][1];
        leds[runner_pos].b = color_table[color_idx][2];

        runner_pos++;
        if (runner_pos >= RUNNER_COUNT) {
            runner_pos = 0;
            runner_state = 1;
            runner_loop = 0;
        }
    }
    else if (runner_state == 1) {
        for (unsigned char i = 0; i < LED_COUNT; i++) {
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = 0;
        }

        for (unsigned char i = 0; i < RUNNER_COUNT; i++) {
            unsigned char color_idx = (runner_pos + i) % 10;
            unsigned char pos = (runner_pos + i) % RUNNER_COUNT;
            leds[pos].r = color_table[color_idx][0];
            leds[pos].g = color_table[color_idx][1];
            leds[pos].b = color_table[color_idx][2];
        }

        runner_pos++;
        if (runner_pos >= RUNNER_COUNT) {
            runner_pos = 0;
            runner_loop++;
            if (runner_loop >= 2) {
                runner_state = 2;
                runner_pos = 0;
            }
        }
    }
    else if (runner_state == 2) {
        if (runner_pos < RUNNER_COUNT) {
            leds[runner_pos].r = 0;
            leds[runner_pos].g = 0;
            leds[runner_pos].b = 0;
            runner_pos++;
        } else {
            runner_pos = 0;
            runner_state = 0;
            runner_loop = 0;
        }
    }
}

// ========== 效果接口实现 ==========
const static Effect_t effects_new[] = {
    {slow_flash_init, slow_flash_update},
    {fast_flash_init, fast_flash_update},
    {breath_10color_init, breath_10color_update},
    {slow_rainbow_init, slow_rainbow_update},
    {fast_rainbow_init, fast_rainbow_update},
    {police_new_init, police_new_update},
    {runner_init, runner_update}
};

void effect_new_init(void) {
    if (current_effect < 7) {
        effects_new[current_effect].init();
    }
}

void effect_new_execute(EffectMode_t mode) {
    current_effect = mode;
    effects_new[mode].init();
}

void effects_new_update(void) {
    if (current_effect < 7) {
        effects_new[current_effect].update();
    }
}
