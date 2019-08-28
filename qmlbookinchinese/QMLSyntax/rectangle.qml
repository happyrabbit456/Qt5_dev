// rectangle.qml

import QtQuick 2.12
import QtQuick.Window 2.12

// The root element is the Rectangle
Rectangle {
    // name this element root
    id: root
    // properties: <name>: <value>
    width: 240; height: 480
    // color property
    color: "#D8D8D8"
    // Declare a nested element (child of root)
    Image {
        id: rocket
        // reference the parent
        x: (parent.width - width)/2; y: 40
        source: 'assets/rocket.jpg'
    }
    // Another child of root
    Text {
        // name this element txtRocket
        id:txtRocket

        // reference element by id
        y: rocket.y + rocket.height + 20
        // reference root element
        width: root.width
        horizontalAlignment: Text.AlignHCenter
        text: 'Rocket'
    }

    Text {
        id: label
        x: 24; y: rocket.y + rocket.height + 20+txtRocket.height+24
        // custom counter property for space presses
        property int spacePresses: 0
        text: "Space pressed: " + spacePresses + " times"
        // (1) handler for text changes
        onTextChanged: console.log("text changed to:", text)
        // need focus to receive key events
        focus: true
        // (2) handler with some JS
        Keys.onSpacePressed: {
            increment()
        }
        // clear the text on escape
        Keys.onEscapePressed: {
            label.text = ''
        }
        // (3) a JS function
        function increment() {
            spacePresses = spacePresses + 1
        }
    }
}
