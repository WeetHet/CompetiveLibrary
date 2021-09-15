struct node {
    node *go[26] = {nullptr}, *link = nullptr, *up = nullptr;
    
    vector<node*> rev;
    
    int cnt = 0, sum = 0;
    bool used = false;
    
    vector<int> term;
};

node *root = nullptr;

void bfs() {
    queue<node *> q;
    root->link = root;
    root->up = root;
    
    for (int i = 0; i < 26; ++i) {
        if (root->go[i]) {
            root->go[i]->link = root;
            root->rev.push_back(root->go[i]);
            root->go[i]->up = root;
            q.push(root->go[i]);
        } else {
            root->go[i] = root;
        }
    }
    
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
            if (v->go[i]) {
                auto u = v->go[i];
                
                auto nxt = v->link->go[i];
                
                u->link = nxt;
                nxt->rev.push_back(u);
                
                if (!nxt->term.empty())
                    u->up = nxt;
                else
                    u->up = nxt->up;
                
                q.push(u);
            } else {
                v->go[i] = v->link->go[i];
            }
        }
    }
}

void dfs(node *v) {
    for (auto en: v->rev) {
        dfs(en);
        
        v->sum += en->sum;
    }
    
    v->sum += v->cnt;
}

void add_string(string &s) {
    static int cnt = 0;
    
    if (root == nullptr) root = new node();
    
    auto t = root;
    
    for (auto ch: s) {
        if (!t->go[ch - 'a'])
            t->go[ch - 'a'] = new node();
        
        t = t->go[ch - 'a'];
    }
    
    t->term.push_back(cnt++);
}