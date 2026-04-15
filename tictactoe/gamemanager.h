#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QObject>
#include "tictactoe.h"
#include "gameserver.h"
#include "gameclient.h"

class GameManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<int> board         READ board          NOTIFY boardChanged)
    Q_PROPERTY(int          currentPlayer READ currentPlayer  NOTIFY currentPlayerChanged)
    Q_PROPERTY(bool         gameOver      READ gameOver       NOTIFY gameOverChanged)
    Q_PROPERTY(int          winner        READ winner         NOTIFY winnerChanged)
    Q_PROPERTY(bool         connected     READ connected      NOTIFY connectedChanged)

public:
    explicit GameManager(QObject* parent = nullptr);

    QVector<int> board()         const;
    int          currentPlayer() const;
    bool         gameOver()      const;
    int          winner()        const;
    bool         connected()     const { return m_connected; }

    Q_INVOKABLE void startAsServer();
    Q_INVOKABLE void connectToServer(const QString& host = "localhost");
    Q_INVOKABLE void makeMove(int index);
    Q_INVOKABLE void resetGame();

signals:
    void boardChanged();
    void currentPlayerChanged();
    void gameOverChanged();
    void winnerChanged();
    void connectedChanged();

private:
    void bindClient(GameClient* client);  // подписываемся на сигналы клиента

    Tictactoe*  m_game   = nullptr;
    GameServer* m_server = nullptr;
    GameClient* m_client = nullptr;
    bool        m_connected = false;
};

#endif // GAMEMANAGER_H
