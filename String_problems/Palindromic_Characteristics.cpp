#include <bits/stdc++.h>
using namespace std;

struct RH {
    long long B = 31, M = 1000000009;
    int N;
    vector<long long> P, F, R;

    RH(string x) {
        N = x.size();
        P.resize(N + 1);
        F.resize(N + 1);
        R.resize(N + 1);
        P[0] = 1;
        for (int i = 1; i <= N; i++) P[i] = (P[i - 1] * B) % M;

        for (int i = 0; i < N; i++)
            F[i + 1] = (F[i] + (x[i] - 'a' + 1) * P[i]) % M;

        reverse(x.begin(), x.end());
        for (int i = 0; i < N; i++)
            R[i + 1] = (R[i] + (x[i] - 'a' + 1) * P[i]) % M;
    }

    long long h(int L, int Rv) {
        long long v = (F[Rv + 1] - F[L] + M) % M;
        return (v * P[N - Rv - 1]) % M;
    }

    long long rh(int L, int Rv) {
        long long v = (R[Rv + 1] - R[L] + M) % M;
        return (v * P[N - Rv - 1]) % M;
    }

    bool ok(int L, int Rv) {
        int a = N - 1 - Rv, b = N - 1 - L;
        return h(L, Rv) == rh(a, b);
    }
};

int main() {
    string w;
    cin >> w;
    int n = w.size();

    RH H(w);
    vector<vector<int>> C(n, vector<int>(n + 1));
    vector<long long> res(n + 2);

    for (int L = 1; L <= n; L++) {
        for (int i = 0; i + L <= n; i++) {
            int j = i + L - 1;
            if (!H.ok(i, j)) continue;

            C[i][L] = 1;
            int h = L / 2;
            if (h > 0 && H.ok(i, i + h - 1))
                C[i][L] = C[i][h] + 1;

            res[C[i][L]]++;
        }
    }

    for (int k = n; k >= 1; k--) res[k] += res[k + 1];
    for (int k = 1; k <= n; k++) cout << res[k] << " ";
    cout << "\n";
}
