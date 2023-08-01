#include<bits/stdc++.h>
#define pb push_back
using u32 = unsigned;
using u64 = unsigned long long;
using u128 = __uint128_t;
u32 output;


constexpr u32 N = 1 << 19 | 1;
constexpr u32 mod = 998244353;
constexpr u32 mod2 = mod * 2;

inline u64 getdiv(u64 x) {
	constexpr u64 base = (-1ull) / mod;
	return u64((u128) x * base >> 64);
}

inline u32 getmod(u64 x) {
	return (u32) x - mod * u32(getdiv(x));
}




struct multi_integer {
	u32 val, ival;
	inline multi_integer() {}
	inline explicit multi_integer(u32 v) {
		val = v;
		ival = ((u64) v << 32) / mod;
	}
	__attribute((always_inline)) u32 operator * (u32 x) const {
		return val * x - u32((u64) x * ival >> 32) * mod;
	}
} wn[N << 1], iwn[N << 1];
u32 lim, shift;

u32 dfta[N], rev[N], w[N];


inline u32 get_index(u32 x, u32 lim) {
	static u32 bak[50];
	int i = 1, lg = std::__lg(lim);
	*bak = x;
	for(int i = 1;i < lg;++i) bak[i] = (u64) bak[i - 1] * bak[i - 1] % mod;
	int res = 0;
	for(int i = lg - 1;i >= 0;--i) if((u64) bak[i] * w[res << i & lim - 1] % mod != 1) 
		res += 1 << lg - 1 - i;
	return res ? lim - res : 0;
}

__attribute((always_inline)) u32 norm1(u32 x) {
	return x >= mod ? x - mod : x;
}
static constexpr u32 mp[4] = {
	0, mod, mod2, mod + mod2
};
inline u32 norm2(u32 x) {
	return x - mp[x>>30];
}
inline u32 norm2_lazy(u32 x) {
	return x - mp[x>>30];
}
inline u32 norm2_ex(u32 x) {
	return x - mp[x>>30];
}
inline u32 pow(u32 a, u32 b, u32 ans = 1) {
	for(;b;b >>= 1, a = (u64) a * a % mod) if(b & 1)
		ans = (u64) ans * a % mod;
	return ans;
}

inline u32 get(u32 x) {
	return ((u64) x << 32) / mod;
}
inline void base_init(u32 len) {
	u32 N = 1;
	for(;N < len;)
		N <<= 1;
	const u32 mid = N >> 1;
	const u32 w = pow(3, mod / N);
	const u32 iw = pow((mod + 1) / 3, mod / N);
	wn[mid] = multi_integer(1);
	iwn[mid] = multi_integer(1);
	for(int i = 1;i < mid;++i) {
		wn[mid + i] = multi_integer((u64) wn[mid + i - 1].val * w % mod);
		iwn[mid + i] = multi_integer((u64) iwn[mid + i - 1].val * iw % mod);
	}
	for(int i = mid - 1;i >= 0;--i) {
		wn[i] = wn[i << 1];
		iwn[i] = iwn[i << 1];
	}
}
inline void init(u32 len) {
	lim = len;
	shift = std::__lg(lim);
}
inline void safe_init(u32 len) {
	lim = 1, shift = 0;
	for(;lim < len;)
		lim <<= 1, ++ shift;
}
inline u32 multi(u32 w, u32 idx) {
	return wn[idx] * w;
}

