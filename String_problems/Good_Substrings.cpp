#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll hash_sub(int L, int R, const vector<ll>& pref, const vector<ll>& pw, ll MOD, int N) {
    ll v = (pref[R + 1] - pref[L] + MOD) % MOD;
    return (v * pw[N - L]) % MOD;
}

int main() {
    string a, b;
    int limit;
    cin >> a >> b >> limit;

    int n = a.size();
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++)
        cnt[i + 1] = cnt[i] + (b[a[i] - 'a'] == '0');

    const ll MOD = 1000000009, P = 31;
    vector<ll> pw(n + 1, 1), pref(n + 1, 0);
    for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * P % MOD;
    for (int i = 0; i < n; i++) pref[i + 1] = (pref[i] + (a[i] - 'a' + 1) * pw[i]) % MOD;

    unordered_set<ll> bag;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (cnt[j + 1] - cnt[i] > limit) break;
            bag.insert(hash_sub(i, j, pref, pw, MOD, n));
        }
    }

    cout << bag.size();
}
