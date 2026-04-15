#include "gameserver.h"
#include <QJsonObject>    // ← QJsonObject
#include <QJsonArray>     // ← QJsonArray
#include <QJsonDocument>

GameServer::GameServer(Tictactoe* game, QObject* parent)
    : QObject(parent), m_game(game)
{
    m_server = new QWebSocketServer("TicTacToe", QWebSocketServer::NonSecureMode, this);

    // когда меняется доска — рассылаем всем клиентам
    connect(m_game, &Tictactoe::boardChanged, this, &GameServer::broadcastState);
}

void GameServer::start(quint16 port) {
    m_server->listen(QHostAddress::LocalHost, port);
    connect(m_server, &QWebSocketServer::newConnection,
            this,     &GameServer::onNewConnection);
}

void GameServer::onNewConnection() {
    QWebSocket* client = m_server->nextPendingConnection();
    m_clients.append(client);

    connect(client, &QWebSocket::textMessageReceived,
            this,   &GameServer::onMessageReceived);
    connect(client, &QWebSocket::disconnected,
            this,   &GameServer::onClientDisconnected);

    // сразу отправляем новому клиенту текущее состояние
    broadcastState();
}

void GameServer::onMessageReceived(const QString& message) {
    // клиент присылает: {"action": "move", "index": 5}
    QJsonObject json = QJsonDocument::fromJson(message.toUtf8()).object();

    if (json["action"] == "move") {
        int index = json["index"].toInt();
        m_game->makeMove(index);  // логика в C++
    }

    if (json["action"] == "reset") {
        m_game->resetGame();
    }
}

void GameServer::onClientDisconnected() {
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    m_clients.removeAll(client);
    client->deleteLater();
}

void GameServer::broadcastState() {
    // собираем состояние игры в JSON
    QJsonArray boardArray;
    for (int cell : m_game->board())
        boardArray.append(cell);

    QJsonObject state {
        {"board",         boardArray},
        {"currentPlayer", m_game->currentPlayer()},
        {"gameOver",      m_game->gameOver()},
        {"winner",        m_game->winner()}
    };

    QString message = QJsonDocument(state).toJson(QJsonDocument::Compact);

    // отправляем всем подключённым клиентам
    for (QWebSocket* client : m_clients)
        client->sendTextMessage(message);
}
