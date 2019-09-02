import QtQuick 2.12
import QtQuick.Window 2.12

// MyWorkerScript.qml

Rectangle {
    width: 300; height: 300

    Text {
        id: myText
        text: 'Click anywhere'
    }

    WorkerScript {
        id: myWorker
        source: "worker_script.js"
        onMessage: myText.text = messageObject.reply
    }

    MouseArea {
        anchors.fill: parent
        onClicked: myWorker.sendMessage({ 'x': mouse.x, 'y': mouse.y })
    }
}

