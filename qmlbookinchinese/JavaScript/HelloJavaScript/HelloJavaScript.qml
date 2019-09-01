import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick 2.0
import "script.js" as MyScript

Item {
    width: 100; height: 100

    MouseArea {
        anchors.fill: parent
        onClicked: {
            MyScript.showCalculations(10)
            console.log("Call factorial() from QML:",
                MyScript.factorial(10))
        }
    }
}
