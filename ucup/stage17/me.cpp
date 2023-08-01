#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;

constexpr int P(998244353), G(3);
inline void inc(int &x, int y) { (x += y) >= P ? x -= P : 0; }
inline int sum(int x, int y) { return x + y >= P ? x + y - P : x + y; }
inline int sub(int x, int y) { return x - y < 0 ? x - y + P : x - y; }
inline int fpow(int x, int k = P - 2) {
  int r = 1;
  for (; k; k >>= 1, x = 1LL * x * x % P)
    if (k & 1) r = 1LL * r * x % P;
  return r;
}

namespace Polynomial {
using Polynom = std::vector<int>;
std::vector<int> w, inv = {1, 1};
void updateInv(int n) {
  if ((int)inv.size() <= n) {
    int p = inv.size();
    inv.resize(n + 1);
    for (int i = p; i <= n; i++) inv[i] = 1LL * (P - P / i) * inv[P % i] % P;
  }
}
void getOmega(int k) {
  w.resize(k);
  w[0] = 1;
  int base = fpow(G, (P - 1) / (k << 1));
  for (int i = 1; i < k; i++) w[i] = 1LL * w[i - 1] * base % P;
}
void dft(int *a, int n) {
  assert((n & n - 1) == 0);
  for (int k = n >> 1; k; k >>= 1) {
    getOmega(k);
    for (int i = 0; i < n; i += k << 1) {
      for (int j = 0; j < k; j++) {
        int y = a[i + j + k];
        a[i + j + k] = (1LL * a[i + j] - y + P) * w[j] % P;
        inc(a[i + j], y);
      }
    }
  }
}
void dft(Polynom &a) { dft(a.data(), a.size()); }
void idft(int *a, int n) {
  assert((n & n - 1) == 0);
  for (int k = 1; k < n; k <<= 1) {
    getOmega(k);
    for (int i = 0; i < n; i += k << 1) {
      for (int j = 0; j < k; j++) {
        int x = a[i + j], y = 1LL * a[i + j + k] * w[j] % P;
        a[i + j] = sum(x, y), a[i + j + k] = sub(x, y);
      }
    }
  }
  for (int i = 0, inv = P - (P - 1) / n; i < n; i++) a[i] = 1LL * a[i] * inv % P;
  std::reverse(a + 1, a + n);
}
void idft(Polynom &a) { idft(a.data(), a.size()); }
Polynom operator*(Polynom a, Polynom b) {
  int len = a.size() + b.size() - 1;
  if (a.size() <= 8 || b.size() <= 8) {
    Polynom c(len);
    for (unsigned i = 0; i < a.size(); i++)
      for (unsigned j = 0; j < b.size(); j++)
        c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % P;
    return c;
  }
  int n = 1 << std::__lg(len - 1) + 1;
  a.resize(n), b.resize(n);
  dft(a), dft(b);
  for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % P;
  idft(a);
  a.resize(len);
  return a;
}
Polynom inverse(Polynom a) { // return-value: a^{-1}
  int n = a.size();
  assert((n & n - 1) == 0);
  if (n == 1) return {fpow(a[0])};
  int m = n >> 1;
  Polynom b = inverse(Polynom(a.begin(), a.begin() + m)), c = b;
  b.resize(n);
  dft(a), dft(b);
  for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % P;
  idft(a);
  for (int i = 0; i < m; i++) a[i] = 0;
  for (int i = m; i < n; i++) a[i] = P - a[i];
  dft(a);
  for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % P;
  idft(a);
  for (int i = 0; i < m; i++) a[i] = c[i];
  return a;
}
Polynom operator/(Polynom a, Polynom b) { // return-value: c(len = n - m + 1), a = b * c + r
  int n = a.size(), m = b.size();
  if (n < m) return {0};
  int k = n == m ? 1 : 1 << std::__lg(n - m) + 1;
  std::reverse(a.begin(), a.end());
  std::reverse(b.begin(), b.end());
  a.resize(k), b.resize(k), b = inverse(b);
  a = a * b;
  a.resize(n - m + 1);
  std::reverse(a.begin(), a.end());
  return a;
}
std::pair<Polynom, Polynom> operator%(Polynom a, Polynom b) { // return-value: {r(len = n - m + 1), c(len = m - 1)}
  int m = b.size();
  Polynom c = a / b;
  b = b * c;
  a.resize(m - 1);
  for (int i = 0; i < m; i++) a[i] = sub(a[i], b[i]);
  return {c, a};
}
Polynom sqrt(Polynom a) { // return-value: \sqrt{a}
  int len = a.size();
  assert((len & len - 1) == 0);
  assert(a[0] == 1); // warning: sqrtMod is needed if a[0] > 1.
  Polynom b(len), binv{1}, bsqr{1}; // sqrt, sqrt_inv, sqrt_sqr
  Polynom foo, bar;  // temp
  b[0] = 1;
  auto shift = [](int x) { return (x & 1 ? x + P : x) >> 1; }; // quick div 2
  for (int m = 1, n = 2; n <= len; m <<= 1, n <<= 1) {
    foo.resize(n), bar = binv;
    for (int i = 0; i < m; i++) {
      foo[i + m] = sub(sum(a[i], a[i + m]), bsqr[i]);
      foo[i] = 0;
    } 
    binv.resize(n);
    dft(foo), dft(binv);
    for (int i = 0; i < n; i++) foo[i] = 1LL * foo[i] * binv[i] % P;
    idft(foo);
    for (int i = m; i < n; i++) b[i] = shift(foo[i]);
    // inv
    if (n == len) break;
    for (int i = 0; i < n; i++) foo[i] = b[i];
    bar.resize(n), binv = bar;
    dft(foo), dft(bar);
    bsqr.resize(n);
    for (int i = 0; i < n; i++) bsqr[i] = 1LL * foo[i] * foo[i] % P;
    idft(bsqr);
    for (int i = 0; i < n; i++) foo[i] = 1LL * foo[i] * bar[i] % P;
    idft(foo);
    for (int i = 0; i < m; i++) foo[i] = 0;
    for (int i = m; i < n; i++) foo[i] = P - foo[i];
    dft(foo);
    for (int i = 0; i < n; i++) foo[i] = 1LL * foo[i] * bar[i] % P;
    idft(foo);
    for (int i = m; i < n; i++) binv[i] = foo[i];
  }
  return b;
}
Polynom deriv(const Polynom &a) { // derivation
  int n = a.size();
  Polynom b(n - 1);
  for (int i = 1; i < n; i++) b[i - 1] = 1LL * a[i] * i % P;
  return b;
}
Polynom integral(const Polynom &a, int c = 0) {
  int n = a.size();
  updateInv(n);
  Polynom b(n + 1);
  b[0] = c;
  for (int i = 0; i < n; i++) b[i + 1] = 1LL * inv[i + 1] * a[i] % P;
  return b;
}
Polynom ln(Polynom a) {
  int n = a.size();
  assert((n & n - 1) == 0);
  Polynom b = deriv(a);
  a = inverse(a);
  a = a * b;
  a.resize(n - 1);
  return integral(a);
}
Polynom exp(Polynom a) { 
  int n = a.size();
  if (n == 1) {
    assert(a[0] == 0);
    return {1};
  }
  assert((n & n - 1) == 0);
  int m = n >> 1;
  Polynom b = exp(Polynom(a.begin(), a.begin() + m)), c;
  b.resize(n), c = ln(b);
  a.resize(n << 1), b.resize(n << 1), c.resize(n << 1);
  dft(a), dft(b), dft(c);
  for (int i = 0; i < n << 1; i++)
    a[i] = (1LL + P + a[i] - c[i]) * b[i] % P;
  idft(a);
  a.resize(n);
  return a;
}
Polynom power(Polynom a, int k) { // b = a^k -> ln b = k ln a -> b = e^{k ln a}
  assert((a.size() & a.size() - 1) == 0);
  a = ln(a);
  for (int &i: a) i = 1LL * i * k % P;
  return exp(a);
}
} // namespace Polynomial

