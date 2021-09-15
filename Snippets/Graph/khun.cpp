bool try_kuhn(int v){
    if (used[v]) return false;
    used[v] = true;
    for (auto u: g[v]) {
        if (back[u] == -1 || try_kuhn(back[u])) {
            back[u] = v;
            pairl[v] = u;
            return true;
        }
    }
    return false;
}

void kuhn(){
    memset(back, -1, sizeof(back));
    memset(pairl, -1, sizeof(pairl));
    for (int run = 1; run;) {
        run = 0, used.reset();
        for (int v = 0; v < n; ++v) {
            if (pairl[v] == -1 && try_kuhn(v)) {
                run = 1;
            }
        }
    }
}