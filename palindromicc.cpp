#include <bits/stdc++.h>
using namespace std;

static const long long MOD1 = 1000000007LL;
static const long long MOD2 = 1000000009LL;
static const long long P = 31LL;

uint64_t getHash(int l, int r,
                 const vector<long long>& h1,
                 const vector<long long>& h2,
                 const vector<long long>& p1,
                 const vector<long long>& p2)
{
    int len = r - l + 1;
    long long x1 = (h1[r+1] - (h1[l] * p1[len]) % MOD1 + MOD1) % MOD1;
    long long x2 = (h2[r+1] - (h2[l] * p2[len]) % MOD2 + MOD2) % MOD2;
    return ((uint64_t)x1 << 32) ^ (uint64_t)x2;
}


bool isPalindrome(int l, int r, int n,
                  const vector<long long>& h1,
                  const vector<long long>& h2,
                  const vector<long long>& hr1,
                  const vector<long long>& hr2,
                  const vector<long long>& p1,
                  const vector<long long>& p2)
{
    uint64_t hf = getHash(l, r, h1, h2, p1, p2);
    int rl = n - 1 - r, rr = n - 1 - l;
    uint64_t hr = getHash(rl, rr, hr1, hr2, p1, p2);
    return hf == hr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();

    vector<long long> p1(n+1), p2(n+1);
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p1[i] = (p1[i-1] * P) % MOD1;
        p2[i] = (p2[i-1] * P) % MOD2;
    }

    vector<long long> h1(n+1, 0), h2(n+1, 0);
    for (int i = 0; i < n; ++i) {
        int v = s[i] - 'a' + 1;
        h1[i+1] = (h1[i] * P + v) % MOD1;
        h2[i+1] = (h2[i] * P + v) % MOD2;
    }

    string rs = s;
    reverse(rs.begin(), rs.end());
    vector<long long> hr1(n+1, 0), hr2(n+1, 0);
    for (int i = 0; i < n; ++i) {
        int v = rs[i] - 'a' + 1;
        hr1[i+1] = (hr1[i] * P + v) % MOD1;
        hr2[i+1] = (hr2[i] * P + v) % MOD2;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<long long> ansDiff(n + 2, 0);

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;

            if (!isPalindrome(l, r, n, h1, h2, hr1, hr2, p1, p2)) 
                continue;

            if (len == 1) {
                dp[l][r] = 1;
            } else {
                int lenHalf = len / 2;
                int leftL = l;
                int leftR = l + lenHalf - 1;
                int rightL = r - lenHalf + 1;
                int rightR = r;

                if (getHash(leftL, leftR, h1, h2, p1, p2) ==
                    getHash(rightL, rightR, h1, h2, p1, p2))
                {
                    dp[l][r] = dp[leftL][leftR] + 1;
                } else {
                    dp[l][r] = 1;
                }
            }

            int v = dp[l][r];
            ansDiff[1] += 1;
            ansDiff[v + 1] -= 1;
        }
    }

    vector<long long> ans(n+1, 0);
    long long cur = 0;
    for (int k = 1; k <= n; ++k) {
        cur += ansDiff[k];
        ans[k] = cur;
    }

    for (int k = 1; k <= n; ++k) {
        if (k > 1) cout << ' ';
        cout << ans[k];
    }
    cout << '\n';
    return 0;
}