#include "gamemanager.h"

GameManager::GameManager(QObject* parent) : QObject(parent) {}

void GameManager::startAsServer() {
    // создаём логику
    m_game   = new Tictactoe(this);
    m_server = new GameServer(m_game, this);
    m_server->start(12345);

    // сервер сам подключается к себе через клиент
    m_client = new GameClient(this);
    bindClient(m_client);
    m_client->connectToServer("ws://localhost:12345");
}

void GameManager::connectToServer(const QString& host) {
    m_client = new GameClient(this);
    bindClient(m_client);
    m_client->connectToServer(QString("ws://%1:12345").arg(host));
}

void GameManager::bindClient(GameClient* client) {
    // пробрасываем сигналы клиента наружу в QML
    connect(client, &GameClient::boardChanged,
            this,   &GameManager::boardChanged);
    connect(client, &GameClient::currentPlayerChanged,
            this,   &GameManager::currentPlayerChanged);
    connect(client, &GameClient::gameOverChanged,
            this,   &GameManager::gameOverChanged);
    connect(client, &GameClient::winnerChanged,
            this,   &GameManager::winnerChanged);
    connect(client, &GameClient::connected, this, [this]() {
        m_connected = true;
        emit connectedChanged();
    });
}

// геттеры — берём данные из клиента
QVector<int> GameManager::board()         const { return m_client ? m_client->board()         : QVector<int>(9, 0); }
int          GameManager::currentPlayer() const { return m_client ? m_client->currentPlayer() : 1; }
bool         GameManager::gameOver()      const { return m_client ? m_client->gameOver()       : false; }
int          GameManager::winner()        const { return m_client ? m_client->winner()         : -1; }

void GameManager::makeMove(int index)  { if (m_client) m_client->makeMove(index); }
void GameManager::resetGame()          { if (m_client) m_client->resetGame(); }