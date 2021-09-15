vector<int> chull(vector<pt> &v) {
    int ind = (int) (min_element(all(v), cmp) - begin(v));
    //        int ind = 0;
    vector<int> cand, chull{ind};
    
    for (int i = 0; i < sz(v); ++i)
        if (v[i] != v[ind])
            cand.push_back(i);
    
    sort(all(cand), [&](int a, int b) {
        pt x = v[a] - v[ind], y = v[b] - v[ind];
        T t = cross(x, y);
        return t != 0 ? t > 0 : norm(x) < norm(y);
    });
    
    for (auto c: cand) {
        while (sz(chull) > 1 && make(v[chull[sz(chull) - 2]], v[chull.back()], v[c]) <= 0)
            chull.pop_back();
        
        chull.push_back(c);
    }
    return chull;
}

vector<pt> hull(vector<pt> v) {
    vector<int> w = chull(v);
    vector<pt> res;
    for (auto &t: w)
        res.push_back(v[t]);
    return res;
}
