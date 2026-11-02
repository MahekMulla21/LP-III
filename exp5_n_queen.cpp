// Exp 5: N-Queens matrix having first Queen placed
// Use backtracking to place remaining Queens

#include <iostream>
using namespace std;

int N, board[20][20];

bool isSafe(int board[20][20], int row, int col, int n) {

    // Check the same column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Backtracking function
bool solveNQueens(int board[20][20], int row, int n) {
    if (row == n) {
        return true;
    }

    // Skip the row containing the first queen
    bool rowHasQueen = false;
    for (int j = 0; j < n; j++) {
        if (board[row][j] == 1) {
            rowHasQueen = true;
            break;
        }
    }

    if (rowHasQueen) {
        return solveNQueens(board, row + 1, n);
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;

            if (solveNQueens(board, row + 1, n)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    cout << "Enter value of N: ";
    cin >> N;

    int row, col;

    cout << "Enter row of first Queen (1-" << N << "): ";
    cin >> row;

    cout << "Enter column of first Queen (1-" << N << "): ";
    cin >> col;

    // Place the first queen
    board[row - 1][col - 1] = 1;

    // Solve the N-Queens problem
    if (solveNQueens(board, 0, N)) {
        cout << "\nFinal N-Queens Matrix:\n";

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 1) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "\nNo solution exists with the first queen at that position."
             << endl;
    }

    return 0;
}