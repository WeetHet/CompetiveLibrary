struct SuffixArray {
    string s;
    int n;
    vector<int> sa, isa, lcp;

    void init(string _s) {
        n = sz(s = _s) + 1;
        genSa();
    }

    void genSa() {
        sa = isa = vector<int>(n);
        sa[0] = n - 1;
        iota(1 + begin(sa), end(sa), 0);
        sort(1 + begin(sa), end(sa), [&](int a, int b) {
            return s[a] < s[b];
        });

        for (int i = 1; i < n; ++i) {
            int a = sa[i - 1], b = sa[i];
            isa[b] = i > 1 && s[a] == s[b] ? isa[a] : i;
        }

        for (int len = 1; len < n; len *= 2) {
            vector<int> sn(sa), is(isa), pos(n);
            iota(begin(pos), end(pos), 0);
            for (auto &t: sn) {
                int tp = t - len;
                if (tp >= 0) sa[pos[isa[tp]]++] = tp;
            }

            for (int i = 1; i < n; ++i) {
                int a = sa[i - 1], b = sa[i];
                isa[b] = is[a] == is[b] && is[a + len] == is[b + len] ? isa[a] : i;
            }
        }
    }
};