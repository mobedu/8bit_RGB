#include <sc.h>
#include "config.h"
#include "ws2812.h"
#include "key.h"
#include "effects.h"
#include "power.h"
#include "cds.h"
#include "rf.h"

static unsigned char power_state = 1;
static unsigned char key_pressed = 0;
static unsigned int key_press_counter = 0;

static void system_clock_init(void) {
    OSCCON = 0x70;
}

static void gpio_init(void) {
    ANSEL0 = 0;
    ANSEL1 = 0;

    // RA0: 按键，输入，上拉
    TRISA |= (1 << PIN_KEY_BIT);
    WPUA |= (1 << PIN_KEY_BIT);

    // RA1: LED供电，输出高（开）
    TRISA &= ~(1 << PIN_LED_POWER_BIT);
    PIN_LED_POWER_ON();

    // RB1: WS2812数据，输出低
    TRISB &= ~(1 << PIN_WS2812B_BIT);
    PORTB &= ~(1 << PIN_WS2812B_BIT);

    // RB4: RF SHUT，输出低（开）
    TRISB &= ~(1 << PIN_SHUT_BIT);
    PIN_SHUT_LOW();

    // ADC引脚输入
    TRISB |= (1 << 0);  // RB0
    TRISB |= (1 << 2);  // RB2
    TRISA |= (1 << 2);  // RA2
    TRISA |= (1 << 3);  // RA3
}

static void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 1333; j++) asm("nop");
    }
}

RGB_t leds[LED_COUNT];

void main(void) {
    unsigned int update_counter = 0;

    INTCON &= ~(1 << 7);
    system_clock_init();
    gpio_init();
    effects_init();

    power_state = 1;
    effects_apply(leds);
    ws2812_update(leds, LED_COUNT);

    INTCON |= (1 << 7);

    while (1) {
        asm("clrwdt");

        // 按键扫描
        if (PIN_KEY_READ() == 0) {
            if (!key_pressed) {
                delay_ms(20);
                if (PIN_KEY_READ() == 0) {
                    key_pressed = 1;
                    key_press_counter = 0;
                }
            } else {
                if (key_press_counter < 255) {
                    key_press_counter++;
                }
                if (key_press_counter == 150) {
                    // 长按：开关机
                    power_state = !power_state;
                    if (power_state) {
                        // 开机：开启LED供电，显示LED
                        PIN_LED_POWER_ON();
                        system_clock_init();
                        gpio_init();
                        effects_apply(leds);
                        ws2812_update(leds, LED_COUNT);
                    } else {
                        // 关机：关闭LED供电
                        power_off_leds(leds);
                        ws2812_update(leds, LED_COUNT);
                        PIN_LED_POWER_OFF();
                    }
                    while (PIN_KEY_READ() == 0);
                    key_pressed = 0;
                    key_press_counter = 0;
                }
            }
        } else {
            if (key_pressed) {
                if (key_press_counter < 150) {
                    if (power_state) {
                        effects_next_color();
                        effects_apply(leds);
                        ws2812_update(leds, LED_COUNT);
                    }
                }
                key_pressed = 0;
                key_press_counter = 0;
            }
        }

        delay_ms(1);
    }
}
