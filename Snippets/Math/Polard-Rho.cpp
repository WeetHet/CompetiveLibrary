ll gcd(ll m, ll n) {
    while (true) {
        ll r = m % n;
        if (r == 0) {
            return n;
        }
        m = n;
        n = r;
    }
}

ll rho(ll n) {
    if(n % 2 == 0)
        return 2;
    
    ll x = rng() % n + 1;
    ll c = rng() % n + 1;
    ll y = x, g = 1;
    
    while (g == 1) {
        x = (((__int128)x * x) % n + c) % n;
        y = (((__int128)y * y) % n + c) % n;
        y = (((__int128)y * y) % n + c) % n;
        g = gcd(abs(x - y), n);
    }
    
    return g;
}
