#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
using namespace std;

struct Trie {
    bool end = false;
    map<string, Trie*> next;
};

string nextRune(const string& s, int& i) {
    unsigned char c = s[i];
    int bytes = 1;
    if ((c & 0xE0) == 0xC0) bytes = 2;
    else if ((c & 0xF0) == 0xE0) bytes = 3;
    else if ((c & 0xF8) == 0xF0) bytes = 4;

    string r = s.substr(i, bytes);
    i += bytes;
    return r;
}

void insertTrie(Trie* root, const string& word) {
    Trie* cur = root;
    for (int i=0; i<word.size();) {
        string r = nextRune(word, i);
        if (!cur->next.count(r))
            cur->next[r] = new Trie();
        cur = cur->next[r];
    }
    cur->end = true;
}

void printTrie(Trie* t, string prefix = "") {
    if (t->end) cout << prefix << "\n";
    for (auto& kv : t->next)
        printTrie(kv.second, prefix + kv.first);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Trie* root = new Trie();

    ifstream file(R"(C:\Users\Lenovo\Desktop\prog4\recnik_mk.txt)");
    if (!file.is_open()) {
        cerr << "error\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        insertTrie(root, line);
    }
    file.close();

    printTrie(root);
    return 0;
}