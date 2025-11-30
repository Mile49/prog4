#include <bits/stdc++.h>
using namespace std;

vector<int> rk(string &s, string &t) {
    const int base = 13;
    const int mod = 1e9+9;
    int n = s.size(), m = t.size();

    vector<long long> pw(max(n, m));
    pw[0] = 1;
    for (int i = 1; i < (int)pw.size(); i++)
        pw[i] = (pw[i - 1] * base) % mod;

    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++)
        pref[i + 1] = (pref[i] + (s[i] - 'a' + 1) * pw[i]) % mod;

    long long th = 0;
    for (int i = 0; i < m; i++)
        th = (th + (t[i] - 'a' + 1) * pw[i]) % mod;

    vector<int> ans;
    for (int i = 0; i + m <= n; i++) {
        long long hval = (pref[i + m] - pref[i] + mod) % mod;
        if (hval == (th * pw[i]) % mod)
            ans.push_back(i);
    }
    return ans;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        string s, t;
        cin >> s >> t;

        vector<int> out = rk(s, t);
        if (out.empty()) {
            cout << "Not Found\n\n";
        } else {
            cout << out.size() << '\n';
            for (int v : out) cout << v + 1 << " ";
            cout << "\n\n";
        }
    }
    return 0;
}
