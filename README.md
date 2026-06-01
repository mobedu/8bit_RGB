# SC8F072 智能车灯 RGB LED 驱动项目

基于 SC8F072 单片机的智能车灯驱动程序，支持 RF433 遥控、震动检测、电池管理等多种功能。

## 硬件连接

| 单片机引脚 | 功能 | 说明 |
|-----------|------|------|
| RB1 | WS2812B 数据 | 接 LED 灯带 DIN |
| RA0 | 按键输入 | 长按开关机，短按切换 |
| RA2 (AN10) | 电池检测 | ADC 输入，分压后连接 |
| RA3 (AN11) | RF433 接收 | INT0 外部中断 |
| RA4 (AN12) | 震动开关 | IOC 电平变化中断 |
| VDD | 电源正极 | 4.5V ~ 5.5V |
| VSS | 电源负极 | GND |

## 功能特点

### LED 效果 (8种模式)
1. **常亮模式** - 单色常亮，10种颜色可选
2. **慢闪模式** - 单色慢闪，10种颜色可选
3. **快闪模式** - 单色快闪，10种颜色可选
4. **呼吸模式** - 十色自动呼吸渐变
5. **慢闪幻彩** - 慢闪自动换色
6. **快闪幻彩** - 快闪自动换色
7. **警示模式** - 红/蓝快闪交替
8. **跑马模式** - 单颗跑马，彩色循环

### RF433 遥控功能
- 开关机控制
- 4H/6H/8H 定时
- 亮度调节 (4档)
- 模式切换
- 颜色切换
- 复位功能

详见：[遥控器功能说明](doc/RF433_REMOTE_SPEC.md)

### 电池管理
- 实时电压检测
- 根据电压自动限制最大亮度
- 欠压保护提示

### 震动检测
- 车行进中灯自动亮起
- 车静止 30 秒后灯自动熄灭

### 低功耗设计
- 自动睡眠模式
- 多唤醒源 (RF433/震动/按键)
- 睡眠电流 < 50μA

## 配置说明

在 `config.h` 中修改：

```c
#define LED_COUNT          24      // LED 数量
#define ENABLE_BATTERY_MONITOR  1  // 电池检测
#define ENABLE_RF433_RECEIVER   1  // RF433 遥控
#define ENABLE_VIBRATION_SENSOR 1  // 震动检测
#define ENABLE_POWER_MANAGEMENT 1  // 低功耗管理
#define AUTO_SLEEP_TIMEOUT       30 // 自动睡眠超时(秒)
```

## 芯片选型

| 芯片 | ROM | RAM | 推荐度 |
|------|-----|-----|--------|
| SC8F072 | 4K | 256B | ❌ 不够 |
| **SC8F074** | **8K** | **512B** | ✅ 推荐 |
| SC8F076 | 16K | 512B | ✅ 富裕 |

## 编译说明

1. 打开 SC8F IDE
2. 加载 `car-rgb.scw` 项目配置
3. 选择芯片型号 (SC8F074 推荐)
4. 编译并烧录

## 项目文件

```
car-rgb/
├── main.c              # 主程序
├── config.h            # 配置定义
├── effects.c/h         # LED 效果
├── effects_new.c/h     # 新版 LED 效果（开发中）
├── key.c/h             # 按键扫描
├── power.c/h           # 电源管理
├── ws2812.c/h          # WS2812B 驱动
├── doc/                # 开发文档
│   ├── README.md       # 文档索引
│   ├── LESSONS_LEARNED.md      # 踩坑记录
│   ├── BUG_FIX_WORKFLOW.md     # BUG修复流程
│   └── ...
├── README.md           # 项目说明（本文件）
└── README_DEV.md       # 开发文档入口
```

## 注意事项

1. **WDT 喂狗**: 所有阻塞操作必须喂狗 (超时约 18ms)
2. **中断优先级**: RF433 时序需要较高优先级
3. **电池分压**: RA2 需要 100k/47k 分压电阻
4. **RF433 天线**: 17cm 铜线作为天线
5. **震动开关**: 需要 10k-100k 下拉电阻
6. **中断关闭**: WS2812B 发送数据时会关闭中断，确保时序准确
7. **供电电压**: WS2812B 推荐 5V 供电，数据信号高电平应接近 VDD
8. **电平兼容**: 如果单片机 2.5V 供电而 LED 5V 供电，建议加电平转换
9. **ANSEL**: 所有用作数字 IO 的引脚必须清除对应的 ANSEL 位

## 文档参考

### 开发文档
- **[开发文档入口](README_DEV.md)** - 查看所有开发相关文档
- **[文档索引](doc/README.md)** - 开发文档目录
- **[踩坑记录](doc/LESSONS_LEARNED.md)** - SC8F072 特有问题和通用问题
- **[BUG修复流程](doc/BUG_FIX_WORKFLOW.md)** - 修复 BUG 的标准流程
- **[遥控器功能说明](doc/RF433_REMOTE_SPEC.md)**
- **[外设集成说明](doc/PERIPHERAL_INTEGRATION.md)**

### 数据手册
- **[SC8F072数据手册](/mnt/h/072_docs/)** - 完整的芯片数据手册
- **[开发经验手册](/mnt/h/072_docs/SC8F072_开发经验手册.md)** - 实战经验总结

## 版本说明

当前包含新版本灯效（7种模式），详见 [doc/NEW_EFFECTS_GUIDE.md](doc/NEW_EFFECTS_GUIDE.md)。

V1.0.4 正确的时序版本 对应3535 WS2812B灯珠
#define S0  PORTB |= (1 << PIN_WS2812B_BIT); __ws_dly = 0; __ws_dly = 0; PORTB &= ~(1 << PIN_WS2812B_BIT)
#define S1  PORTB |= (1 << PIN_WS2812B_BIT); __ws_dly = 0; __ws_dly = 0; __ws_dly = 0; __ws_dly = 0; __ws_dly = 0; PORTB &= ~(1 << PIN_WS2812B_BIT)
