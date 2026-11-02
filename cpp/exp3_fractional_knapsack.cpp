// Exp 3: Fractional Knapsack using Greedy method
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item { char name; double profit, weight, ratio; };

bool cmp(Item a, Item b) { return a.ratio > b.ratio; }

int main() {
    int n; double W;
    cout << "Enter number of items: ";
    cin >> n;
    Item it[50];
    for (int i = 0; i < n; i++) {
        it[i].name = 'A' + i;
        cout << "Enter profit and weight of item " << it[i].name << ": ";
        cin >> it[i].profit >> it[i].weight;
        it[i].ratio = it[i].profit / it[i].weight;
    }
    cout << "Enter capacity of knapsack: ";
    cin >> W;

    sort(it, it + n, cmp);                    // sort by profit/weight ratio (descending)

    double curWeight = W, finalValue = 0;
    cout << "\nItem\tProfit\tWeight\tRatio\tFraction taken\n";
    for (int i = 0; i < n; i++) {
        if (curWeight <= 0) break;
        double frac;
        if (it[i].weight <= curWeight) {      // take whole item
            frac = 1;
            curWeight -= it[i].weight;
            finalValue += it[i].profit;
        } else {                              // take fraction and stop
            frac = curWeight / it[i].weight;
            finalValue += it[i].profit * frac;
            curWeight = 0;
        }
        cout << it[i].name << "\t" << it[i].profit << "\t" << it[i].weight << "\t"
             << fixed << setprecision(2) << it[i].ratio << "\t" << frac << endl;
    }
    cout << "\nMaximum profit = " << finalValue << endl;
    return 0;
}