inline void dft(u32 * a) {
#define trans(a, b, idx) \
	{ \
		const u32 A = norm2(a + b);\
		b = wn[idx] * (a + mod2 - b),\
		a = A; \
	}
#define trans2(a, b) \
	{ \
		const u32 A = norm2(a + b);\
		b = norm2(a + mod2 - b), \
		a = A; \
	}

	for(int mid = lim >> 1;mid != 4;mid >>= 1) {
		for(int j = 0;j != lim;j += mid + mid) {
			for(int k = 0;k != mid;k += 4) {
				const u32 A0 = wn[mid + k + 0] * (a[j + k + 0] + mod2 - a[mid + j + k + 0]);
				const u32 A1 = wn[mid + k + 1] * (a[j + k + 1] + mod2 - a[mid + j + k + 1]);
				const u32 A2 = wn[mid + k + 2] * (a[j + k + 2] + mod2 - a[mid + j + k + 2]);
				const u32 A3 = wn[mid + k + 3] * (a[j + k + 3] + mod2 - a[mid + j + k + 3]);
				a[j + k + 0] = norm2(a[j + k + 0] + a[mid + j + k + 0]);
				a[j + k + 1] = norm2(a[j + k + 1] + a[mid + j + k + 1]);
				a[j + k + 2] = norm2(a[j + k + 2] + a[mid + j + k + 2]);
				a[j + k + 3] = norm2(a[j + k + 3] + a[mid + j + k + 3]);
				a[mid + j + k + 0] = A0;
				a[mid + j + k + 1] = A1;
				a[mid + j + k + 2] = A2;
				a[mid + j + k + 3] = A3;
			}
		}
	}
	for(int j = 0;j != lim;j += 8) {
		trans2(a[j + 0], a[j + 4]);
		trans(a[j + 1], a[j + 5], 5);
		trans(a[j + 2], a[j + 6], 6);
		trans(a[j + 3], a[j + 7], 7);

		trans2(a[j + 0], a[j + 2]);
		trans(a[j + 1], a[j + 3], 3);
		trans2(a[j + 4], a[j + 6]);
		trans(a[j + 5], a[j + 7], 3);

		trans2(a[j + 0], a[j + 1]);
		trans2(a[j + 2], a[j + 3]);
		trans2(a[j + 4], a[j + 5]);
		trans2(a[j + 6], a[j + 7]);
	}
#undef trans
#undef trans2
}


inline void dft_last(u32 * a) {
	int mid = lim >> 1;

	{
		int k = 0, limit = mid / 2 + 1;
		for(;k + 1 != limit;k += 4) {
			a[mid + k + 0] = wn[mid + k + 0] * a[k + 0];
			a[mid + k + 1] = wn[mid + k + 1] * a[k + 1];
			a[mid + k + 2] = wn[mid + k + 2] * a[k + 2];
			a[mid + k + 3] = wn[mid + k + 3] * a[k + 3];
		}
		a[mid + k + 0] = wn[mid + k + 0] * a[k + 0];
	}

	mid >>= 1;

	const u32 A0 = wn[mid + 0] * (a[0] + mod2 - a[mid + 0]);
	a[0] = norm2(a[0] + a[mid + 0]), a[mid + 0] = A0;

	{
		int k = 1;
		for(;k + 3 != mid;k += 4) {
			a[mid + k + 0] = wn[mid + k + 0] * a[k + 0];
			a[mid + k + 1] = wn[mid + k + 1] * a[k + 1];
			a[mid + k + 2] = wn[mid + k + 2] * a[k + 2];
			a[mid + k + 3] = wn[mid + k + 3] * a[k + 3];
		}
		for(;k != mid;k += 1) a[mid + k + 0] = wn[mid + k + 0] * a[k + 0];
	}

	a += mid + mid;

	const u32 A1 = wn[mid + 0] * (a[0] + mod2 - a[mid + 0]);
	a[0] = norm2(a[0] + a[mid + 0]), a[mid + 0] = A1;

	{
		int k = 1;
		for(;k + 3 != mid;k += 4) {
			a[mid + k + 0] = wn[mid + k + 0] * a[k + 0];
			a[mid + k + 1] = wn[mid + k + 1] * a[k + 1];
			a[mid + k + 2] = wn[mid + k + 2] * a[k + 2];
			a[mid + k + 3] = wn[mid + k + 3] * a[k + 3];
		}
		for(;k != mid;k += 1) a[mid + k + 0] = wn[mid + k + 0] * a[k + 0];
	}

	init(lim >> 2);
	dft(a - lim);
	dft(a);
	dft(a + lim);
}

