struct line {
    ll k = 0, b = INF;
    line(ll k, ll b) : k(k), b(b) {}
    line() = default;
    
    ll operator()(const ll& x) const {
        return k * x + b;
    }
};

constexpr int MAXC = 1e6 + 5;
vector<line> t(4 * MAXC + 1);

ll get(int v, int lo, int hi, ll p) {
    if (lo == hi) {
        return t[v](p);
    }
    
    int mid = (lo + hi) / 2;
    if (p <= mid) {
        return min(t[v](p), get(2 * v + 1, lo, mid, p));
    } else {
        return min(get(2 * v + 2, mid + 1, hi, p), t[v](p));
    }
}

void upd(int v, int lo, int hi, line ln) {
    if (lo == hi) {
        if (ln(lo) < t[v](lo))
            t[v] = ln;
        return;
    }
    
    int mid = (lo + hi) / 2;
    if (ln(mid) < t[v](mid))
        swap(ln, t[v]);
    
    if (ln.k > t[v].k)
        upd(2 * v + 1, lo, mid, ln);
    else
        upd(2 * v + 2, mid + 1, hi, ln);
}