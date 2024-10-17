import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Window {
//     width: 640
//     height: 480
//     visible: true
//     title: qsTr("Hello World")
// }

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Calculator 1.0"

    property string currentDisplay: "0"
    property string operation: ""
    property real leftOperand: 0

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            id: display
            text: currentDisplay
            font.pixelSize: 40
            horizontalAlignment: Text.AlignRight
            Layout.fillWidth: true
        }

        GridLayout {
            columns: 4
            Layout.fillWidth: true

            Button { text: "7"; onClicked: appendNumber("7"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "8"; onClicked: appendNumber("8"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "9"; onClicked: appendNumber("9"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "+"; onClicked: setOperation("+"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }

            Button { text: "4"; onClicked: appendNumber("4"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "5"; onClicked: appendNumber("5"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "6"; onClicked: appendNumber("6"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "-"; onClicked: setOperation("-"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }

            Button { text: "1"; onClicked: appendNumber("1"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "2"; onClicked: appendNumber("2"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "3"; onClicked: appendNumber("3"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "*"; onClicked: setOperation("*"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }

            Button { text: "0"; Layout.columnSpan: 2; onClicked: appendNumber("0"); Layout.margins: 5; Layout.preferredWidth: 160; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "C"; onClicked: clearDisplay(); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }
            Button { text: "/"; onClicked: setOperation("/"); Layout.margins: 5; Layout.preferredWidth: 80; Layout.preferredHeight: 80; font.pixelSize: 24 }

            Button {
                text: "="
                Layout.columnSpan: 4
                Layout.margins: 5
                Layout.preferredWidth: 320
                Layout.preferredHeight: 80
                font.pixelSize: 24
                onClicked: {
                    var rightOperand = parseFloat(currentDisplay)
                    var logInput = leftOperand + " " + operation + " " + rightOperand
                    var result = calculateResult()

                    logger.logToFile(logInput, result)

                    currentDisplay = result
                }
            }
        }
    }

    function appendNumber(number) {
        if (currentDisplay.length < 16) { // max 16 numbers
            if (currentDisplay === "0") {
                currentDisplay = number;
            } else {
                currentDisplay += number;
            }
        }
    }

    function setOperation(op) {
        leftOperand = parseFloat(currentDisplay);
        currentDisplay = "0";
        operation = op;
    }

    function calculateResult() {
        var rightOperand = parseFloat(currentDisplay);
        var result = 0;

        if (operation === "+") {
            result = leftOperand + rightOperand;
        } else if (operation === "-") {
            result = leftOperand - rightOperand;
        } else if (operation === "*") {
            result = leftOperand * rightOperand;
        } else if (operation === "/") {
            if (rightOperand !== 0) {
                result = leftOperand / rightOperand;
            } else {
                result = "Error";
            }
        }

        return result.toString();
    }

    function clearDisplay() {
        currentDisplay = "0";
        operation = "";
        leftOperand = 0;
    }
}
