import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id:root
    property alias stack: stackView
    width: 400
    height: 500
    visible: true
    title: qsTr("крестики нолики")

    StackView{
        id:stackView
        anchors.fill: parent

        initialItem: "StartScreen.qml"
    }
}
