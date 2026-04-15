#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QWebSocket>

class GameClient : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVector<int> board         READ board          NOTIFY boardChanged)
    Q_PROPERTY(int          currentPlayer READ currentPlayer  NOTIFY currentPlayerChanged)
    Q_PROPERTY(bool         gameOver      READ gameOver       NOTIFY gameOverChanged)
    Q_PROPERTY(int          winner        READ winner         NOTIFY winnerChanged)

public:
    explicit GameClient(QObject* parent = nullptr);
    void connectToServer(const QString& url = "ws://localhost:12345");

    QVector<int> board()         const { return m_board; }
    int          currentPlayer() const { return m_currentPlayer; }
    bool         gameOver()      const { return m_gameOver; }
    int          winner()        const { return m_winner; }

    Q_INVOKABLE void makeMove(int index);
    Q_INVOKABLE void resetGame();

signals:
    void boardChanged();
    void currentPlayerChanged();
    void gameOverChanged();
    void winnerChanged();
    void connected();

private slots:
    void onMessageReceived(const QString& message);

private:
    QWebSocket   m_socket;
    QVector<int> m_board;
    int          m_currentPlayer = 1;
    bool         m_gameOver      = false;
    int          m_winner        = -1;
};
#endif // GAMECLIENT_H
