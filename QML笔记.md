#  QML和Qt Quick学习
## 介绍
Qt Quick和Qt Widgets一样是一种用户界面技术,Qt Widget使用C++进行开发，而Qt Quick使用一种叫做QML的声明式语言开发<br/>
Qt Quick的两种含义:广义上来说，是一门用户界面技术的名称，狭义上来说，是QML的类型和功能库<br/>
**MinGW**即Minimalist GUN For Windows,是将GUN开发工具移植到Win32平台下的产物<br/>
**CMake**创建Qt项目:CMakeModules 通常是一组为Qt项目定制的CMake脚本和模块。这些模块提供了用于配置Qt项目所需的设置和变量，以及可能需要的FindModules，帮助CMake找到Qt及其依赖项。<br/>

---------
## 目录<br/>
**qml01:**第一个qml案例<br/>

**qml02：**纯qml样例<br/>

**qml03：**Item与Rectangle<br/>

**qml04：**水平，垂直居中<br/>

**qml05：**别名，属性，Tab键操作，js属性<br/>



---------

## 一些学习心得和体会
**2024/3/4**&emsp;&emsp;今天在学即时通讯小程序的时候发现跟不上课程进度，主要是各种界面的制作太过繁琐，我打算先不跟着视频去写那个项目。打算先学qml,之后使用qml做界面。<br/>

---------
## 问题与学习
**问题01:ApplicationWindow和Window元素**
回答:<br/>
ApplicationWindow提供了一个完整的窗口，包括菜单栏、工具栏、状态栏等。<br/>
Window提供了一个空白窗口，没有标题栏或其他装饰。它通常用于创建无边框窗口或弹出窗口，如对话框、提示框等。<br/>
<br/>
**问题02:QML控件父子问题**
回答:<br/>
在 QML 中创建一个控件时，如果没有显式地指定父控件，那么这个控件的父控件就是包含它的容器控件。<br/>
