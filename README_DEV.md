# 项目开发文档索引

## 📚 核心文档

| 文档 | 说明 | 适用场景 |
|------|------|---------|
| [BUG修复工作流程](doc/BUG_FIX_WORKFLOW.md) | 修复BUG的标准流程 | 每次修复BUG时遵循 |
| [踩坑记录与最佳实践](doc/LESSONS_LEARNED.md) | 遇到的问题和解决方案 | 类似问题快速查阅 |
| [版本切换说明](doc/VERSIONS.md) | 新旧版本功能对比 | 选择使用哪个版本 |
| [版本切换修复](doc/VERSION_SWITCH_FIX.md) | 版本切换的正确方法 | 切换版本时参考 |

---

## 🚀 快速开始

### 新团队成员
1. 阅读 [doc/LESSONS_LEARNED.md](doc/LESSONS_LEARNED.md) - 了解常见坑
2. 阅读 [doc/BUG_FIX_WORKFLOW.md](doc/BUG_FIX_WORKFLOW.md) - 学习修复流程

### 遇到编译错误
1. 查看 `output/cmscerr.err` 获取错误信息
2. 参考 [doc/LESSONS_LEARNED.md](doc/LESSONS_LEARNED.md) 中的"常见错误代码"
3. 按照工作流程修复

### 切换版本
1. 参考 [doc/VERSION_SWITCH_FIX.md](doc/VERSION_SWITCH_FIX.md)
2. 修改项目配置文件 `.scw`
3. 修改 `main.c` 中的宏定义

---

## 📖 文档维护

### 添加新经验
遇到新问题时，在 [doc/LESSONS_LEARNED.md](doc/LESSONS_LEARNED.md) 中添加：
- 问题描述
- 根本原因
- 错误示例
- 正确解决方案
- 检查清单

### 更新工作流程
如果发现更好的修复流程，更新 [doc/BUG_FIX_WORKFLOW.md](doc/BUG_FIX_WORKFLOW.md)

---

## 🔗 外部参考

- SC8F系列单片机数据手册
- SDCC编译器文档
- 项目特定：8bit-RGB灯效实现

---

*本文档索引会随着项目发展持续更新*
