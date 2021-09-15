#define BREAK_CONDITION max(lq, l) >= min(rq, r) || x >= t[v].max1
#define TAG_CONDITION (lq <= l && r <= rq) && (t[v].max2 < x && x < t[v].max1)

struct node {
    int max1, max2 = 0, sum, cntmax, d = 2e9;
    
    node() = default;
    
    node(int x) {
        max1 = x;
        sum = x;
        cntmax = 1;
    }
} t[4 * N];
int a[N];

void calc(int v) {
    t[v].max1 = max(t[2 * v + 1].max1, t[2 * v + 2].max1);
    
    t[v].max2 = max(t[2 * v + 1].max2, t[2 * v + 2].max2);
    if (min(t[2 * v + 1].max1, t[2 * v + 2].max1) != t[v].max1) {
        t[v].max2 = max(t[v].max2, min(t[2 * v + 1].max1, t[2 * v + 2].max1));
    }
    
    t[v].cntmax = (t[2 * v + 1].max1 > t[2 * v + 2].max1 ? t[2 * v + 1].cntmax :
                   (t[2 * v + 1].max1 == t[2 * v + 2].max1? t[2 * v + 1].cntmax + t[2 * v + 2].cntmax : t[2 * v + 2].cntmax));
    t[v].sum = t[2 * v + 1].sum + t[2 * v + 2].sum;
}

void pushdown(int v, int l, int r) {
    if (t[v].d == 0) return;
    
    if (r - l > 1) {
        t[2 * v + 1].d = min(t[2 * v + 1].d, t[v].d);
        t[2 * v + 2].d = min(t[2 * v + 2].d, t[v].d);
    }
    
    if (t[v].d > t[v].max1) {
        t[v].d = 2e9;
        return;
    }
    
    t[v].sum -= (t[v].max1 - t[v].d) * t[v].cntmax;
    t[v].max1 = t[v].d;
    
    t[v].d = 2e9;
    return;
}

void apply(int v, int x, int l, int r) {
    t[v].d = x;
    pushdown(v, l, r);
}

void build(int v, int l, int r) {
    if (r - l == 1) {
        t[v] = node(a[l]);
        return;
    }
    int m = l + ((r - l) >> 1);
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    calc(v);
}

void modify(int v, int l, int r, int lq, int rq, int x) {
    pushdown(v, l, r);
    if (BREAK_CONDITION) return;
    
    if (TAG_CONDITION) {
        apply(v, x, l, r);
        return;
    }
    
    int m = l + ((r - l) >> 1);
    modify(2 * v + 1, l, m, lq, rq, x);
    modify(2 * v + 2, m, r, lq, rq, x);
    calc(v);
}

int query(int v, int l, int r, int lq, int rq) {
    pushdown(v, l, r);
    if (max(l, lq) >= min(r, rq)) return 0;
    
    if (lq <= l && r <= rq) return t[v].sum;
    
    int m = l + ((r - l) >> 1);
    return query(2 * v + 1, l, m, lq, rq) + query(2 * v + 2, m, r, lq, rq);
}
