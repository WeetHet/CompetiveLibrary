class node {
public:
    int val, res;
    node *l, *r, *p;
    bool rev;
    int sz;
    
    node(int _id) {
        val = _id;
        res = _id;
        l = r = p = nullptr;
        rev = false;
        sz = 1;
    }
    
    void pull() {
        // now init from self:
        sz = 1;
        res = val;
        
        // now pull from l:
        if (l != nullptr) {
            l->p = this;
            sz += l->sz;
            res = max(res, l->res);
        }
        // now pull from r:
        if (r != nullptr) {
            r->p = this;
            sz += r->sz;
            res = max(res, r->res);
        }
    }
    
    void push() {
        if (rev) {
            if (l != nullptr) l->rev ^= 1;
            if (r != nullptr) r->rev ^= 1;
            swap(l, r);
            rev = false;
        }
    }
};

void debug_node(node *v, string pref = "") {
    if (v != nullptr) {
        v->push();
        debug_node(v->r, pref + " ");
        cerr << pref << "-" << " " << v->val << '\n';
        debug_node(v->l, pref + " ");
    } else {
        cerr << pref << "-" << " " << "nullptr " << '\n';
    }
}

bool is_bst_root(node *v) {
    if (v == nullptr) {
        return false;
    }
    v->push();
    return (v->p == nullptr || (v->p->l != v && v->p->r != v));
}

void rotate(node *v) {
    node *u = v->p;
    u->push();
    v->push();
    assert(u != nullptr);
    v->p = u->p;
    if (v->p != nullptr) {
        if (v->p->l == u) {
            v->p->l = v;
        }
        if (v->p->r == u) {
            v->p->r = v;
        }
    }
    if (v == u->l) {
        u->l = v->r;
        v->r = u;
    } else {
        u->r = v->l;
        v->l = u;
    }
    u->pull();
    v->pull();
}

void splay(node *v) {
    if (v == nullptr) {
        return;
    }
    while (!is_bst_root(v)) {
        node *u = v->p;
        if (!is_bst_root(u)) {
            if ((u->l == v) ^ (u->p->l == u)) {
                rotate(v);
            } else {
                rotate(u);
            }
        }
        rotate(v);
    }
    v->push();
}

pair<node *, int> find(node *v, const function<int(node *)> &go_to) {
    // go_to returns: 0 -- found; -1 -- go left; 1 -- go right
    // find returns the last vertex on the descent and its go_to
    if (v == nullptr) {
        return {nullptr, 0};
    }
    splay(v);
    int dir;
    while (true) {
        v->push();
        dir = go_to(v);
        if (dir == 0) {
            break;
        }
        node *u = (dir == -1 ? v->l : v->r);
        if (u == nullptr) {
            break;
        }
        v = u;
    }
    splay(v);
    return {v, dir};
}

node *get_leftmost(node *v) {
    return find(v, [&](node *x) { return -1; }).first;
}

node *get_rightmost(node *v) {
    return find(v, [&](node *x) { return 1; }).first;
}

pair<node *, node *> split(node *v, const function<bool(node *)> &is_right) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }
    v->push();
    pair<node *, int> p = find(v, [&](node *u) { return is_right(u) ? -1 : 1; });
    v = p.first;
    if (p.second == -1) {
        node *u = v->l;
        if (u == nullptr) {
            return {nullptr, v};
        }
        u->push();
        v->l = nullptr;
        u->p = v->p;
        u = get_rightmost(u);
        v->p = u;
        v->pull();
        return {u, v};
    } else {
        node *u = v->r;
        if (u == nullptr) {
            return {v, nullptr};
        }
        u->push();
        v->r = nullptr;
        v->pull();
        return {v, u};
    }
}

node *merge(node *v, node *u) {
    if (v == nullptr) {
        u->push();
        return u;
    }
    if (u == nullptr) {
        v->push();
        return v;
    }
    v->push();
    u->push();
    v = get_rightmost(v);
    assert(v->r == nullptr);
    splay(u);
    v->r = u;
    v->pull();
    return v;
}

int get_size(node *v) {
    splay(v);
    return (v != nullptr ? v->sz : 0);
}

int get_res(node *v) {
    splay(v);
    return (v != nullptr ? v->res : 0);
}

node *expose(node *v) {
    if (v == nullptr) return nullptr;
    
    node *c = nullptr;
    
    for (auto u = v; u != nullptr; u = u->p) {
        splay(u);
        u->r = c;
        u->pull();
        c = u;
    }
    
    splay(v);
    return c;
}

void evert(node *&v) {
    expose(v);
    v->rev ^= 1;
}

node *root(node *v) {
    expose(v);
    v = get_leftmost(v);
    expose(v);
    
    return v;
}

bool path(node *v, node *u) {
    if (v == u) return true;
    
    expose(u), expose(v);
    
    return u->p != nullptr;
}

void link(node *v, node *u) {
    if (path(v, u)) return;
    
    evert(v);
    v->p = u;
}

void cut(node *v) {
    expose(v);
    if (v->l == nullptr)
        return;
    v->l->p = nullptr;
    v->l = nullptr;
}

node *lca(node *v, node *u) {
    if (!path(v, u))
        return nullptr;
    expose(v);
    return expose(u);
}

int depth(node *v) {
    expose(v);
    return get_size(v->l);
}

void print(node *t) {
    if (t == nullptr) return;
    print(t->l);
    std::cerr << t->val << ' ';
    print(t->r);
}

void write(node *t) {
    std::cerr << "-----------------\n";
    print(t);
    std::cerr << "\n-----------------\n";
}