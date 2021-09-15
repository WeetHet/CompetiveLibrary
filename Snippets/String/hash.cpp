int add(int a, int b, int MOD) {
    return (a % MOD + b % MOD) % MOD;
}
 
int sub(int a, int b, int MOD) {
    return (a % MOD - b % MOD + MOD) % MOD;
}
 
int mul(int a, int b, int MOD) {
    return static_cast<int>(1ll * a * b % MOD);
}

struct Hash {
    string s;
    vi p;
    vi hash;
    int P, MOD;
 
    void build() {
        int n = sz(s);
        p.resize(n);
        hash.resize(n);
        
        p[0] = 1;
        hash[0] = s[0];
        for (int i = 1; i < sz(s); ++i) {
            p[i] = mul(p[i - 1], P, MOD);
            hash[i] = add(mul(hash[i - 1], P, MOD), s[i], MOD);
        }
    }
     
    // [l, r)
    int getSub(int l, int r) {
        int h = hash[r - 1];
     
        if (l != 0)
            h = sub(h, mul(hash[l - 1], p[r - l], MOD), MOD);
        return h;
    }
};
