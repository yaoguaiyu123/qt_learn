// Date:2024/3/4
// Author:妖怪鱼
// Introduction:Item与Rectangle
import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle{
        rotation: 30
        id:rectangle1
        x:100;
        y:190;
        width: 150;
        height: 150;
        color: "#a5dda2";
        border.width: 20
        border.color: "#f1e710"
        //渐变颜色
        //Gradient是一个用于定义颜色渐变的容器,它可以包含一个或多个GradientStop对象。
        //GradientStop用于定义渐变中的一个特定颜色和位置,其position属性0.0表示表示渐变开始的位置
        //1.0表示渐变结束的位置
        gradient: Gradient{

            GradientStop {
                position: 0.0;color: "#ff5555";
            }
            GradientStop {
                position: 1.0;color: "#3333ff";
            }
        }
    }

    Rectangle{
        //直接设置坐标
//        x:rectangle1.x + rectangle1.width + 20
        //使用锚点
        anchors.left: rectangle1.right
        anchors.leftMargin: 200
        y:120;
        width: 150;
        height: 150;
        color: "#cd8987";
        focus: true
        //MouseArea是一个特殊的矩形控件，可以相应鼠标事件
        MouseArea{
            anchors.fill:parent    //使MouseArea填满整个父控件
            onClicked: {
                console.log("点击")
            }
        }
        Keys.onReturnPressed: {   //回车键按下,需要设置focus:true
            console.log("回车键")
        }
    }



}
