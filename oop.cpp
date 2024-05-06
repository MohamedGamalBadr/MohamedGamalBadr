#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char player1;
    char player2;
    char currentPlayer;
    bool playWithAI;

public:
    TicTacToe() {
        board.resize(3, vector<char>(3, ' '));
        player1 = 'X';
        player2 = 'O';
        currentPlayer = player1;
        playWithAI = false;
    }

    void play() {
        cout << "Welcome to Tic Tac Toe!" << endl;
        cout << "1. Play with another player" << endl;
        cout << "2. Play with AI" << endl;
        cout << "Enter your choice (1 or 2): ";
        int choice;
        cin >> choice;
        playWithAI = (choice == 2);

        while (true) {
            displayBoard();
            if (playWithAI && currentPlayer == player2) {
                makeAIMove();
            } else {
                makeMove();
            }
            if (checkWin()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            }
            if (checkTie()) {
                displayBoard();
                cout << "It's a tie!" << endl;
                break;
            }
            switchPlayer();
        }
    }

private:
    void displayBoard() {
        cout << "-------------" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " | ";
            }
            cout << endl << "-------------" << endl;
        }
    }

    void makeMove() {
        int row, col;
        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (row[1-3] column[1-3]): ";
            cin >> row >> col;
            row--;
            col--;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                board[row][col] = currentPlayer;
                break;
            }
            cout << "Invalid move. Try again." << endl;
        }
    }

    void makeAIMove() {
        int bestScore = -numeric_limits<int>::max();
        int bestRow = -1;
        int bestCol = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player2;
                    int score = minimax(0, false, -numeric_limits<int>::max(), numeric_limits<int>::max());
                    board[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }
        board[bestRow][bestCol] = player2;
    }

    int minimax(int depth, bool isMaximizingPlayer, int alpha, int beta) {
        if (checkWin()) {
            return isMaximizingPlayer ? -10 + depth : 10 - depth;
        }
        if (checkTie()) {
            return 0;
        }

        if (isMaximizingPlayer) {
            int bestScore = -numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = player2;
                        int score = minimax(depth + 1, false, alpha, beta);
                        board[i][j] = ' ';
                        bestScore = max(bestScore, score);
                        alpha = max(alpha, bestScore);
                        if (beta <= alpha)
                            break;
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = player1;
                        int score = minimax(depth + 1, true, alpha, beta);
                        board[i][j] = ' ';
                        bestScore = min(bestScore, score);
                        beta = min(beta, bestScore);
                        if (beta <= alpha)
                            break;
                    }
                }
            }
            return bestScore;
        }
    }

    bool checkWin() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
                return true;
            }
        }
        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
                return true;
            }
        }
        // Check diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
            return true;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
            return true;
        }
        return false;
    }

    bool checkTie() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}