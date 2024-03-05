// Date:2024/3/5
// Author:妖怪鱼
// Introduction:水平,垂直居中
import QtQuick
import QtQuick.Controls
//import语句导入一个模块，qt6可以不写版本号，自动导入最高的版本

Rectangle {
    id:root
    width: 640
    height: 480
    visible: true
    color: "#dadada"

    Image {
        id: image
        source: "./06.png"
        width: 200
        height: 200
        //设置Image元素垂直居中
        y:root.height / 2- image.height /2
        //设置Text元素水平居中
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        height: root.height / 3
        text: qsTr("Hello World")
        //设置Text元素水平居中
        anchors.horizontalCenter: parent.horizontalCenter
        //设置Text元素中的文字垂直居中,需要先设置Text的高度
        verticalAlignment: Text.AlignVCenter
        color:"#f85544"

    }
}
