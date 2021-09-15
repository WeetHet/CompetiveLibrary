constexpr int LOGN = 18; // limit for array size
int n; // array size
int t[2 * N];

void build() { // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = max(t[i << 1], t[i << 1 | 1]);
}

void modify(int p, int value) { // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
}

int query(int l, int r) { // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, t[l++]);
        if (r & 1) res = max(res, t[--r]);
    }
    return res;
}

vector<int> g[N];
int sz[N], up[LOGN][N];

int in[N], out[N], nxt[N], rin[N], par[N];
int timer = 0;

void dfsSz(int v = 0, int p = -1) { // Count sizes and push bigger sizes upper
    sz[v] = 1;
    for (auto &u: g[v]) {
        if (u != p) {
            dfsSz(u, v);
            sz[v] += sz[u];
            
            if (sz[u] > sz[g[v][0]])
                swap(u, g[v][0]);
        }
    }
}

bool isParent(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

int lca(int v, int u) {
    if (isParent(u, v)) return u;
    if (isParent(v, u)) return v;
    
    for (int k = LOGN - 1; k >= 0; --k) {
        if (!isParent(up[k][v], u))
            v = up[k][v];
    }
    return up[0][v];
}

void precalc() {
    for (int u = 0; u < n; ++u)
        up[0][u] = par[u];
    
    up[0][0] = 0;
    for (int i = 1; i < LOGN; i++)
        for (int u = 0; u < n; ++u)
            up[i][u] = up[i - 1][up[i - 1][u]];
}

void dfsHld(int v = 0, int p = -1) {
    in[v] = timer++;
    rin[in[v]] = v;
    
    for (auto u: g[v]) {
        if (u != p) {
            par[u] = v;
            
            nxt[u] = (u == g[v][0] ? nxt[v] : u);
            dfsHld(u, v);
        }
    }
    
    out[v] = timer;
}

int get(int v, int upv) {
    int ans = 0;
    
    while (nxt[v] != nxt[upv]) {
        ans = max(ans, query(in[nxt[v]], in[v] + 1));
        v = par[nxt[v]];
    }
    
    ans = max(ans, query(in[upv], in[v] + 1));
    return ans;
}