namespace PolyEI { // Polynomial-MultiEvaluation & Interpolation-Polynomial.
// To calc f(a_i): Construct SegTree with {a} and call multiEval(f).
// To calc f from (a_i, b_i): Construct SegTree with {a} and call interpolate(b).
using namespace Polynomial;
class SegTree {
  std::vector<Polynom> p;
  int n, raw_n;
 public:
  SegTree(std::vector<int> a) {
    raw_n = a.size();
    n = raw_n > 1 ? 1 << std::__lg(raw_n - 1) + 1 : 1;
    p.resize(n << 1);
    for (int i = 0; i < n; i++) p[i + n] = Polynom({1, i < raw_n ? P - a[i] : 0});
    for (int i = n - 1; i; i--) {
      int ls = i << 1, rs = ls | 1, len = p[ls].size() - 1 << 1;
      p[ls].resize(len), p[rs].resize(len);
      dft(p[ls]), dft(p[rs]);
      p[i].reserve(len + 1), p[i].resize(len);
      for (int j = 0; j < len; j++) p[i][j] = 1LL * p[ls][j] * p[rs][j] % P;
      idft(p[i]);
      p[i].push_back(sub(p[i][0], 1));
      p[i][0] = 1;
    }
    dbg(raw_n, n);
  }
  std::vector<int> multiEval(Polynom f) const {
    int m = f.size();
    if (m == 1) return std::vector<int>(raw_n, f[0]);
    Polynom q = p[1];
    q.resize(1 << std::__lg(m - 1) + 1);
    q = inverse(q);
    q.resize(m);
    std::reverse(f.begin(), f.end());
    q = q * f;
    q.resize(m);
    if (m > n) { 
      q = Polynom(q.end() - n, q.end());
    } else {
      q.resize(n);
      std::rotate(q.begin(), q.begin() + m, q.end()); // xxx0000 -> 00000xxx
    }
    for (int k = n, o = 1; k > 1; k >>= 1)
      for (int i = 0; i < n; i += k, o++) {
        if (i >= raw_n) continue;
        int *a = &q[i];
        int const *l = p[o << 1].data(), *r = p[o << 1 | 1].data();
        dft(a, k);
        Polynom foo(k), bar(k);
        for (int j = 0; j < k; j++) foo[j] = 1LL * a[j] * r[j] % P;
        for (int j = 0; j < k; j++) bar[j] = 1LL * a[j] * l[j] % P;
        idft(foo), idft(bar);
        std::copy(foo.end() - k / 2, foo.end(), a);
        std::copy(bar.end() - k / 2, bar.end(), a + k / 2);
      }
    q.resize(raw_n);
    return q;
  }
  Polynom interpolate(std::vector<int> b) const {
    assert(b.size() == raw_n);
    Polynom q(p[1].begin(), p[1].begin() + raw_n + 1);
    std::reverse(q.begin(), q.end());
    q = multiEval(deriv(q));
    for (int i = 0; i < raw_n; i++) q[i] = 1LL * fpow(q[i]) * b[i] % P;
    q.resize(n);
    for (int k = 1, h = n >> 1; k < n; k <<= 1, h >>= 1)
      for (int i = 0, o = h; i < n; i += k << 1, o++) {
        if (i >= raw_n) continue;
        int *a = &q[i], *b = &q[i + k];
        int const *l = p[o << 1].data(), *r = p[o << 1 | 1].data();
        Polynom foo(k << 1), bar(k << 1);
        for (int j = 0; j < k; j++) foo[j] = a[j];
        for (int j = 0; j < k; j++) bar[j] = b[j];
        dft(foo), dft(bar);
        for (int j = 0; j < k << 1; j++)
          foo[j] = (1LL * foo[j] * r[j] + 1LL * bar[j] * l[j]) % P;
        idft(foo);
        std::copy(foo.begin(), foo.end(), a);
      }
    q.resize(raw_n);
    std::reverse(q.begin(), q.end());
    return q;
  }
};
} // namespace PolyEI

using Polynomial::Polynom;
int main() {
  int n, m; readInt(n, m);
  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) scanf("%d",&a[i]);
  for (int i = 0; i < m; i++) readInt(b[i]);
  a = PolyEI::SegTree(b).multiEval(a);
  for (int i: a) printf("%d ", i);
  return 0;
}
