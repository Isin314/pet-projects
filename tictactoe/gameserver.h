#ifndef GAMESERVER_H
#define GAMESERVER_H
#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include "tictactoe.h"

class GameServer : public QObject {
    Q_OBJECT
public:
    explicit GameServer(Tictactoe* game, QObject* parent = nullptr);
    void start(quint16 port = 12345);

private slots:
    void onNewConnection();
    void onMessageReceived(const QString& message);
    void onClientDisconnected();

private:
    void broadcastState();          // отправить состояние всем клиентам

    QWebSocketServer* m_server;
    Tictactoe*        m_game;
    QList<QWebSocket*> m_clients;  // список подключённых клиентов
};

#endif // GAMESERVER_H
