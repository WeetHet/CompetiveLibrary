const int logN = 20;

int n, l;
vector<pair<int, int>> g[N];
int level[N], parent[N], d[N];
int f[N][logN], depth[N];

set<pair<int, int>> ncentre[N];

void precalc(int u) {
    for (int i = 1; i < logN; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    
    for (int i = 0; i < sz(g[u]); i++) {
        int v = g[u][i].first, w = g[u][i].second;
        
        if (!d[v]) {
            f[v][0] = u;
            depth[v] = depth[u] + w;
            d[v] = d[u] + 1;
            precalc(v);
        }
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    
    for (int i = logN - 1; i >= 0; i--)
        if (d[f[u][i]] >= d[v]) {
            u = f[u][i];
        }
    
    if (u == v) return u;
    
    for (int i = logN - 1; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    
    return f[u][0];
}

int dist(int u, int v) {
    int x = lca(u, v);
    int res = depth[u] + depth[v] - 2 * depth[x];
    return res;
}

int dfs(int v, int size, int &center, int p = -1) {
    int sum = 1;
    for (auto pt : g[v]) {
        int x = pt.first;
        if (level[x] == -1 && x != p)
            sum += dfs(x, size, center, v);
    }
    
    if (center == -1 && (2 * sum >= size || p == -1))
        center = v;
    
    return sum;
}

void build(int v, int size, int depth, int last) {
    int center = -1;
    dfs(v, size, center);
    parent[center] = last;
    level[center] = depth;
    for (auto [x, w] : g[center])
        if (level[x] == -1)
            build(x, size / 2, depth + 1, center);
}

void add(int v) {
    for (int v0 = v; v != -1; v = parent[v]) {
        ncentre[v].emplace(dist(v0, v), v0);
    }
}

void del(int v) {
    for (int v0 = v; v != -1; v = parent[v]) {
        ncentre[v].erase({dist(v0, v), v0});
    }
}

int get(int v) {
    int ans = INF;
    for (int v0 = v; v != -1; v = parent[v]) {
        if (!ncentre[v].empty())
            ckmin(ans, dist(v0, ncentre[v].begin()->second));
    }
    
    return ans;
}