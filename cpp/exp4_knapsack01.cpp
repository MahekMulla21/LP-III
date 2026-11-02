// Exp 4: 0-1 Knapsack using Branch and Bound (and Dynamic Programming for verification)
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

struct Item { int weight, profit; };
struct Node { int level, profit, weight; float bound; };

bool cmp(Item a, Item b) { return (double)a.profit / a.weight > (double)b.profit / b.weight; }

float bound(Node u, int n, int W, Item arr[]) {
    if (u.weight >= W) return 0;
    float result = u.profit;
    int j = u.level + 1, totWeight = u.weight;
    while (j < n && totWeight + arr[j].weight <= W) {
        totWeight += arr[j].weight;
        result += arr[j].profit;
        j++;
    }
    if (j < n) result += (W - totWeight) * (float)arr[j].profit / arr[j].weight;
    return result;
}

int knapsackBB(int W, Item arr[], int n) {
    sort(arr, arr + n, cmp);
    queue<Node> Q;
    Node u, v;
    u.level = -1; u.profit = u.weight = 0;
    Q.push(u);
    int maxProfit = 0;
    while (!Q.empty()) {
        u = Q.front(); Q.pop();
        if (u.level == n - 1) continue;
        v.level = u.level + 1;
        // include next item
        v.weight = u.weight + arr[v.level].weight;
        v.profit = u.profit + arr[v.level].profit;
        if (v.weight <= W && v.profit > maxProfit) maxProfit = v.profit;
        v.bound = bound(v, n, W, arr);
        if (v.bound > maxProfit) Q.push(v);
        // exclude next item
        v.weight = u.weight; v.profit = u.profit;
        v.bound = bound(v, n, W, arr);
        if (v.bound > maxProfit) Q.push(v);
    }
    return maxProfit;
}

int knapsackDP(int W, Item arr[], int n) {
    vector<vector<int>> K(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= W; w++)
            if (arr[i - 1].weight <= w)
                K[i][w] = max(arr[i - 1].profit + K[i - 1][w - arr[i - 1].weight], K[i - 1][w]);
            else K[i][w] = K[i - 1][w];
    return K[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    Item arr[50];
    for (int i = 0; i < n; i++) {
        cout << "Enter weight and profit of item " << i + 1 << ": ";
        cin >> arr[i].weight >> arr[i].profit;
    }
    cout << "Enter capacity of knapsack: ";
    cin >> W;
    cout << "\nMaximum profit (Branch and Bound) = " << knapsackBB(W, arr, n) << endl;
    cout << "Maximum profit (Dynamic Programming) = " << knapsackDP(W, arr, n) << endl;
    return 0;
}
