// Date:2024/3/4
// Author:妖怪鱼
// Introduction:纯qml样例
import QtQuick
import QtQuick.Controls

ApplicationWindow {
    x:450;
    y:300;
    width: 700
    height: 400
    visible: true
    maximumHeight: 800  //限制最小或者最大高度
    minimumHeight: 300  //限制最小或者最大高度
    title: qsTr("我的一个小案例")
//    opacity: 0.8    //透明度设置
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
        Menu {
            title: qsTr("Picture")
            MenuItem {
                text: qsTr("Store")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    signal mySig()
    onMySig: {
        console.log("触发信号")
    }
    property bool isBig: false;   //自定义属性
    onIsBigChanged: {
        console.log("这个控件的宽度发生了变化，跨过了900");
    }
    onWidthChanged: {
        console.log("当前宽度为:",width)
        if(width >=900){
            isBig = true;
        }else{
            isBig = false;
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "red"
        id: rectangle01
    }


    //Content Area
    TextArea {
        background: rectangle01
        text: qsTr("Hello World")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "white"        //  文字颜色的设置
    }

    Button{
        id : btn01
        text: "按钮1"
        width: 80
        height: 50
        background: Rectangle{
            color: btn01.focus ? "blue" : "green"
        }
        onClicked: {   //设置按钮的点击事件
            console.log("按钮1被点击")
        }
        Keys.onRightPressed:{    //这里设置键盘事件，但是键盘事件设置到按钮上的话，只有当前对焦在按钮上才会执行事件
            btn02.focus = true
        }
        onActiveFocusChanged: {
            if(btn01.activeFocus){
                console.log("当前按钮1获得了焦点")
            }else{
                console.log("当前按钮1失去了焦点~~")
            }
        }
    }

    Button{
        x: 90
        id : btn02
        text: "按钮2"
        width: 80
        height: 50
        background: Rectangle{
            color: btn02.focus ? "blue" : "green"
        }
        onClicked: {
            console.log("按钮2被点击")
        }
        Keys.onLeftPressed:{
            btn01.focus = true
        }
    }
}
