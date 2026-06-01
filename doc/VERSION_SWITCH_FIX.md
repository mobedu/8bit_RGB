# 版本切换正确方法

## 问题说明

项目同时编译 effects.c 和 effects_new.c 会导致链接错误，因为两个文件都定义了相同名称的全局变量：
- system_tick_ms
- current_effect
- leds

## 解决方案：只编译当前使用的版本

### 方法1：修改项目配置文件（推荐）

编辑 8BIT-RGB.scw，在 [FILE] 部分注释掉不需要的文件：

**使用新版本（当前配置）：**
```
[FILE]
;SourceFile=effects.c       ; 注释掉旧版本
SourceFile=key.c
SourceFile=main.c
SourceFile=effects_new.c    ; 启用新版本
HeadFile=config.h
HeadFile=effects.h
HeadFile=key.h
HeadFile=ws2812.h
HeadFile=effects_new.h
```

**切换到旧版本：**
```
[FILE]
SourceFile=effects.c        ; 启用旧版本
SourceFile=key.c
SourceFile=main.c
;SourceFile=effects_new.c   ; 注释掉新版本
HeadFile=config.h
HeadFile=effects.h
HeadFile=key.h
HeadFile=ws2812.h
HeadFile=effects_new.h
```

### 方法2：临时重命名文件

- 使用新版本：将 effects.c 重命名为 effects.c.bak
- 使用旧版本：将 effects_new.c 重命名为 effects_new.c.bak

## 当前配置建议

由于 main.c 中设置了 `USE_NEW_EFFECTS 1`，建议：
1. 项目配置中只编译 effects_new.c
2. 注释掉 effects.c

这样既能避免链接错误，又能轻松切换版本。
