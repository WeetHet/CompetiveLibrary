struct node {
    int sum = 0;
    int l = -1, r = -1;

    node() = default;

    node(int sum, int l, int r) : sum(sum), l(l), r(r) {}

    bool operator==(const node &rhs) const {
        return sum == rhs.sum &&
               l == rhs.l &&
               r == rhs.r;
    }

    bool operator!=(const node &rhs) const {
        return !(rhs == *this);
    }
};

constexpr int N = 450005;

int roots[N];
vector<node> vert(2e7);

node nil{-1, -1, -1};

int pos = 0;

void extend(int i, int lb, int rb) {
    if (vert[i].l == -1 && lb + 1 < rb) {
        vert[pos] = node();
        vert[i].l = pos++;

        vert[pos] = node();
        vert[i].r = pos++;
    }
}

void copy(int i) {
    if (vert[i].l != -1) {
        vert[pos] = vert[vert[i].l];
        vert[i].l = pos++;

        vert[pos] = vert[vert[i].r];
        vert[i].r = pos++;
    }
}

void add(int t, int k, int x, int lb = 0, int rb = N) {
    while (true) {
        extend(t, lb, rb);
        copy(t);
        vert[t].sum += x;
        if (vert[t].l != -1) {
            int mid = lb + (rb - lb) / 2;
            if (k < (lb + rb) / 2) {
                t = vert[t].l;
                rb = mid;
            }
            else {
                t = vert[t].r;
                lb = mid;
            }
        } else {
            break;
        }
    }
}

int get_sum(int t, int lq, int rq, int lb = 0, int rb = N) {
    if (lq <= lb && rb <= rq)
        return vert[t].sum;
    if (max(lb, lq) >= min(rb, rq))
        return 0;
    int mid = lb + (rb - lb) / 2;
    extend(t, lb, rb);
    return get_sum(vert[t].l, lq, rq, lb, mid) + get_sum(vert[t].r, lq, rq, mid, rb);
}

int get(int t) {
    if (t != -1 && vert[t] != nil) return vert[t].sum;
    else return 0;
}

int get_left(int t) {
    if (t == -1) return -1;
    else return vert[t].l;
}

int get_right(int t) {
    if (t == -1) return -1;
    else return vert[t].r;
}

int go(int a, int b, int k, int lb = 0, int rb = N) {
    int key, mid;

    while (rb - lb > 1) {
        key = get(get_left(b)) - get(get_left(a));
        mid = lb + (rb - lb) / 2;
        if (key >= k) {
            a = get_left(a);
            b = get_left(b);
            rb = mid;
        } else {
            a = get_right(a);
            b = get_right(b);
            k -= key;
            lb = mid;
        }
    }
    return lb;
}