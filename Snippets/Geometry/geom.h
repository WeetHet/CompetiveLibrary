inline namespace geometry {
    using T = long long; // or long double if needed
    
    struct pt {
        T x = 0, y = 0;
        
        pt(T x, T y) : x(x), y(y) {}
        
        pt(pt p1, pt p2) { *this = pt(p2.x - p1.x, p2.y - p1.y); }
        
        pt() = default;
        
        bool operator==(const pt &rhs) const { return x == rhs.x && y == rhs.y; }
        bool operator!=(const pt &rhs) const { return !(rhs == *this); }
    };
    
    T dot(const pt& a, const pt& b) { return a.x * b.x + a.y * b.y; }
    T cross(const pt& a, const pt& b) { return a.x * b.y - a.y * b.x; }
    
    T sq(T a) { return a * a; }
    T norm(const pt &p) { return sq(p.x) + sq(p.y); }
    ld len(const pt &p) { return sqrtl(norm(p)); }
    
    T arg(const pt &p) { return atan2(p.y, p.x); }
    pt conj(const pt &p) { return pt(p.x, -p.y); }
    pt perp(const pt &p) { return pt(-p.y, p.x); }
    pt dir(T ang) { return pt(cos(ang), sin(ang)); }
    
    pt operator-(const pt &l) { return pt(-l.x, -l.y); }
    pt operator+(const pt &l, const pt &r) { return pt(l.x + r.x, l.y + r.y); }
    pt operator-(const pt &l, const pt &r) { return pt(l.x - r.x, l.y - r.y); }
    pt operator*(const pt &l, const T &r) { return pt(l.x * r, l.y * r); }
    pt operator*(const T &l, const pt &r) { return r * l; }
    pt operator/(const pt &l, const T &r) { return pt(l.x / r, l.y / r); }
    pt &operator+=(pt &l, const pt &r) { return l = l + r; }
    pt &operator-=(pt &l, const pt &r) { return l = l - r; }
    pt &operator*=(pt &l, const T &r) { return l = l * r; }
    pt &operator/=(pt &l, const T &r) { return l = l / r; }
    
    pt unit(const pt& p) { return p / len(p); }
    
    istream& operator>>(istream &is, pt &p) {
        is >> p.x >> p.y; return is; }
    
    ostream& operator<<(ostream &os, const pt &p) {
        os << p.x << ' ' << p.y; return os; }
}
