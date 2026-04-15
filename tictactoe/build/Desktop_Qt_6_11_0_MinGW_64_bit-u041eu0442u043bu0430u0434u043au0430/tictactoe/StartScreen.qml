import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    property StackView stack

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 16

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: "Крестики-нолики"
            font.pixelSize: 32
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            text: "Создать игру"
            onClicked: {
                game.startAsServer()
                root.stack.push("WaitingScreen.qml")
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            text: "Подключиться"
            onClicked: root.stack.push("ConnectScreen.qml")
        }
    }
}
