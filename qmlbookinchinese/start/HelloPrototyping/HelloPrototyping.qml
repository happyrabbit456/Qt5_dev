import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "lightgreen"

    Item {
        anchors.fill: parent;
        focus: true;
        Keys.onEscapePressed: {
            Qt.quit();  // 没有功能: 不退出, why?
        }
        Keys.onReturnPressed: {  // 对应Enter键
            console.log("ColorPicker:onReturnPressed");
            event.accepted = true;
        }

        Keys.onSpacePressed: {  // 对应Space键
            console.log("ColorPicker:onSpacePressed");
            event.accepted = true;
        }

        onFocusChanged: {
            console.log("ColorPicker:onFocusChanged");
        }

        Keys.onPressed: {
            switch(event.key) {
            case Qt.Key_Left:
                console.log("Key_Left");
                break;
            case Qt.Key_Right:
                console.log("Key_Right");
                break;
            case Qt.Key_Up:
                console.log("Key_Up");
                break;
            case Qt.Key_Down:
                console.log("Key_Down");
                break;
            default:
                return;
            }
            event.accepted = true
        }
    }

    MouseArea {
        id: mouseTestArea1
        anchors.fill: parent
        propagateComposedEvents: true

        onPressAndHold: {
            console.log("*********** ListView onPressAndHold!");
            mouse.accepted = false;
        }


        onCanceled: {console.log("onCanceled");}//鼠标时间取消或者被窃取时触发。
        onClicked: {console.log("onClicked");}  // 点击时触发
        onDoubleClicked: {console.log("onDoubleClicked");} //双击触发
        onEntered: {console.log("onEntered");} //进入鼠标区域触发，悬浮属性为false，需点击才触发
        onExited: {console.log("onExited");}   //退出鼠标区域(hoverEnabled得为true)，或者点击退出的时触发
        //        onPressAndHold: {console.log("onPressAndHold");} //长按触发，默认时间800ms
        onPressed: {console.log("onPressed");}          //按下就能触发
        onReleased: {console.log("onReleased");}        //释放时触发
        onPositionChanged: {console.log("onPositionChanged");} //鼠标位置变化（hoverEnabled得为true），不然得点击才变化

    }
}
