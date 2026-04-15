import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    ColumnLayout {
            anchors.centerIn: parent
            spacing: 16

            Text {
                text: "Введите IP сервера"
                font.pixelSize: 22
                Layout.alignment: Qt.AlignHCenter
            }

            TextField {
                id: ipField
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "localhost"
                text: "localhost"
            }

            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Подключиться"
                onClicked: {
                    game.connectToServer(ipField.text)
                    root.stack.push("WaitingScreen.qml")
                }
            }
        }
}
