int glg(int s) {
    return s > 1? 32 - __builtin_clz(s - 1): 0;
}

template<class T>
void ks(T* a, T* b, T* c, T* t, int n) {
    ll ca = 0, cb = 0;
    for (ll i = 0; i < n;  ++i)
        ca += a[i] != 0, cb += b[i] != 0;
    
    if (min(ca, cb) <= 1500 / n) {
        if (ca > cb) swap(a, b);
        for (ll i = 0; i < n; ++i)
            if (a[i] != 0)
                for (ll j = 0; j < n; ++j)
                    c[i + j] += a[i] * b[j];
    } else {
        int h = n >> 1;
        
        ks(a, b, c, t, h);
        ks(a + h, b + h, c + n, t, h);
        
        for (ll i = 0; i < h; ++i)
            a[i] += a[i + h], b[i] += b[i + h];
        
        ks(a, b, t, t + n, h);
        for (ll i = 0; i < h; ++i)
            a[i] -= a[i + h], b[i] -= b[i + h];
        for (ll i = 0; i < n; ++i)
            t[i] -= c[i] + c[i + n];
        for (ll i = 0; i < n; ++i)
            c[i + h] += t[i], t[i] = 0;
    }
}

template<class T>
vector<T> conv(vector<T> a, vector<T> b) {
    int sa = sz(a), sb = sz(b);
    if (!sa || !sb) return {};
    
    int n = 1 << glg(max(sa, sb));
    a.resize(n), b.resize(n);
    vector<T> c(2 * n), t(2 * n);
    ks(&a[0], &b[0], &c[0], &t[0], n);
    
    c.resize(sa + sb - 1);
    return c;
}

constexpr ll BASE = 1e6, BASE_LEN = 6;

template<class T>
void normal(vector<T>& num) {
    if (!sz(num)) return;
    
    for (ll i = 0; i < sz(num) - 1; ++i) {
        num[i + 1] += num[i] / BASE;
        num[i] %= BASE;
    }
    
    while (num.back() > BASE) {
        num.push_back(num.back() / BASE);
        num[sz(num) - 2] %= BASE;
    }
}

vector<ll> str_ll(string s) {
    vector<ll> res;
    ll num = 0;
    
    for (int i = 0; i < sz(s) % BASE_LEN; ++i) {
        num = num * 10 + (s[i] - '0');
    }
    res.push_back(num);
    
    for (int i = sz(s) % BASE_LEN; i < sz(s); i += BASE_LEN) {
        num = 0;
        
        for (int j = 0; j < BASE_LEN; ++j) {
            num = num * 10 + (s[i + j] - '0');
        }
        
        res.push_back(num);
    }
    return res;
}