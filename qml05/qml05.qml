// Date:2024/3/5
// Author:妖怪鱼
// Introduction:别名属性，tab键操作,js函数
import QtQuick
import QtQuick.Controls

Rectangle{
    height: 300
    width: 300
    id:root
    Text {
        id:thisLabel
        property int times: 24
        //property alias 关键字用于创建一个别名属性，可以让一个属性指向另一个属性，使它们共享相同的值
        property alias anotherTimes: thisLabel.times
        text: "thisLabel "+  anotherTimes
        width:200
        height:30
        font.pixelSize: 24
        KeyNavigation.tab: thatLabel     //指定当按下tab键的时候焦点移动到哪个元素上
        onHeightChanged: {
            console.log("height: ",height)
        }
        focus: true
        color:focus ?"red" :"black"
        Rectangle{
            anchors.fill: parent
            color: "#cccccc"
            z:parent.z-1
        }
    }
    Text {
        y:60
        id: thatLabel
        text: qsTr("thatLabel " + thisLabel.times)
        KeyNavigation.tab: thisLabel
        font.pixelSize: 36
        color:focus ?"red" :"black"

        //js函数
        function increment(){
            thisLabel.times +=1;
            console.log("increment ",thisLabel.times)
        }
        //这里是一个回调函数
//        onTextChanged: function(text){
//            console.log("text changed to ",text)
//        }
        onTextChanged: (text)=>{
            console.log("text changed to ",text)
        }

        Keys.onSpacePressed:{increment()}
        Keys.onEscapePressed: {
            text  = 'esc'
        }
    }

}


