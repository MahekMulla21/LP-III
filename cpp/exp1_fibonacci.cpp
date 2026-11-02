// Exp 1: Recursive and non-recursive Fibonacci with time/space analysis
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

long long recCalls = 0;

void fibonacciIterative(int n) {          // Time O(n), Space O(1)
    long long F = 0, L = 1, V;
    cout << "Iterative: ";
    if (n >= 1) cout << F << " ";
    if (n >= 2) cout << L << " ";
    for (int i = 3; i <= n; i++) {
        V = F + L;
        cout << V << " ";
        F = L; L = V;
    }
    cout << endl;
}

long long fiboRec(int n) {                // Time O(2^n), Space O(n) (stack)
    recCalls++;
    if (n == 0 || n == 1) return n;
    return fiboRec(n - 1) + fiboRec(n - 2);
}

int main() {
    int n;
    cout << "Enter the number of terms (n): ";
    cin >> n;

    auto t1 = high_resolution_clock::now();
    fibonacciIterative(n);
    auto t2 = high_resolution_clock::now();

    cout << "Recursive:  ";
    recCalls = 0;
    auto t3 = high_resolution_clock::now();
    for (int i = 0; i < n; i++) cout << fiboRec(i) << " ";
    auto t4 = high_resolution_clock::now();
    cout << endl << endl;

    cout << "Iterative time : " << duration_cast<nanoseconds>(t2 - t1).count() << " ns" << endl;
    cout << "Recursive time : " << duration_cast<nanoseconds>(t4 - t3).count() << " ns" << endl;
    cout << "Recursive function calls: " << recCalls << endl << endl;
    cout << "Time  complexity: Iterative = O(n),  Recursive = O(2^n)" << endl;
    cout << "Space complexity: Iterative = O(1),  Recursive = O(n) (call stack)" << endl;
    return 0;
}
