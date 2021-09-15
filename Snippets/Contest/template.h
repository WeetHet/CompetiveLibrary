#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define tcT template<class T
#define tcTU tcT, class U

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(size(x))
#define lwb(x, val) (int)(lower_bound(all(x), val) - begin(x))
#define upb(x, val) (int)(upper_bound(all(x), val) - begin(x))
#define mp make_pair
#define ff first
#define ss second
#define forn(i, n) for (int (i) = 0; (i) < (n); ++(i))

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

tcT> using PR = pair<T, T>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

tcT> using V = vector<T>;
using vi = V<int>;
using vll = V<ll>;
using vpi = V<pii>;
using vpl = V<pll>;

inline namespace Helpers {
    tcT, class = void> struct is_iterable: false_type {};
    tcT> struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>>: true_type {};
    tcT> constexpr bool is_iterable_v = is_iterable<T>::value;
    
    tcT, class = void> struct is_readable: false_type {};
    tcT> struct is_readable<T, typename std::enable_if_t<is_same_v<decltype(cin >> declval<T&>()), istream&>>>: true_type {};
    tcT> constexpr bool is_readable_v = is_readable<T>::value;
    
    tcT, class = void> struct is_printable: false_type {};
    tcT> struct is_printable<T, typename std::enable_if_t<is_same_v<decltype(cout << declval<T>()), ostream&>>>: true_type {};
    tcT> constexpr bool is_printable_v = is_printable<T>::value;
}

inline namespace Input {
    tcT> constexpr bool needs_input_v = !is_readable_v<T> && is_iterable_v<T>;
    
    tcT, class ...U> void re(T& t, U&... u);
    tcTU> void re(pair<T,U>& p);
    
    tcT> typename std::enable_if_t<is_readable_v<T>, void> re(T& x) { cin >> x; }
    
    tcT> typename std::enable_if_t<needs_input_v<T>, void> re(T& i);
    tcTU> void re(pair<T, U>& p) { re(p.ff, p.ss); }
    tcT> typename enable_if<needs_input_v<T>, void>::type re(T& i) { for (auto &x: i) re(x); }
    tcT, class ...U> void re(T& t, U&... u) { re(t); re(u...); }
    
#define ints(...) int __VA_ARGS__; re(__VA_ARGS__)
}

inline namespace ToString {
    tcT> constexpr bool needs_output_v = !is_printable_v<T> && is_iterable_v<T>;
    
    tcT> typename std::enable_if_t<is_printable_v<T>, string> ts(T v) {
        stringstream ss; ss << fixed << setprecision(15) << v;
        return ss.str();
    }
    
    tcT> string bit_vec(T t) {
        string res = "{"; forn(i, sz(t)) res += ts(t[i]);
        res += "}"; return res;
    }
    
    string ts(V<bool> v) { return bit_vec(v); }
    template<size_t SZ> string ts(bitset<SZ> b) { return bit_vec(b); }
    tcTU> string ts(pair<T, U> p);
    tcT> typename std::enable_if_t<needs_output_v<T>, string> ts(T v);
    tcTU> string ts(pair<T, U> p) { return "(" + ts(p.ff) + ", " + ts(p.ss) + ")"; }
    
    tcT> typename enable_if<is_iterable_v<T>, string>::type ts_sep(T v, string sep) {
        bool fst = 1; string res = "";
        for (const auto& x: v) {
            if (!fst) res += sep;
            fst = 0; res += ts(x);
        }
        return res;
    }
    
    tcT> typename std::enable_if_t<needs_output_v<T>, string> ts(T v) {
        return "{" + ts_sep(v, ", ") + "}";
    }
}

inline namespace Output {
    tcT> void pr_sep(ostream& os, string, const T& t) { os << ts(t); }
    tcT, class... U> void pr_sep(ostream& os, string sep, const T& t, const U&... u) {
        pr_sep(os, sep, t); os << sep; pr_sep(os, sep, u...);
    }
    
    template<class ...T> void pr(const T&... t) { pr_sep(cout, "", t...); }
    void ps() { cout << "\n"; }
    template<class ...T> void ps(const T&... t) { pr_sep(cout, " ", t...); ps(); }
    template<class ...T> void dbg_out(const T&... t) { pr_sep(cerr, " | ", t...); cerr << endl; }
    void loc_info(int line, string names) {
        cerr << "Line(" << line << ") -> [" << names << "]: "; }
}

namespace Debug {
    template<class ...T> void dbg_out(const T&... t) { pr_sep(cerr, " | ", t...); cerr << endl; }
    void loc_info(int line, string names) { cerr << "Line(" << line << ") -> [" << names << "]: "; }
}

// If using FileIO don't forget to replace define readf
#ifdef LOCAL
#define dbg(...) Debug::loc_info(__LINE__,#__VA_ARGS__), Debug::dbg_out(__VA_ARGS__)
#define readf(FILE) freopen(FILE, "r", stdin)
#else
#define dbg(...) 0
#define readf(FILE) 0
#endif

clock_t startTime = clock();
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

int main() {
    readf("input.txt");
    cin.tie(0)->sync_with_stdio(0);
    
    return 0;
}