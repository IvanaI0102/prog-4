#include <bits/stdc++.h>
using namespace std;

static const long long MOD1 = 1000000007LL;
static const long long MOD2 = 1000000009LL;
static const long long P = 31LL;

uint64_t getHashPair(int l, int r, const vector<long long> &h1, const vector<long long> &h2, const vector<long long> &p1, const vector<long long> &p2)
{
    int len = r - l + 1;

    long long x1 = (h1[r+1] - (h1[l] * p1[len]) % MOD1 + MOD1) % MOD1;
    long long x2 = (h2[r+1] - (h2[l] * p2[len]) % MOD2 + MOD2) % MOD2;

    return ((uint64_t)x1 << 32) ^ (uint64_t)x2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    if (!(cin >> s)) return 0;
    string goodMask;
    cin >> goodMask;
    int k;
    cin >> k;

    int n = s.size();
    vector<bool> good(26);
    for (int i = 0; i < 26; ++i)
        good[i] = (goodMask[i] == '1');


    vector<long long> p1(n+1), p2(n+1);
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p1[i] = (p1[i-1] * P) % MOD1;
        p2[i] = (p2[i-1] * P) % MOD2;
    }

    vector<long long> h1(n+1,0), h2(n+1,0);
    for (int i = 0; i < n; ++i) {
        int val = s[i] - 'a' + 1;
        h1[i+1] = (h1[i] * P + val) % MOD1;
        h2[i+1] = (h2[i] * P + val) % MOD2;
    }

    unordered_set<uint64_t> seen;
    seen.reserve(1 << 20);

    for (int l = 0; l < n; ++l) {
        int bad = 0;
        for (int r = l; r < n; ++r) {
            if (!good[s[r] - 'a']) ++bad;
            if (bad > k) break;

            uint64_t hpair =
                getHashPair(l, r, h1, h2, p1, p2);

            seen.insert(hpair);
        }
    }

    cout << seen.size() << '\n';
    return 0;
}