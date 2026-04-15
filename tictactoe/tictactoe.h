#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QObject>
#include <QVector>

class Tictactoe : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVector<int> board         READ board          NOTIFY boardChanged)
    Q_PROPERTY(int          currentPlayer READ currentPlayer  NOTIFY currentPlayerChanged)
    Q_PROPERTY(bool         gameOver      READ gameOver       NOTIFY gameOverChanged)
    Q_PROPERTY(int          winner        READ winner         NOTIFY winnerChanged)

public:
    Tictactoe(QObject* parent = nullptr);

    QVector<int> board() const {return m_board;}
    int currentPlayer() const {return m_currentPlayer;}
    bool gameOver() const {return m_gameOver;}
    int winner() const {return m_winner;}

    Q_INVOKABLE void makeMove(int index);
    Q_INVOKABLE void resetGame();
signals:
    void boardChanged();
    void currentPlayerChanged();
    void gameOverChanged();
    void winnerChanged();

private:
    QVector<int> m_board;
    int m_currentPlayer;
    bool m_gameOver;
    int m_winner;

    int checkWinner();
    bool isBoardFull();
};

#endif // TICTACTOE_H
