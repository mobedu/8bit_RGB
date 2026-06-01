#ifndef __EFFECTS_NEW_H
#define __EFFECTS_NEW_H

#include <sc.h>
#include "config.h"

// 颜色选择（用于按键切换）
extern unsigned char g_color_index;

void effect_new_init(void);
void effect_new_execute(EffectMode_t mode);
void effects_new_update(void);

#endif
