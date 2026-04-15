import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Connections {
            target: game
            function onGameOverChanged() {
                if (game.gameOver) {
                    // переходим на экран конца
                    root.stack.push("GameOverScreen.qml")
                }
            }
        }

    ColumnLayout {
            anchors.centerIn: parent
            spacing: 16

            // Статус игры
            Text {
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 22
                text: {
                    if (!game.gameOver)
                        return "Ход: " + (game.currentPlayer === 1 ? "❌" : "⭕") + game.currentPlayer
                }
            }

            // Игровое поле 3x3
            Grid {
                columns: 3
                spacing: 4
                Layout.alignment: Qt.AlignHCenter

                Repeater {
                    model: game.board   // напрямую из C++

                    Rectangle {
                        width: 100; height: 100
                        color: "#f0f0f0"
                        border.color: "#888"
                        border.width: 2
                        radius: 8

                        Text {
                            anchors.centerIn: parent
                            font.pixelSize: 52
                            text: modelData === 1 ? "❌" : (modelData === 2 ? "⭕" : "")
                        }

                        MouseArea {
                            anchors.fill: parent
                            enabled: !game.gameOver
                            onClicked: game.makeMove(index)  // вызов C++ метода
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
            }
    }

}
