#include "gameclient.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

GameClient::GameClient(QObject* parent) : QObject(parent) {
    m_board = QVector<int>(9, 0);

    connect(&m_socket, &QWebSocket::textMessageReceived,
            this,      &GameClient::onMessageReceived);

    connect(&m_socket, &QWebSocket::connected,
            this,      &GameClient::connected);
}

void GameClient::connectToServer(const QString& url) {
    m_socket.open(QUrl(url));
}

void GameClient::makeMove(int index) {
    // отправляем ход на сервер
    QJsonObject msg {
        {"action", "move"},
        {"index",  index}
    };
    m_socket.sendTextMessage(QJsonDocument(msg).toJson(QJsonDocument::Compact));
}

void GameClient::resetGame() {
    QJsonObject msg { {"action", "reset"} };
    m_socket.sendTextMessage(QJsonDocument(msg).toJson(QJsonDocument::Compact));
}

void GameClient::onMessageReceived(const QString& message) {
    // получаем состояние от сервера и обновляем свойства
    QJsonObject json = QJsonDocument::fromJson(message.toUtf8()).object();

    QJsonArray boardArray = json["board"].toArray();
    m_board.clear();
    for (const QJsonValue& val : boardArray)
        m_board.append(val.toInt());

    m_currentPlayer = json["currentPlayer"].toInt();
    m_gameOver      = json["gameOver"].toBool();
    m_winner        = json["winner"].toInt();

    // уведомляем QML
    emit boardChanged();
    emit currentPlayerChanged();
    emit gameOverChanged();
    emit winnerChanged();
}