inline u32 div_lim(u32 x) {
	return (x + u64(-x & (lim - 1)) * mod) >> shift;
}
inline void base_idft(u32 * a) {
#define trans(a, b, idx) \
	{ \
		u32 A = norm2_lazy(a), B = iwn[idx] * b; \
		a = A + B; \
		b = A + mod2 - B; \
	}
#define trans2(a, b) \
	{ \
		const u32 A = norm2(a), B = norm2(b); \
		a = A + B; \
		b = A + mod2 - B; \
	}

	for(int j = 0;j != lim;j += 8) {
		trans2(a[j + 0], a[j + 1]);
		trans2(a[j + 2], a[j + 3]);
		trans2(a[j + 4], a[j + 5]);
		trans2(a[j + 6], a[j + 7]);

		trans2(a[j + 0], a[j + 2]);
		trans(a[j + 1], a[j + 3], 3);
		trans2(a[j + 4], a[j + 6]);
		trans(a[j + 5], a[j + 7], 3);

		trans2(a[j + 0], a[j + 4]);
		trans(a[j + 1], a[j + 5], 5);
		trans(a[j + 2], a[j + 6], 6);
		trans(a[j + 3], a[j + 7], 7);
	}
	for(int mid = 8;mid != lim;mid <<= 1) {
		for(int j = 0;j != lim;j += mid + mid) {
			for(int k = 0;k != mid;k += 4) {
				const u32 A0 = norm2_lazy(a[j + k + 0]), B0 = iwn[mid + k + 0] * a[mid + j + k + 0];
				const u32 A1 = norm2_lazy(a[j + k + 1]), B1 = iwn[mid + k + 1] * a[mid + j + k + 1];
				const u32 A2 = norm2_lazy(a[j + k + 2]), B2 = iwn[mid + k + 2] * a[mid + j + k + 2];
				const u32 A3 = norm2_lazy(a[j + k + 3]), B3 = iwn[mid + k + 3] * a[mid + j + k + 3];
				a[mid + j + k + 0] = A0 + mod2 - B0; 
				a[mid + j + k + 1] = A1 + mod2 - B1; 
				a[mid + j + k + 2] = A2 + mod2 - B2; 
				a[mid + j + k + 3] = A3 + mod2 - B3; 
				a[j + k + 0] = A0 + B0;
				a[j + k + 1] = A1 + B1;
				a[j + k + 2] = A2 + B2;
				a[j + k + 3] = A3 + B3;
			}
		}
	}
#undef trans
#undef trans2
}
inline void idft_last_copy(u32 * a, u32 * res) {

#define trans(a, b, idx) \
		{ \
			u32 A = norm2_lazy(a), B = iwn[idx] * b; \
			a = A + B; \
			b = A + mod2 - B; \
		}
#define trans2(a, b) \
		{ \
			const u32 A = norm2(a), B = norm2(b); \
			a = A + B; \
			b = A + mod2 - B; \
		}
	for(int j = 0;j != lim;j += 8) {
		trans2(a[j + 0], a[j + 1]);
		trans2(a[j + 2], a[j + 3]);
		trans2(a[j + 4], a[j + 5]);
		trans2(a[j + 6], a[j + 7]);

		trans2(a[j + 0], a[j + 2]);
		trans(a[j + 1], a[j + 3], 3);
		trans2(a[j + 4], a[j + 6]);
		trans(a[j + 5], a[j + 7], 3);

		trans2(a[j + 0], a[j + 4]);
		trans(a[j + 1], a[j + 5], 5);
		trans(a[j + 2], a[j + 6], 6);
		trans(a[j + 3], a[j + 7], 7);
	}
	for(int mid = 8;mid < lim >> 2;mid <<= 1) {
		for(int j = 0;j != lim;j += mid + mid) {
			for(int k = 0;k != mid;k += 4) {
				const u32 A0 = norm2_lazy(a[j + k + 0]), B0 = iwn[mid + k + 0] * a[mid + j + k + 0];
				const u32 A1 = norm2_lazy(a[j + k + 1]), B1 = iwn[mid + k + 1] * a[mid + j + k + 1];
				const u32 A2 = norm2_lazy(a[j + k + 2]), B2 = iwn[mid + k + 2] * a[mid + j + k + 2];
				const u32 A3 = norm2_lazy(a[j + k + 3]), B3 = iwn[mid + k + 3] * a[mid + j + k + 3];
				a[mid + j + k + 0] = A0 + mod2 - B0; 
				a[mid + j + k + 1] = A1 + mod2 - B1; 
				a[mid + j + k + 2] = A2 + mod2 - B2; 
				a[mid + j + k + 3] = A3 + mod2 - B3; 
				a[j + k + 0] = A0 + B0;
				a[j + k + 1] = A1 + B1;
				a[j + k + 2] = A2 + B2;
				a[j + k + 3] = A3 + B3;
			}
		}
	}
	int mid = lim >> 2;
	for(int j = 0;j != lim;j += mid + mid) {
		for(int k = 0;k != mid;k += 4) {
			const u32 A0 = norm2_lazy(a[j + k + 0]), B0 = iwn[mid + k + 0] * a[mid + j + k + 0];
			const u32 A1 = norm2_lazy(a[j + k + 1]), B1 = iwn[mid + k + 1] * a[mid + j + k + 1];
			const u32 A2 = norm2_lazy(a[j + k + 2]), B2 = iwn[mid + k + 2] * a[mid + j + k + 2];
			const u32 A3 = norm2_lazy(a[j + k + 3]), B3 = iwn[mid + k + 3] * a[mid + j + k + 3];
			a[mid + j + k + 0] = A0 + mod2 - B0; 
			a[mid + j + k + 1] = A1 + mod2 - B1; 
			a[mid + j + k + 2] = A2 + mod2 - B2; 
			a[mid + j + k + 3] = A3 + mod2 - B3; 
		}
	}
	res -= mid;
	mid <<= 1;
	for(int k = mid >> 1;k != mid;k += 4) {
		const u32 A0 = norm2_lazy(a[k + 0]), B0 = iwn[mid + k + 0] * a[mid + k + 0];
		const u32 A1 = norm2_lazy(a[k + 1]), B1 = iwn[mid + k + 1] * a[mid + k + 1];
		const u32 A2 = norm2_lazy(a[k + 2]), B2 = iwn[mid + k + 2] * a[mid + k + 2];
		const u32 A3 = norm2_lazy(a[k + 3]), B3 = iwn[mid + k + 3] * a[mid + k + 3];
		res[k + 0] = norm2_ex(A0 + mod2 - B0);
		res[k + 1] = norm2_ex(A1 + mod2 - B1);
		res[k + 2] = norm2_ex(A2 + mod2 - B2);
		res[k + 3] = norm2_ex(A3 + mod2 - B3);
	}
#undef trans
#undef trans2
}

