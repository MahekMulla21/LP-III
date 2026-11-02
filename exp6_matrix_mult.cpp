// Exp 6: Matrix multiplication - sequential vs multithreaded using POSIX threads (pthread)
// Compile: g++ exp6_pthread.cpp -o exp6 -lpthread
#include <iostream>
#include <vector>
#include <pthread.h>
#include <sys/time.h>
#include <cstdlib>
using namespace std;

int N;
vector<vector<int> > A, B, C1, C2, C3;

struct Arg { int i, j; };

double now_us() {
    struct timeval tv; gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000.0 + tv.tv_usec;
}
void sequential() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C1[i][j] = 0;
            for (int k = 0; k < N; k++) C1[i][j] += A[i][k] * B[k][j];
        }
}
void* rowWorker(void* p) {                   // one thread per row
    int i = ((Arg*)p)->i;
    for (int j = 0; j < N; j++) {
        C2[i][j] = 0;
        for (int k = 0; k < N; k++) C2[i][j] += A[i][k] * B[k][j];
    }
    return NULL;
}
void* cellWorker(void* p) {                  // one thread per cell
    int i = ((Arg*)p)->i, j = ((Arg*)p)->j;
    C3[i][j] = 0;
    for (int k = 0; k < N; k++) C3[i][j] += A[i][k] * B[k][j];
    return NULL;
}
void show(const char* t, vector<vector<int> >& M) {
    if (N > 6) return;
    cout << t << endl;
    for (int i = 0; i < N; i++) { for (int j = 0; j < N; j++) cout << M[i][j] << "\t"; cout << endl; }
    cout << endl;
}

int main() {
    cout << "Enter matrix size N (NxN): ";
    cin >> N;
    vector<vector<int> > Z(N, vector<int>(N, 0));
    A = B = C1 = C2 = C3 = Z;
    srand(1);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) { A[i][j] = rand() % 10; B[i][j] = rand() % 10; }
    show("Matrix A:", A);
    show("Matrix B:", B);

    double s = now_us(); sequential(); double t1 = now_us() - s;

    s = now_us();
    {
        vector<pthread_t> th(N); vector<Arg> a(N);
        for (int i = 0; i < N; i++) { a[i].i = i; a[i].j = 0; pthread_create(&th[i], NULL, rowWorker, &a[i]); }
        for (int i = 0; i < N; i++) pthread_join(th[i], NULL);
    }
    double t2 = now_us() - s;

    s = now_us();
    {
        vector<pthread_t> th(N * N); vector<Arg> a(N * N);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                int id = i * N + j; a[id].i = i; a[id].j = j;
                pthread_create(&th[id], NULL, cellWorker, &a[id]);
            }
        for (int id = 0; id < N * N; id++) pthread_join(th[id], NULL);
    }
    double t3 = now_us() - s;

    show("Result (sequential):", C1);
    show("Result (thread per row):", C2);
    show("Result (thread per cell):", C3);
    cout << "Results match: " << ((C1 == C2 && C1 == C3) ? "YES" : "NO") << endl << endl;
    cout << "Sequential time      : " << (long long)t1 << " microseconds" << endl;
    cout << "Thread-per-row time  : " << (long long)t2 << " microseconds" << endl;
    cout << "Thread-per-cell time : " << (long long)t3 << " microseconds" << endl;
    return 0;
}