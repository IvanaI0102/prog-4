#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string value;

    BigInt(string s = "0") {
        if (s.empty()) {
            value = "0";
        } else {
            size_t first_nonzero = 0;
            while (first_nonzero < s.size() - 1 && s[first_nonzero] == '0') {
                first_nonzero++;
            }
            value = s.substr(first_nonzero);
        }
    }

    bool isLess(const BigInt& other) const {
        if (value.length() != other.value.length()) {
            return value.length() < other.value.length();
        }
        return value < other.value;
    }

    BigInt operator+(BigInt other) {
        string res = "";
        int i = value.length() - 1, j = other.value.length() - 1, ostatok = 0;
        while (i >= 0 || j >= 0 || ostatok) {
            int v1 = 0;
            if (i >= 0) v1 = value[i--] - '0';
            int v2 = 0;
            if (j >= 0) v2 = other.value[j--] - '0';
            int sum = ostatok + v1 + v2;
            res += (char)((sum % 10) + '0'); 
            ostatok = sum / 10;
        }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator*(BigInt other) {
        int n = value.length(), m = other.value.length();
        vector<int> res(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (value[i] - '0') * (other.value[j] - '0');
                int sum = mul + res[i + j + 1];
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }
        string s = "";
        for (int x : res) if (!(s.empty() && x == 0)) s += (char)(x + '0');
        if (s.empty()) return BigInt("0");
        return BigInt(s);
    }
    

    bool operator==(const BigInt& other) const {
        return value == other.value;
    }
};


struct CompareBigIntPair {
    bool operator()(const pair<BigInt, BigInt>& a, const pair<BigInt, BigInt>& b) {
      
        return b.first.isLess(a.first);
    }
};

void generatePrimesDijkstra(BigInt limit) {
    if (limit.isLess(BigInt("2"))) return;

   
    priority_queue<pair<BigInt, BigInt>, vector<pair<BigInt, BigInt>>, CompareBigIntPair> pq;

    cout << "2 ";
    pq.push({BigInt("4"), BigInt("2")});

    BigInt n("3");
    while (n.isLess(limit) || n == limit) {
        
        
        if (n.isLess(pq.top().first)) {
            cout << n.value << " ";
            pq.push({n * n, n});
        } else {
           
            while (n == pq.top().first) {
                pair<BigInt, BigInt> current = pq.top();
                pq.pop();
                current.first = current.first + current.second;
                pq.push(current);
            }
        }
        n = n + BigInt("1");
    }
    cout << endl;
}

int main() {
    string limitInput;
   
    cin >> limitInput;//vnesi BigInt limit

    BigInt limit(limitInput);
    cout << limit.value << " " << endl;
    generatePrimesDijkstra(limit);

    return 0;
}