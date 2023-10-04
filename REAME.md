# Coordinate 转换类

## 使用方法

1. sudo apt-get install libgeographic-dev
2. 拷贝本项目到您的工程目录下，并在 CMakeLists.txt 使用 add_subdirectory() 添加本项目
3. 链接环节，请链接 common::coordinate
4. 头文件中，使用 #include "coordinate.h" 即可

## 维护者与版本

维护者：ztyu
联系方式：peiwvy@163.com

版本历史：

v1.0.2
yaml加载格式变化
v1.0.1
增加zone northbp读取
v1.0.0
这个类用于处理坐标的转换，包括从 WGS84 坐标到 UTM 坐标的转换，以及它们的反向转换。类也支持坐标偏移的处理