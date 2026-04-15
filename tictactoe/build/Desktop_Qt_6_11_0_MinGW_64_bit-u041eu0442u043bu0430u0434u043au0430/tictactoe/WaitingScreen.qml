import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Connections {
            target: game
            function onConnectedChanged() {
                if (game.connected)
                    root.stack.replace("GameScreen.qml")
            }
        }

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 16

            BusyIndicator { Layout.alignment: Qt.AlignHCenter }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: "Ожидание подключения..."
                font.pixelSize: 18
            }

            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Отмена"
                onClicked: stack.pop()
            }
        }
}
