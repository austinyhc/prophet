#include <bits/stdc++.h>

#define fastio() std::ios_base::sync_with_stdio(false); std::cin.tie(NULL); std::cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#ifndef ONLINE_JUDGE
#define dbg(x) std::cout << #x << " "; _print(x); std::cout << endl;
#else
#define dbg(x)
#endif

inline void _print(ll t)          {std::cout << t;}
inline void _print(int t)         {std::cout << t;}
inline void _print(std::string t) {std::cout << t;}
inline void _print(char t)        {std::cout << t;}
inline void _print(lld t)         {std::cout << t;}
inline void _print(double t)      {std::cout << t;}
inline void _print(ull t)         {std::cout << t;}

template<class T, class V> void _print(std::pair<T, V> p);
template<class T, class V> void _print(std::map<T, V> v);
template<class T, class V> void _print(std::unordered_map<T, V> v);
template<class T> void _print(std::vector<T> v);
template<class T> void _print(std::multiset<T> v);
template<class T> void _print(std::set<T> v);

template<class T, class V>
void _print(std::pair<T, V> p) {
    std::cout << "{";
    _print(p.first);
    std::cout << ",";
    _print(p.second);
    std::cout << "}";
}

template<class T, class V>
void _print(std::map<T, V> v) {
    std::cout << "[ ";
    for (auto i : v) {
        _print(i);
        std::cout << " ";
    }
    std::cout << "]";
}

template<class T, class V>
void _print(std::unordered_map<T, V> v) {
    std::cout << "[ ";
    for (auto i : v) {
        _print(i);
        std::cout << " ";
    }
    std::cout << "]";
}

template<class T>
void _print(std::vector<T> v) {
    std::cout << "[ ";
    for (T i : v) {
        _print(i);
        std::cout << " ";
    }
    std::cout << "]";
}

template<class T>
void _print(std::set<T> v) {
    std::cout << "[ ";
    for (T i : v) {
        _print(i);
        std::cout << " ";
    }
    std::cout << "]";
}

template<class T>
void _print(std::multiset<T> v) {
    std::cout << "[ ";
    for (T i : v) {
        _print(i);
        std::cout << " ";
    }
    std::cout << "]";
}

