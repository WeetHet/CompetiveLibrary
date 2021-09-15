T diameter(vector<pt> pts) {
        pts = hull(pts);
        int n = sz(pts), ind = 1;
        T ans = 0;
        if (n > 1)
            for (int i = 0; i < n; ++i)
                for (int j = (i + 1) % n;; ind = (ind + 1) % n) {
                    ckmax(ans, dist2(pts[i], pts[ind]));
                    if (cross(pts[j] - pts[i], pts[(ind + 1) % n] - pts[ind]) <= 0)
                        break;
                }
        
        return ans;
    }