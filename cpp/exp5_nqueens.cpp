// Exp 5: N-Queens with first queen placed by user, remaining placed by Backtracking
#include <iostream>
using namespace std;

int N, board[20][20];

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) if (board[i][col]) return false;                 // column
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) if (board[i][j]) return false;   // left diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) if (board[i][j]) return false;    // right diagonal
    return true;
}

bool solve(int row) {
    if (row == N) return true;
    // row 0 already holds the first queen (placed by user)
    if (row == 0) return solve(1);
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            if (solve(row + 1)) return true;
            board[row][col] = 0;               // backtrack
        }
    }
    return false;
}

int main() {
    cout << "Enter N: ";
    cin >> N;
    int c;
    cout << "Enter column (1 to " << N << ") for the first queen in row 1: ";
    cin >> c;
    board[0][c - 1] = 1;
    if (solve(0)) {
        cout << "\nFinal N-Queens matrix:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << board[i][j] << " ";
            cout << endl;
        }
    } else cout << "\nNo solution exists with first queen at that position." << endl;
    return 0;
}
