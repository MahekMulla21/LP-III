// Exp 2: Huffman Encoding using Greedy strategy
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

struct Node {
    char ch; int freq; Node *left, *right;
    Node(char c, int f, Node* l = NULL, Node* r = NULL) : ch(c), freq(f), left(l), right(r) {}
};
struct Compare {
    bool operator()(Node* a, Node* b) { return a->freq > b->freq; }   // min-heap
};

void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) { codes[root->ch] = code.empty() ? "0" : code; return; }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

int main() {
    int n;
    cout << "Enter number of symbols: ";
    cin >> n;
    vector<char> sym(n); vector<int> freq(n);
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < n; i++) {
        cout << "Enter symbol and its frequency: ";
        cin >> sym[i] >> freq[i];
        pq.push(new Node(sym[i], freq[i]));
    }
    while (pq.size() > 1) {                    // greedy: merge two least frequent
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        pq.push(new Node('$', l->freq + r->freq, l, r));
    }
    Node* root = pq.top();
    map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "\nSymbol\tFrequency\tHuffman Code\n";
    int wpl = 0;
    for (int i = 0; i < n; i++) {
        cout << sym[i] << "\t" << freq[i] << "\t\t" << codes[sym[i]] << endl;
        wpl += freq[i] * codes[sym[i]].length();
    }
    cout << "\nWeighted external path length = " << wpl << endl;

    string msg;
    cout << "\nEnter a message to encode: ";
    cin >> msg;
    string enc = "";
    for (char c : msg) enc += codes[c];
    cout << "Encoded message: " << enc << endl;
    string dec = ""; Node* cur = root;
    for (char b : enc) {
        cur = (b == '0') ? cur->left : cur->right;
        if (!cur->left && !cur->right) { dec += cur->ch; cur = root; }
    }
    cout << "Decoded message: " << dec << endl;
    return 0;
}
