import QtQuick 2.12
import QtQuick.Window 2.12

import "factorial.js" as MathFunctions

//在使用JS工作时，有一些对象和方法会被频繁的使用。下面是它们的一个小的集合。

//Math.floor(v),Math.ceil(v),Math.round(v) - 从浮点数获取最大，最小和随机整数
//Math.random() - 创建一个在0到1之间的随机数
//Object.keys(o) - 获取对象的索引值（包括QObject）
//JSON.parse(s), JSON.stringify(o) - 转换在JS对象和JSON字符串
//Number.toFixed(p) - 修正浮点数精度
//Date - 日期时间操作

Window {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property var obj1: {
        key: 'value'
    }

    function factorial(a) {
        a = parseInt(a);
        if (a <= 0)
            return 1;
        else
            return a * factorial(a - 1);
    }

    function doIt() {
        console.log("doIt()")
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

            MathFunctions.doIt()
        }
    }

    Timer {
        id: timeUpdater
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            var d = new Date();
            console.log(d.getSeconds());
        }
    }
    Component.onCompleted: {
        //Running JavaScript at Startup
        console.log(factorial(3))

        // Call using function execution
        root["doIt"]();
        var fn = root["doIt"];
        // Call using JS call method (could pass in a custom this object and arguments)
        fn.call()


        var data = JSON.stringify(obj1);
        console.log(data);
        var obj = JSON.parse(data);
        console.log(obj.key); // > 'value'


        var keys = Object.keys(root);
        for(var i=0; i<keys.length; i++) {
            var key = keys[i];
            // prints all properties, signals, functions from object
            console.log(key + ' : ' + root[key]);
        }
    }
}