inline void idft(u32 * a) {
	base_idft(a);
	for(int i = 0;i != lim;++i)
		a[i] = div_lim(a[i]);
}

inline void fill(u32 * a, const u32 * b, u32 len)
{
	memcpy(a, b, len << 2);
	memset(a + len, 0, (lim - len) << 2);
}
inline void sub(u32 & x) { x = x ? x - 1 : mod - 1; }
static const u32 brute_limit = 32;
u32 n, m, M;
u32 a[N << 1], b[N << 1], b2[N], b4[N], c[N << 1], d[N << 1];
u32 ans[N];
u32 o[9][N];
u32 val[9][N << 2];
u32 sgt[9][N << 2];

u32 power_b[N], ex_b[N];
u32 dft_val[N];

inline void prod(u32* a, const u32* b, const u32* c) {
	for(int i = 0;i < lim;i += 4) {
		a[i + 0] = getmod((u64) b[i + 0] * c[i + 0]);
		a[i + 1] = getmod((u64) b[i + 1] * c[i + 1]);
		a[i + 2] = getmod((u64) b[i + 2] * c[i + 2]);
		a[i + 3] = getmod((u64) b[i + 3] * c[i + 3]);
	}
}
inline void solve(u32 dep, u32 l, u32 r, bool good) {

	if(l >= m) {
		std::fill(val[dep] + l * 4, val[dep] + r * 4, 1);
		return ;
	}

	u32 n = r - l;

	static u32 t[N];
	if(n < brute_limit) {
		u32 * x = o[dep] + l;
		for(int i = l;i < r;i += 4) {
			const u32 v0 = b[i + 0] ? mod - b[i + 0] : 0;
			const u32 v1 = b[i + 1] ? mod - b[i + 1] : 0;
			const u32 v2 = b[i + 2] ? mod - b[i + 2] : 0;
			const u32 v3 = b[i + 3] ? mod - b[i + 3] : 0;

			const u32 v01 = (u64) v0 * v1 % mod;
			const u32 v23 = (u64) v2 * v3 % mod;

			const u32 a4 = (u64) v01 * v23 % mod;
			const u32 a3 = ((u64) v01 * (v2 + v3) + (u64) v23 * (v0 + v1)) % mod;
			const u32 a2 = (v01 + v23 + (u64) (v0 + v1) * (v2 + v3)) % mod;
			const u32 a1 = (v0 + v1 + v2 + v3) % mod;

			for(int j = i - l + 3;j > 3;--j) {
				x[j] = ((u64) x[j - 4] * a4 + (u64) x[j - 3] * a3 + (u64) x[j - 2] * a2 + (u64) x[j - 1] * a1 + x[j]) % mod;
			}
			x[3] = (a4 + (u64) x[0] * a3 + (u64) x[1] * a2 + (u64) x[2] * a1 + x[3]) % mod;
			x[2] = (a3 + (u64) x[0] * a2 + (u64) x[1] * a1 + x[2]) % mod;
			x[1] = (a2 + (u64) x[0] * a1 + x[1]) % mod;
			x[0] = norm1(x[0] + a1);
		}

	} else {
		u32 mid0 = (l * 3 + r * 1) >> 2;
		u32 mid1 = (l * 2 + r * 2) >> 2;
		u32 mid2 = (l * 1 + r * 3) >> 2;
		solve(dep + 1, l, mid0, 1);
		solve(dep + 1, mid0, mid1, 1);
		solve(dep + 1, mid1, mid2, 1);
		solve(dep + 1, mid2, r, 1);
		init(n);
		u32* da = val[dep + 1] + l * 4;
		u32* db = val[dep + 1] + mid0 * 4;
		u32* dc = val[dep + 1] + mid1 * 4;
		u32* dd = val[dep + 1] + mid2 * 4;
		if(mid0 >= m) {
			memcpy(dft_val, da, lim << 2);
			memcpy(o[dep] + l, o[dep + 1] + l, lim);
		} else {
			prod(sgt[dep] + l + l, da, db);
			prod(sgt[dep] + mid1 + mid1, dc, dd);
			prod(dft_val, sgt[dep] + l + l, sgt[dep] + mid1 + mid1);
			memcpy(t, dft_val, lim << 2);
			idft(t);
			memcpy(o[dep] + l, t + 1, (lim - 1) << 2);
			sub(o[dep][l + n - 1] = t[0]);
		}
	}

	if(good) {
		init(n << 2);
		memcpy(val[dep] + l * 4 + 1, o[dep] + l, n << 2);
		val[dep][l * 4] = 1;
		if(n >= brute_limit) {
			dft_last(val[dep] + l * 4);
			memcpy(val[dep] + l * 4, dft_val, n << 2);
		} else {
			dft(val[dep] + l * 4);
		}
	}
}
inline void getans(u32 dep, u32 l, u32 r, u32 * a, u32 * cur, bool good, u32 inv) {

	if(l >= m) return ;

	u32 n = r - l;
	if(n < brute_limit) {
		static u32 g[N], B[N];
		memcpy(B + 1, o[dep] + l, (n - 1) << 2);
		*B = 1;
		for(int i = 0;i < n;++i) {
			a[i] = norm1(a[i]);
			u64 sum = 0;
			int j = 0;
			for(;j + 3 <= i;j += 4) {
				sum +=
					(u64) a[j + 0] * B[i - j - 0] +
					(u64) a[j + 1] * B[i - j - 1] +
					(u64) a[j + 2] * B[i - j - 2] +
					(u64) a[j + 3] * B[i - j - 3] ;
			}
			for(;j <= i;++j) sum += (u64) a[j] * B[i - j];
			g[i] = sum % mod;
		}
		for(int i = l;i < r;++i) {
			u32 & x = ans[i];
			const u32 b1 = b[i];
			const u32 b2 = :: b2[i];
			const u32 b3 = (u64) b2 * b1 % mod;
			const u32 b4 = :: b4[i];
			x = ((u64) x * b4 + (u64) g[0 + 0] * b3 + (u64) g[0 + 1] * b2 + (u64) g[0 + 2] * b1 + g[0 + 3]) % mod;
			x = ((u64) x * b4 + (u64) g[4 + 0] * b3 + (u64) g[4 + 1] * b2 + (u64) g[4 + 2] * b1 + g[4 + 3]) % mod;
			if(n != 8) {
				x = ((u64) x * b4 + (u64) g[8 + 0] * b3 + (u64) g[8 + 1] * b2 + (u64) g[8 + 2] * b1 + g[8 + 3]) % mod;
				x = ((u64) x * b4 + (u64) g[12 + 0] * b3 + (u64) g[12 + 1] * b2 + (u64) g[12 + 2] * b1 + g[12 + 3]) % mod;
			}
			x = (u64) x * inv % mod;
		}
		return ;
	}
	static u32 c[N];
	u32 mid0 = (l * 3 + r * 1) >> 2;

	if(mid0 >= m) {
		for(int i = 0;i != n / 4;++i) a[n + i] = a[n / 4 * 3 + i];
		getans(dep + 1, l, mid0, a + n, cur + n, 1, inv);
		return ;
	}

	u32 mid1 = (l * 2 + r * 2) >> 2;
	u32 mid2 = (l * 1 + r * 3) >> 2;

	u32* da = val[dep + 1] + l * 4;
	u32* db = val[dep + 1] + mid0 * 4;
	u32* dc = val[dep + 1] + mid1 * 4;
	u32* dd = val[dep + 1] + mid2 * 4;
	u32* dab = sgt[dep] + l * 2;
	u32* dcd = sgt[dep] + mid1 * 2;

	init(n);
	dft(a);

	prod(cur, a, dcd);
	prod(c, cur, db);

	inv = div_lim(inv);
	idft_last_copy(c, a + n);
	getans(dep + 1, l, mid0, a + n, cur + n, 1, inv);

	if(mid0 >= m) return ;
	init(n);
	prod(c, cur, da);
	idft_last_copy(c, a + n);
	getans(dep + 1, mid0, mid1, a + n, cur + n, 1, inv);

	if(mid1 >= m) return ;
	init(n);
	prod(cur, a, dab);
	prod(c, cur, dd);
	idft_last_copy(c, a + n);
	getans(dep + 1, mid1, mid2, a + n, cur + n, 1, inv);

	if(mid2 >= m) return ;
	init(n);
	prod(c, cur, dc);
	idft_last_copy(c, a + n);
	getans(dep + 1, mid2, r, a + n, cur + n, 1, inv);
}

