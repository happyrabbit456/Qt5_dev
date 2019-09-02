import QtQuick 2.12
import QtQuick.Window 2.12

import "factorial.js" as MathFunctions

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function factorial(a) {
        a = parseInt(a);
        if (a <= 0)
            return 1;
        else
            return a * factorial(a - 1);
    }

    function mouseAreaClicked(area) {
        console.log("Clicked in area at: " + area.x + ", " + area.y);
    }

    MouseArea {
        anchors.fill: parent
        onClicked:
        {
            console.log(factorial(5))
            console.log(MathFunctions.factorial(10))

            onPressed: label.text = "I am Pressed!"
            onReleased: label.text = "Click Me!"
        }
    }

    Text {
        id: label
        anchors.centerIn: parent
        text: "Press Me!"
    }


    Rectangle {
        id: item
        width: 200; height: 200
        color: "yellow"

        MouseArea {
            id: mouseArea
            anchors.fill: parent

        }

        Component.onCompleted: {
            mouseArea.clicked.connect(MathFunctions.jsFunction)
            //使用Qt.binding()完成属性绑定
            color = Qt.binding(function() { return mouseArea.pressed ? "red" : "green" })
        }
    }

    Component.onCompleted: {
        //Running JavaScript at Startup
        console.log(factorial(3))
    }
}
