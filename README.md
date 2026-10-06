# MFC 曹操华容道

经典滑块益智游戏**华容道**（Klotski）的 Windows 桌面版，使用 **Visual Studio 2022（C++ / MFC / v143 工具集）** 开发。

![平台](https://img.shields.io/badge/platform-Windows-blue) ![IDE](https://img.shields.io/badge/IDE-VS2022-purple) ![语言](https://img.shields.io/badge/language-C%2B%2B%20%2F%20MFC-green)

## 功能特性

- **多个经典棋局**：横刀立马、前后围隔等，棋局数据由 `bin/sanguohrd.txt` 定义，可自行扩展
- **自动求解**：内置 BFS 广度优先搜索求解器，可自动计算最优解法
- **自动演示**：独立演示线程（`CDemoThread`），可调速播放解题步骤
- **背景音乐**：程序启动时播放 `bin/bk.mp3`
- **华容道人物棋子**：曹操、关羽、张飞、赵云、马超、黄忠、四个兵，位图资源在 `res/`、`res3/` 目录

## 下载

无需编译，直接到 [Releases](https://github.com/foolpanda/MFCcaocaohrd/releases) 页面下载对应压缩包（x64 为 64 位，x86 为 32 位），解压后运行 `MFCcaocaohrd_xxx.exe` 即可。

> 压缩包内已包含运行所需的棋局文件 `sanguohrd.txt` 和背景音乐 `bk.mp3`，请保持它们与 exe 在同一目录。

## 从源码编译

1. 安装 **Visual Studio 2022**（勾选"使用 C++ 的桌面开发"工作负载，其中包含 MFC 库）
2. 双击打开 `MFCcaocaohrd.sln`
3. 选择 `Release | x64`（或 `Release | x86`）配置
4. 按 **F7** 或 **Ctrl+Shift+B** 生成，输出位于 `bin/` 目录

## 使用方法

- 鼠标拖动棋子滑动，把**曹操**（2×2 大块）移到底部中间的出口即获胜
- 通过菜单可切换棋局、启动自动求解 / 演示、调整演示速度

## 项目结构

```
MFCcaocaohrd.sln          VS2022 解决方案
MFCcaocaohrd/             源代码目录
├── MFCcaocaohrd.cpp/h    应用程序类（初始化、读取棋局、播放音乐）
├── MFCcaocaohrdDlg.cpp/h 主对话框
├── QZ.cpp/h              棋子类 + BFS 求解器
├── TStage.cpp/h          棋局/关卡数据结构
├── WNDChess.cpp/h        棋子窗口
├── CDemoThread.cpp/h     自动演示线程
├── Direction.cpp/h       方向定义
├── res/ res2/ res3/      位图、图标、音乐等资源
└── bin/                  编译输出与运行时数据文件
.github/workflows/        CI：打 v* 标签自动编译并发布 Release
```

## License

仅供学习交流使用。
