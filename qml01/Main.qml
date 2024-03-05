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
                onTriggered: console.log("点击了Open按钮");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    //Content Area
    TextArea {
        text: qsTr("Hello World")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Image{
        id:logo
        source:"../qml01/02.jpg"
        anchors.centerIn: parent
    }

    MyText{
        anchors.top:logo.bottom
        anchors.horizontalCenter: logo.horizontalCenter
    }
}
