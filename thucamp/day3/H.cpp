#include <bits/stdc++.h>
using i64 = long long;
template<class T>
struct Point {
    T x;
    T y;
    Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
    
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(Point p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(Point p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(T v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point &operator/=(T v) & {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, Point b) {
        return a += b;
    }
    friend Point operator-(Point a, Point b) {
        return a -= b;
    }
    friend Point operator*(Point a, T b) {
        return a *= b;
    }
    friend Point operator/(Point a, T b) {
        return a /= b;
    }
    friend Point operator*(T a, Point b) {
        return b *= a;
    }
    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};
 
template<class T>
T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}
 
template<class T>
T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}
 
template<class T>
T square(Point<T> p) {
    return dot(p, p);
}
 
template<class T>
double length(Point<T> p) {
    return std::sqrt(double(square(p)));
}
 
long double length(Point<long double> p) {
    return std::sqrt(square(p));
}
 
template<class T>
Point<T> normalize(Point<T> p) {
    return p / length(p);
}
 
template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()) : a(a_), b(b_) {}
};
 
template<class T>
Point<T> rotate(Point<T> a) {
    return Point(-a.y, a.x);
}
 
template<class T>
int sgn(Point<T> a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}
 
template<class T>
bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) > 0;
}
 
template<class T>
bool pointOnLineRight(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) < 0;
}
 
template<class T>
Point<T> lineIntersection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}
 
template<class T>
bool pointOnSegment(Point<T> p, Line<T> l) {
    return cross(p - l.a, l.b - l.a) == 0 && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x)
        && std::min(l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}
 
template<class T>
bool pointInPolygon(Point<T> a, std::vector<Point<T>> p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    
    return t == 1;
}
 
template<class T>
bool pointOutPolygon(Point<T> a, std::vector<Point<T>> p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    
    return t == 0;
}
 
// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<class T>
std::tuple<int, Point<T>, Point<T>> segmentIntersection(Line<T> l1, Line<T> l2) {
    if (std::max(l1.a.x, l1.b.x) < std::min(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.x, l1.b.x) > std::max(l2.a.x, l2.b.x)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::max(l1.a.y, l1.b.y) < std::min(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (std::min(l1.a.y, l1.b.y) > std::max(l2.a.y, l2.b.y)) {
        return {0, Point<T>(), Point<T>()};
    }
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point<T> p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point<T> p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) {
        return {0, Point<T>(), Point<T>()};
    }
    
    Point p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}
 
template<class T>
bool segmentInPolygon(Line<T> l, std::vector<Point<T>> p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));
        
        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u))
                    || pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l)
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
 
