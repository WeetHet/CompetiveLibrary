ll mulmod(ll a, ll b, ll mod) {
    return ((__int128)a * b) % mod;
}

ll modulo(ll base, ll exponent, ll mod) {
    ll x = 1;
    ll y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            x = mulmod(x, y, mod);
        y = mulmod(y, y, mod);
        exponent = exponent / 2;
    }
    return x % mod;
}

bool miillerTest(ll p,int iteration){
    if (p < 2) {
        return false;
    }
    
    if (p != 2 && p % 2 == 0) {
        return false;
    }
    
    ll s = p - 1;
    while (s % 2 == 0) {
        s /= 2;
    }
    
    for (int i = 0; i < iteration; i++) {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1){
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0){
            return false;
        }
    }
    return true;
}
