#include "Tictactoe.h"

Tictactoe::Tictactoe(QObject* parent) : QObject(parent) {
    resetGame();
}

void Tictactoe::resetGame(){
    m_board = QVector<int>(9, 0);
    m_currentPlayer = 1;
    m_gameOver = false;
    m_winner = -1;

    emit boardChanged();
    emit currentPlayerChanged();
    emit gameOverChanged();
    emit winnerChanged();
}

void Tictactoe::makeMove(int index){
    // Игнорируем невалидные ходы
    if (m_gameOver) return;
    if (index < 0 || index >= 9) return;
    if (m_board[index] != 0) return;

    m_board[index] = m_currentPlayer;
    emit boardChanged();

    int w = checkWinner();
    if (w != -1) {
        m_winner   = w;
        m_gameOver = true;
        emit winnerChanged();
        emit gameOverChanged();
        return;
    }

    if (isBoardFull()) {
        m_winner   = 0;   // ничья
        m_gameOver = true;
        emit winnerChanged();
        emit gameOverChanged();
        return;
    }

    m_currentPlayer = (m_currentPlayer == 1) ? 2 : 1;
    emit currentPlayerChanged();
}

int Tictactoe::checkWinner(){
    // Все выигрышные комбинации
    const int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},  // строки
        {0,3,6}, {1,4,7}, {2,5,8},  // столбцы
        {0,4,8}, {2,4,6}            // диагонали
    };

    for (auto& line : lines) {
        int a = m_board[line[0]];
        if (a != 0 && a == m_board[line[1]] && a == m_board[line[2]])
            return a;
    }
    return -1;   // победителя нет
}

bool Tictactoe::isBoardFull(){
    return !m_board.contains(0);
}