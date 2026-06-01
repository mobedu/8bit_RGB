#ifndef __CONFIG_H
#define __CONFIG_H

#include <sc.h>

#define USE_16MHZ        1
#if USE_16MHZ
#define _XTAL_FREQ       16000000UL
#else
#define _XTAL_FREQ       4000000UL
#endif

#define LED_COUNT        10

// ========== 引脚定义 (按 PIN.md，SC8F073更新) ==========
#define PIN_KEY_BIT     0    // RA0 bit position - 按键
#define PIN_SHUT_BIT    4    // RB4 bit position - RF SHUT
#define PIN_LED_POWER_BIT 1  // RA1 bit position - WS2812供电控制
#define PIN_WS2812B_BIT 1    // RB1 bit position - WS2812数据

#define PIN_KEY_READ()  ((PORTA >> PIN_KEY_BIT) & 1)
#define PIN_SHUT_LOW()  PORTB &= ~(1 << PIN_SHUT_BIT)
#define PIN_SHUT_HIGH() PORTB |= (1 << PIN_SHUT_BIT)
#define PIN_LED_POWER_ON()  PORTA |= (1 << PIN_LED_POWER_BIT)
#define PIN_LED_POWER_OFF() PORTA &= ~(1 << PIN_LED_POWER_BIT)
#define PIN_WS2812B_LOW()  PORTB &= ~(1 << PIN_WS2812B_BIT)
#define PIN_WS2812B_HIGH() PORTB |= (1 << PIN_WS2812B_BIT)

// ========== ADC 配置 ==========
#define PIN_BAT_ADC      RB0      // 电池电压检测 (AN8)
#define PIN_CDS_ADC      RB2      // 光敏电阻检测 (AN10)
#define ADC_REF_MV       2400     // 参考电压 2.4V
#define ADC_RESOLUTION   4095     // 12位 ADC (0-4095)

// 电池分压: R1=300K, R2=100K, 分压比 = 100K/(300K+100K) = 0.25
// 测量范围: 2.4V / 0.25 = 9.6V (实际需要 0-4.2V)
#define BAT_R1_OHM       300000
#define BAT_R2_OHM       100000
#define BAT_DIVIDER      ((BAT_R2_OHM * 1000) / (BAT_R1_OHM + BAT_R2_OHM))

// 光敏分压: R1=30K, R2=10K, 分压比 = 10K/(30K+10K) = 0.25
// 测量范围: 2.4V / 0.25 = 9.6V (实际需要 0-6V)
#define CDS_R1_OHM       30000
#define CDS_R2_OHM       10000
#define CDS_DIVIDER      ((CDS_R2_OHM * 1000) / (CDS_R1_OHM + CDS_R2_OHM))

// ========== 电池保护参数 ==========
#define BAT_PROTECT_MV   2700     // 低电压保护 2.7V
#define BAT_RECOVER_MV   3100     // 恢复电压 3.1V
#define BAT_MAX_MV       4200     // 电池满电 4.2V
#define BAT_MIN_MV       0        // 电池最低 0V

// ========== 光敏参数 ==========
#define CDS_DARK_THRESH  1000     // 暗阈值 (ADC值)
#define CDS_BRIGHT_THRESH 3000    // 亮阈值

// ========== 外设使能 ==========
#define ENABLE_BATTERY_MONITOR    1
#define ENABLE_CDS_SENSOR         1
#define ENABLE_VIBRATION_SENSOR   1
#define ENABLE_RF433_CONTROL      1
#define ENABLE_POWER_MANAGEMENT   1

#define BATTERY_CHECK_INTERVAL    5000
#define CDS_CHECK_INTERVAL        1000
#define AUTO_SLEEP_TIMEOUT        30

// ========== 电池规格 ==========
#define BAT_CAPACITY_MAH          1800

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB_t;

typedef struct {
    void (*init)(void);
    void (*update)(void);
} Effect_t;

typedef enum {
    EFFECT_SLOW_FLASH = 0,
    EFFECT_FAST_FLASH,
    EFFECT_BREATH_10COLOR,
    EFFECT_SLOW_RAINBOW,
    EFFECT_FAST_RAINBOW,
    EFFECT_POLICE_NEW,
    EFFECT_MARQUEE_NEW,
    EFFECT_COUNT_NEW
} EffectMode_t;

extern volatile EffectMode_t current_effect;
extern RGB_t leds[LED_COUNT];
extern unsigned char g_color_index;

#endif