inline void init_inv(const u32 * a, u32 * res, int n) {
	static u32 pre[N];
	*pre = *a;
	for(int i = 1;i != n;++i) {
		pre[i] = (u64) pre[i - 1] * a[i] % mod;
	}
	u32&all_inv = res[0] = pow(pre[n - 1], mod - 2);
	for(int i = n - 1;i;--i) {
		res[i] = (u64) all_inv * pre[i - 1] % mod;
		all_inv = (u64) all_inv * a[i] % mod;
	}
}

inline void naive() {
	for(u32 i = m - 1;~i;--i) {
		u32 x = b[i], &ret = ans[i] = 0;
		for(int i = n - 1;~i;--i) {
			ret = ((u64) ret * x + a[i]) % mod;
		}
	}
}
typedef std::vector<u32> vi;
vi mult_eval(vi A,vi B) {
	//cin >> n >> m;
    n=A.size(); m=B.size();
	for(M = 1;M < n || M < m;) M <<= 1;
	const int max_ask = 1 << 19;
	if(M > max_ask)
		M = max_ask;

	base_init(M);

	for(u32 i = 0;i < n;++i) a[i]=A[i];
	for(u32 i = 0;i < m;++i) b[i]=B[i];
	if((u64) n * m < 500000) naive();
	else {
		init(M);
		fill(dfta, a, n);
		dft(dfta);
		for(int i = 1;i < lim;++i) rev[i] = rev[i >> 1] >> 1 | i % 2 * lim / 2;
		const int GG = pow(3, mod / lim);
		for(int i = 0, multi = 1;i < lim;++i) {
			a[rev[lim - i]] = (u64) dfta[rev[i]] * multi % mod;
			w[i] = multi;
			multi = (u64) multi * GG % mod;
		}
		*a = *dfta;

		u32 res = 0;
		for(int i = 0;i < m;++i) {
			power_b[i] = b[i];
		}
		static u32 og[N];
		init(M), lim = m;

		prod(power_b, power_b, power_b);
		memcpy(b2, power_b, m << 2);
		prod(power_b, power_b, power_b);
		memcpy(b4, power_b, m << 2);

		for(int i = 2;i < shift;++i) {
			prod(power_b, power_b, power_b);
		}
		init(M);
		for(int i = m;i < lim;++i) {
			power_b[i] = 1;
		}
		for(int i = 0;i < lim;++i) {
			power_b[i] = norm1(norm2(power_b[i] + mod - 1));
			if(power_b[i] == 0) {
				og[i] = b[i];
				b[i] = 3;
			}
		}

		solve(0, 0, M, 0);
		init(M);
		init_inv(dft_val, d, M);
		prod(a, d, a);
		idft(a);
		for(u32 i = 0;i < M;++i) a[i] = norm2(a[i]);
		static u32 cur[N << 1];
		getans(0, 0, M, a, cur, 0, 1);
		for(int i = 0;i < m;++i) {
			if(power_b[i]) {
				ans[i] = (u64) ans[i] * (mod - power_b[i]) % mod;
			} else {
				ans[i] = norm1(dfta[rev[get_index(og[i], M)]]);
			}
		}
	}
    vi ret(0);
	for(u32 i = 0;i<m;i++) {
        ret.pb(ans[i]);
	}
    return ret;
}
const double PI=acos(-1.0);
typedef long long ll;
namespace fft
{
    struct num
    {
        double x,y;
        num() {x=y=0;}
        num(double x,double y):x(x),y(y){}
    };
    inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
    inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
    inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
    inline num conj(num a) {return num(a.x,-a.y);}