template<class T>
bool segmentOutPolygon(Line<T> l, std::vector<Point<T>> p) {
    int n = p.size();
    if (!pointOutPolygon(l.a, p)) {
        return false;
    }
    if (!pointOutPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));
        
        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (cross(v - u, w - v) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineRight(l.a, Line(v, u))
                    || pointOnLineRight(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineRight(u, l)) {
                        if (pointOnLineRight(w, l)
                            && pointOnLineRight(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineRight(w, l)
                            || pointOnLineRight(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineRight(u, Line(l.b, l.a))) {
                        if (pointOnLineRight(w, Line(l.b, l.a))
                            && pointOnLineRight(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineRight(w, Line(l.b, l.a))
                            || pointOnLineRight(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineRight(u, l)) {
                        if (pointOnLineRight(w, Line(l.b, l.a))
                            || pointOnLineRight(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineRight(w, l)
                            || pointOnLineRight(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
 
constexpr i64 inf = 1E14;
using P = Point<long double>;
const long double Pi = std::acos(-1.0);
long double dis[525][525];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, x0, y0;
    std::cin >> n;
    std::vector<P> a(n);
    for (int i=0;i<n;i++){
        std::cin >> x0 >> y0;
        a[i] = P(5*x0+12*y0, 5*y0-12*x0);
    }
    std::cin >> m;
    std::vector<P> b(m);
    for (int i=0;i<m;i++){
        std::cin >> x0 >> y0;
        b[i] = P(5*x0+12*y0, 5*y0-12*x0);
    }
    assert(n+m<=520);
    
    int p=0; 
    for (int i=1;i<n;i++) 
        if (a[i].x<a[p].x||(a[i].x==a[p].x&&a[i].y>a[p].y)) p=i;
 
    for (int i=0;i<=n+m;i++)
        for (int j=0;j<=n+m;j++)
            dis[i][j]=1e9;
 
    std::vector<P> c(n+m);
    for (int i=0;i<n;i++) c[i]=a[i];
    for (int i=0;i<m;i++) c[i+n]=b[i];
    for (int i=0;i<n+m;i++){
        if (i>=n&&c[i].x<a[p].x) continue;
        for (int j=i+1;j<n+m;j++){
            if (j>=n&&c[j].x<a[p].x) continue;
            if (c[i].x==a[p].x&&c[j].x==a[p].x){
                if ((c[i].y>a[p].y)^(c[j].y>a[p].y)) continue;
            }
            bool flag=segmentOutPolygon(Line(c[i],c[j]), a)&&segmentInPolygon(Line(c[i],c[j]), b);
            if (!flag) continue;
            if (i!=p&&j!=p) dis[i][j]=dis[j][i]=length(c[i]-c[j]);
        }
    }
 
    for (int j=0;j<n;j++)
        if (j!=p&&segmentOutPolygon(Line(a[p],a[j]), a)&&segmentInPolygon(Line(a[p],a[j]), b)){
            if (!pointOnLineLeft(a[j],Line(a[p],a[(p+n-1)%n]))&&!pointOnLineRight(a[j],Line(a[p],a[(p+n-1)%n]))){
                dis[p][j]=length(a[p]-a[j]);
            } else if (!pointOnLineLeft(a[j],Line(a[p],a[(p+1)%n]))&&!pointOnLineRight(a[j],Line(a[p],a[(p+1)%n]))){
                dis[j][n+m]=length(a[p]-a[j]);
            } else {
                if (pointOnLineLeft(a[j],Line(a[p],a[(p+n-1)%n]))) dis[p][j]=length(a[p]-a[j]);
                else dis[j][n+m]=length(a[p]-a[j]);
            }
        }
    assert((dis[(p+1)%n][n+m]<5e8)^(dis[(p+n-1)%n][n+m]<5e8));
        
    for (int j=0;j<m;j++){
        if (b[j].x<a[p].x) continue;
        if (segmentOutPolygon(Line(a[p],b[j]), a)&&segmentInPolygon(Line(a[p],b[j]), b)){
            if (!pointOnLineLeft(b[j],Line(a[p],a[(p+n-1)%n]))&&!pointOnLineRight(b[j],Line(a[p],a[(p+n-1)%n]))){
                dis[p][j+n]=length(a[p]-b[j]);
            } else if (!pointOnLineLeft(b[j],Line(a[p],a[(p+1)%n]))&&!pointOnLineRight(b[j],Line(a[p],a[(p+1)%n]))){
                dis[j+n][n+m]=length(a[p]-b[j]);
            } else {
                if (pointOnLineLeft(b[j],Line(a[p],a[(p+n-1)%n]))) dis[p][j+n]=length(a[p]-b[j]);
                else dis[j+n][n+m]=length(a[p]-b[j]);
            }
        }
    }
    /*
    std::cout<<p<<std::endl;
    std::cout << a[p].x << " " << a[p].y << std::endl;
    std::cout << a[(p+n-1)%n].x << " " << a[(p+n-1)%n].y << std::endl;
    for (int i=0;i<n+m;i++){
        for (int j=0;j<=n+m;j++)std::cout<<(bool)(dis[i][j]<1e7)<<' ';
        std::cout<<std::endl;
    }
    
    for (int i=0;i<=n+m;i++){
        for (int j=0;j<=n+m;j++)std::cout<<(bool)(dis[i][j]<50)<<' ';
        std::cout << std::endl;
    }
    */
    
    //if (n+m>=300) assert(0);
    std::cout.precision(18);
    for (int k=0;k<=n+m;k++)
        for (int i=0;i<=n+m;i++)
            for (int j=0;j<=n+m;j++)
                dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
    
    assert(dis[p][n+m]<=1e8);
    std::cout << dis[p][n+m]/13 << std::endl;
 
    return 0;
}
