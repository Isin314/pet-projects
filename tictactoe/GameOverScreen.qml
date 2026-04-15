import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Item {
    ColumnLayout{
        anchors.centerIn: parent
        spacing: 16

        // Статус игры
        Text {
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 22
            text: {
                if (game.winner === 0)
                    return "Ничья!"
                return "Победил: " + (game.winner === 1 ? "❌" : "⭕")
            }
        }
        // Кнопка новой игры
        Button {
            Layout.alignment: Qt.AlignHCenter
            text: "Новая игра"
            onClicked: {
                game.resetGame()
                // убираем GameOver и Game, возвращаемся на старт
                root.stack.pop(null)  // null = до самого низа
                root.stack.push("GameScreen.qml")
            }
        }
        Button {
                    Layout.alignment: Qt.AlignHCenter
                    text: "В меню"
                    onClicked: {
                        // возвращаемся на StartScreen
                        root.stack.pop(null)
                    }
                }
    }

}