    int base=1;
    std::vector<num> roots={{0,0},{1,0}};
    vi rev={0,1};
    const double PI=acosl(-1.0);

    void ensure_base(int nbase)
    {
        if(nbase<=base) return;
        rev.resize(1<<nbase);
        for(int i=0;i<(1<<nbase);i++)
            rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));
        roots.resize(1<<nbase);
        while(base<nbase)
        {
            double angle=2*PI/(1<<(base+1));
            for(int i=1<<(base-1);i<(1<<base);i++)
            {
                roots[i<<1]=roots[i];
                double angle_i=angle*(2*i+1-(1<<base));
                roots[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
            }
            base++;
        }
    }

    void fft(std::vector<num> &a,int n=-1)
    {
        if(n==-1) n=a.size();
        assert((n&(n-1))==0);
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for(int i=0;i<n;i++)
            if(i<(rev[i]>>shift))
               std::swap(a[i],a[rev[i]>>shift]);
        for(int k=1;k<n;k<<=1)
        {
            for(int i=0;i<n;i+=2*k)
            {
                for(int j=0;j<k;j++)
                {
                    num z=a[i+j+k]*roots[j+k];
                    a[i+j+k]=a[i+j]-z;
                    a[i+j]=a[i+j]+z;
                }
            }
        }
    }

    std::vector<num> fa,fb;

    vi multiply(vi &a, vi &b)
    {
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<sz;i++)
        {
            int x=(i<(int)a.size()?a[i]:0);
            int y=(i<(int)b.size()?b[i]:0);
            fa[i]=num(x,y);
        }
        fft(fa,sz);
        num r(0,-0.25/sz);
        for(int i=0;i<=(sz>>1);i++)
        {
            int j=(sz-i)&(sz-1);
            num z=(fa[j]*fa[j]-conj(fa[i]*fa[i]))*r;
            if(i!=j) fa[j]=(fa[i]*fa[i]-conj(fa[j]*fa[j]))*r;
            fa[i]=z;
        }
        fft(fa,sz);
        vi res(need);
        for(int i=0;i<need;i++) res[i]=fa[i].x+0.5;
        return res;
    }

    vi multiply_mod(vi &a,vi &b,int m,int eq=0)
    {
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<(int)a.size();i++)
        {
            int x=(a[i]%m+m)%m;
            fa[i]=num(x&((1<<15)-1),x>>15);
        }
        fill(fa.begin()+a.size(),fa.begin()+sz,num{0,0});
        fft(fa,sz);
        if(sz>(int)fb.size()) fb.resize(sz);
        if(eq) copy(fa.begin(),fa.begin()+sz,fb.begin());
        else
        {
            for(int i=0;i<(int)b.size();i++)
            {
                int x=(b[i]%m+m)%m;
                fb[i]=num(x&((1<<15)-1),x>>15);
            }
            fill(fb.begin()+b.size(),fb.begin()+sz,num{0,0});
            fft(fb,sz);
        }
        double ratio=0.25/sz;
        num r2(0,-1),r3(ratio,0),r4(0,-ratio),r5(0,1);
        for(int i=0;i<=(sz>>1);i++)
        {
            int j=(sz-i)&(sz-1);
            num a1=(fa[i]+conj(fa[j]));
            num a2=(fa[i]-conj(fa[j]))*r2;
            num b1=(fb[i]+conj(fb[j]))*r3;
            num b2=(fb[i]-conj(fb[j]))*r4;
            if(i!=j)
            {
                num c1=(fa[j]+conj(fa[i]));
                num c2=(fa[j]-conj(fa[i]))*r2;
                num d1=(fb[j]+conj(fb[i]))*r3;
                num d2=(fb[j]-conj(fb[i]))*r4;
                fa[i]=c1*d1+c2*d2*r5;
                fb[i]=c1*d2+c2*d1;
            }
            fa[j]=a1*b1+a2*b2*r5;
            fb[j]=a1*b2+a2*b1;
        }
        fft(fa,sz);fft(fb,sz);
        vi res(need);
        for(int i=0;i<need;i++)
        {
            ll aa=fa[i].x+0.5;
            ll bb=fb[i].x+0.5;
            ll cc=fa[i].y+0.5;
            res[i]=(aa+((bb%m)<<15)+((cc%m)<<30))%m;
        }
        return res;
    }
    vi square_mod(vi &a,int m)
    {
        return multiply_mod(a,a,m,1);
    }
};
const int maxn=2e5+5;
int inv[maxn];
int _n,_a[maxn],_ans[maxn];
char _s[maxn];
vi solve(int l,int r){
	if (l==r){
		if (_s[l]=='+') return (vi){mod-(l-1),1};
		else return (vi){mod-(l+1),1};
	}
	int mid=(l+r)>>1;
	vi T1=solve(l,mid);
	vi T2=solve(mid+1,r);
	vi Q(r-mid);
	for (int i=mid+1;i<=r;i++) Q[i-(mid+1)]=i;
	vi R=mult_eval(T1,Q);
	for (int i=mid+1;i<=r;i++) _ans[i]=1ll*_ans[i]*R[i-(mid+1)]%mod;
	return fft::multiply_mod(T1,T2,mod);
}
int jc[maxn],njc[maxn];
int main(){
    std::cin >> _n;
	for (int i=0;i<_n;i++) std::cin >> _a[i];
    std::cin >> _s+1;
	inv[1]=1; for (int i=2;i<maxn;i++) inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
	jc[0]=njc[0]=1; for (int i=1;i<maxn;i++) jc[i]=1ll*jc[i-1]*i%mod,njc[i]=1ll*njc[i-1]*inv[i]%mod;
	_ans[0]=1;
	for (int i=1;i<_n;i++) _ans[i]=1;
	vi tmp=solve(1,_n-1);
	for (int i=1;i<_n;i++){
		_ans[i]=1ll*_ans[i]*njc[i]%mod;
		if (_s[i]=='-') _ans[i]=mod-_ans[i];
	}
	int sum=0;
	for (int i=0;i<_n;i++) sum=(sum+1ll*_ans[i]*_a[i])%mod;
    std::cout << 1ll*sum*jc[_n-1]%mod << '\n';
}
