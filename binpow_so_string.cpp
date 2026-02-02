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

    bool isLess(BigInt other) {
        if (value.length() != other.value.length()) {
            return value.length() < other.value.length();
        }
        return value < other.value;
    }

    BigInt operator+(BigInt other) {
        string res = "";
        int i = value.length() - 1;
        int j = other.value.length() - 1;
        int ostatok = 0;
        
        while (i >= 0 || j >= 0 || ostatok) {
            int v1 = 0;
            if (i >= 0) {
                v1 = value[i--] - '0';
            }
            
            int v2 = 0;
            if (j >= 0) {
                v2 = other.value[j--] - '0';
            }
            
            int sum = ostatok + v1 + v2;
            res += (char)((sum % 10) + '0'); 
            ostatok = sum / 10;
        }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator-(BigInt other) {
        string res = "";
        int i = value.length() - 1;
        int j = other.value.length() - 1;
        int zimaj = 0;
        
        while (i >= 0) {
            int v1 = value[i--] - '0'; 
            int v2 = 0;
            if (j >= 0) {
                v2 = other.value[j--] - '0';
            }
            
            int sub = v1 - v2 - zimaj;
            if (sub < 0) {
                sub += 10;
                zimaj = 1; 
            } else {
                zimaj = 0; 
            }
            res += (char)(sub + '0');
        }
        while (res.length() > 1 && res.back() == '0') {
            res.pop_back();
        }
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    BigInt operator*(BigInt other) {
        int n = value.length();
        int m = other.value.length();
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
        for (int x : res) {
            if (!(s.empty() && x == 0)) {
                s += (char)(x + '0');
            }
        }
        
        if (s.empty()) {
            return BigInt("0");
        } else {
            return BigInt(s);
        }
    }

    BigInt operator/(BigInt other) {
        if (other.value == "0") return BigInt("Error");
        string res = "";
        string currentStr = "";
        
        for (char c : value) {
            currentStr += c;
            BigInt current(currentStr);
            int count = 0;
            
            while (!(current.isLess(other))) {
                current = current - other;
                currentStr = current.value;
                count++;
            }
            res += (char)(count + '0');
            currentStr = current.value;
        }
        return BigInt(res);
    }

    BigInt operator%(BigInt other) {
        if (other.value == "0") return BigInt("Error");
        string currentStr = "";
        
        for (char c : value) {
            currentStr += c;
            BigInt current(currentStr);
            
            while (!(current.isLess(other))) {
                current = current - other;
                currentStr = current.value;
            }
            currentStr = current.value;
        }
        return BigInt(currentStr);
    }
};


BigInt binpow(BigInt b, BigInt e, BigInt m) {
    BigInt res("1");
    b = b % m; 
    
    while (e.value != "0") {
        int lastDigit = e.value.back() - '0';
        if (lastDigit % 2 != 0) {
            res = (res * b) % m;
        }
        
        b = (b * b) % m;
        e = e / BigInt("2");
    }
    return res;
}

int main() {
    BigInt base("3");
    BigInt exp("13");
    BigInt mod("100");

    BigInt result = binpow(base, exp, mod);

    cout << result.value << endl; 
    return 0;
}