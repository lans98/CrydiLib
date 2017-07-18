// =========================================================================
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// =========================================================================

// =========================================================================
// Disclaimer notes:
//  This library is not intended to be a viable option for use in situations
//  of reliability and robustness, several of these algorithms need to be
//  better implemented, this library serves to demonstrate certain algorithms
//  applied to the theory of numbers, also serves as an example as a basis
//  for creating a library (quite simple).
// =========================================================================

#include "inc/crydi3_tools.h"

namespace crydi {

int EuclidGcd(int a, int b) {
	int mod;
	while (b > 0) {
		mod = Mod(a,b);
		a = b;
		b = mod;
	}
	return a;
}

long EuclidGcd(long a, long b) {
	long mod;
	while (b > 0) {
		mod = Mod(a,b);
		a = b;
		b = mod;
	}
	return a;
}

ZZ EuclidGcd(ZZ a, ZZ b) {
	ZZ mod;
	while (b > 0) {
		mod = Mod(a, b);
		a = b;
		b = mod;
	}
	return a;
}

int SteinGcd(int a, int b) {
	int shift {1};

	while ((a & b & 1) == 0) {
		a >>= 1;
		b >>= 1;
		shift <<= 1;
	}

	while (a != 0) {
		if ((a & 1) == 0) {
			a >>= 1;
		} else if ((b & 1) == 0) {
			b >>= 1;
		} else {
			if (a >= b)
				a = (a - b) >> 1;
			else
				b = (b - a) >> 1;
		}
	}
	return shift * b;
}

long SteinGcd(long a, long b) {
	long shift {1};

	while ((a & b & 1) == 0) {
		a >>= 1;
		b >>= 1;
		shift <<= 1;
	}

	while (a != 0) {
		if ((a & 1) == 0) {
			a >>= 1;
		} else if ((b & 1) == 0) {
			b >>= 1;
		} else {
			if (a >= b)
				a = (a - b) >> 1;
			else
				b = (b - a) >> 1;
		}
	}
	return shift * b;
}

ZZ SteinGcd(ZZ a, ZZ b) {
	ZZ shift {1};

	while ((a & b & 1) == 0) {
		a >>= 1;
		b >>= 1;
		shift <<= 1;
	}

	while (a != 0) {
		if ((a & 1) == 0) {
			a >>= 1;
		} else if ((a & 1) == 0) {
			b >>= 1;
		} else {
			if (a >= b)
				a = (a - b) >> 1;
			else
				b = (b - a) >> 1;
		}
	}
	return shift * b;
}

int Gcd(int a, int b, gcd_flag algorithm) {
	if (algorithm & STEIN_GCD)
		return SteinGcd(a, b);
	if (algorithm & EUCLID_GCD)
		return EuclidGcd(a, b);
	return -1;
}

long Gcd(long a, long b, gcd_flag algorithm) {
	if (algorithm & STEIN_GCD)
		return SteinGcd(a, b);
	if (algorithm & EUCLID_GCD)
		return EuclidGcd(a, b);
	return -1;
}

ZZ Gcd(ZZ a, ZZ b, gcd_flag algorithm) {
	if (algorithm & STEIN_GCD)
		return SteinGcd(a, b);
	if (algorithm & EUCLID_GCD)
		return EuclidGcd(a, b);
	return ZZ(-1);
}

void EuclidExtendedGcd(int a, int b, int &mcd, int &x, int &y) {
	mcd = a;
	x = 1;
	y = 0;

	int x_2 {0}, y_2 {1};
	int q {}, mod {};

	while (b > 0) {
		q = mcd/b;

		mod = Mod(mcd, b);
		mcd = b;
		b = mod;

		mod = x - (q * x_2);
		x = x_2;
		x_2 = mod;

		mod = y - (q * y_2);
		y = y_2;
		y_2 = mod;
	}
}

void EuclidExtendedGcd(long a, long b, long &mcd, long &x, long &y) {
	mcd = a;
	x = 1;
	y = 0;

	int x_2 {0}, y_2 {1};
	int q {}, mod {};

	while (b > 0) {
		q = mcd/b;

		mod = Mod(mcd, b);
		mcd = b;
		b = mod;

		mod = x - (q * x_2);
		x = x_2;
		x_2 = mod;

		mod = y - (q * y_2);
		y = y_2;
		y_2 = mod;
	}
}

void EuclidExtendedGcd(ZZ a, ZZ b, ZZ &mcd, ZZ &x, ZZ &y) {
	mcd = a;
	x = 1;
	y = 0;

	ZZ x_2 {0}, y_2 {1};
	ZZ q {}, mod {};

	while (b > 0) {
		q = mcd/b;

		mod = Mod(mcd, b);
		mcd = b;
		b = mod;

		mod = x - (q * x_2);
		x = x_2;
		x_2 = mod;

		mod = y - (q * y_2);
		y = y_2;
		y_2 = mod;
	}
}

int FindModularInverse(int a, int b) {
	int mcd, x, y;
	EuclidExtendedGcd(a, b, mcd, x, y);
	return Mod(x,b);
}

long FindModularInverse(long a, long b) {
	long mcd, x, y;
	EuclidExtendedGcd(a, b, mcd, x, y);
	return Mod(x,b);
}

ZZ FindModularInverse(ZZ a, ZZ b) {
	ZZ mcd, x, y;
	EuclidExtendedGcd(a, b, mcd, x, y);
	return Mod(x,b);
}

int RandomInt(int a, int b) {
	random_device random__device;
	mt19937 eng(random__device());
	uniform_int_distribution<> distr(a, b);
	return distr(eng);
}

long RandomLong(long a, long b) {
	random_device random__device;
	mt19937 eng(random__device());
	uniform_int_distribution<long> distr(a, b);
	return distr(eng);
}

int ModularExp(int base, int exp, int mod) {
	int result = 1;

	while (exp != 0) {
		if (exp & 1)
			result = Mod(result * base, mod);
		base = Mod(base * base, mod);
		exp >>= 1;
	}

	return result;
}

long ModularExp(long base, long exp, long mod) {
	long result = 1;

	while (exp != 0) {
		if (exp & 1)
			result = Mod(result * base, mod);
		base = Mod(base * base, mod);
		exp >>= 1;
	}
	return result;
}

ZZ ModularExp(ZZ base, ZZ exp, ZZ mod) {
	ZZ result {1};

	while (exp != 0) {
		if ((exp & 1) == 1)
			result = Mod(result * base, mod);
		base = Mod(base * base, mod);
		exp >>= 1;
	}

	return result;
}

__random__ random;

void InitSeeds() {
    if (__already_init_seed) return;
    short *rand_obj = new short;
    random.seed = reinterpret_cast<uintmax_t>(rand_obj) | 1UL;

    milliseconds time_ms {
      duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
      )
    };

    random.c = reinterpret_cast<uintmax_t>((random.seed >> 11) ^ (time_ms.count() << 7)) | 1UL;
    random.a = reinterpret_cast<uintmax_t>((random.seed << 11) ^ (time_ms.count() >> 7)) | 1UL;

    delete rand_obj;
    __already_init_seed = true;
}

uintmax_t GenRandomLong(uintmax_t max) {
  if (!__already_init_seed) InitSeeds();
  uintmax_t rand_num = Mod(random.a * random.seed + random.c, max);
  random.seed = rand_num;
  return rand_num;
}

ZZ GenRandomZZ(int num_bits) {
  int total_count = 0;
  uintmax_t temp_num;
  string num = "";
  while (total_count < num_bits) {
    temp_num = GenRandomLong(numeric_limits<uintmax_t>::max());
    num += NumberToString(temp_num);
    total_count += CountBits(temp_num);
  }
  NTL:ZZ final_num = StringToNumber<ZZ>(num);
  total_count = CountBits(final_num);
  if (total_count > num_bits) {
    final_num >>= (total_count - num_bits);
  }
  return final_num;
}

int GenRandomIntPrime(int min, uintmax_t k) {
  int random_num = RandomInt(min, numeric_limits<int>::max());
	while (!MillerRabinTest(random_num, k))  {
    if (random_num & 1)
      random_num += 2;
    else
      random_num += 1;
	}
	return random_num;
}

long GenRandomLongPrime(long min, uintmax_t k) {
	long random_num = RandomLong(min, numeric_limits<long>::max());
	while (!MillerRabinTest(random_num, k)) {
    if (random_num & 1)
      random_num += 2;
    else
      random_num += 1;
  }
	return random_num;
}

ZZ GenRandomZZPrime(long num_bits, uintmax_t k) {
	ZZ random_num = GenRandomZZ(num_bits);
	while (!MillerRabinTest(random_num, k)) {
    if ((random_num & 1) == 1)
      random_num += 2;
    else
      random_num += 1;
  }
	return random_num;
}

bool FermatTest(const int &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	int a;
	vector<int> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomInt(2, n);
		} while (
				(Gcd(n, a) != 1) ||
				(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		if (ModularExp(a, n - 1, n) != 1) return false;
	}
	return true;
}

bool FermatTest(const long &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	long a;
	vector<long> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomLong(2, n);
		} while (
			(Gcd(n, a) != 1)	||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		if (ModularExp(a, n - 1, n) != 1) return false;
	}
	return true;
}

bool FermatTest(const ZZ &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	ZZ a;
	vector<ZZ> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomLen_ZZ(n.size() * 64);
			a = Mod(a, n);
		} while (
			(a < 3) ||
			(Gcd(n, a) != 1) ||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		if (ModularExp(a, n - 1, n) != 1) return false;
	}
	return true;
}

bool EulerTest(const int &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	int a;
	vector<int> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomInt(2, n);
		} while (
			(Gcd(n, a) != 1) ||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		a = ModularExp(a, (n - 1) >> 1, n);
		if (a != 1 && a != n - 1) return false;
	}
	return true;
}

bool EulerTest(const long &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	long a;
	vector<long> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomLong(2, n);
		} while (
			(Gcd(n, a) != 1) ||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		a = ModularExp(a, (n - 1) >> 1, n);
		if (a != 1 && a != n - 1) return false;
	}
	return true;
}

bool EulerTest(const ZZ &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	ZZ a;
	vector<ZZ> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomLen_ZZ(n.size() * 64);
			a = Mod(a , n);
		} while (
			(a < 3)	||
			(Gcd(n, a) != 1) ||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		a = ModularExp(a, (n - 1) >> 1, n);
		if (a != 1 && a != n - 1) return false;
	}
	return true;
}

bool MillerRabinTest(const int &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	int m = n - 1;
	uintmax_t r = 0;
	while ((m & 1) == 0) {
		m >>= 1;
		++r;
	}

	int a;
	vector<int> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomInt(2, n);
		}	while (
			(Gcd(n, a) != 1)	||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		a = ModularExp(a, m, n);
		if (a == 1 || a == n - 1) continue;

		for (uintmax_t j = 1; j < r; ++j) {
			a = ModularExp(a, 2, n);
			if (a == 1) return false;
			if (a == n - 1) break;
		}
		if (a != 1 && a != n - 1) return false;
	}
	return true;
}

bool MillerRabinTest(const long &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	long m = n - 1;
	uintmax_t r = 0;
	while ((m & 1) == 0) {
		m >>= 1;
		++r;
	}

	long a;
	vector<long> used_bases;

	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomLong(2, n);
		} while (
			(Gcd(n, a) != 1)	||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		a = ModularExp(a, m, n);
		if (a == 1 || a == n - 1) continue;

		for (uintmax_t j = 1; j < r; ++j) {
			a = ModularExp(a, 2L, n);
			if (a == 1) return false;
			if (a == n - 1) break;
		}
		if (a != 1 && a != n - 1) return false;
	}
	return true;
}

bool MillerRabinTest(const ZZ &n, uintmax_t k) {
	if ((n & 1) == 0)
		return false;
	if (n == 2)
		return true;

	ZZ m = n - 1;
	uintmax_t r {0L};
	while ((m & 1) == 0) {
		m >>= 1;
		++r;
	}

	ZZ a;
	vector<ZZ> used_bases;
	for (uintmax_t i = 0; i < k; ++i) {
		do {
			a = RandomLen_ZZ(n.size() * 64);
			a = Mod(a,n);
		} while(
			(a < 3)	||
			(Gcd(n,a) != 1) ||
			(find(used_bases.begin(), used_bases.end(), a) != used_bases.end())
		);
		used_bases.push_back(a);

		a = ModularExp(a, m, n);
		if (a == 1 || a == n - 1) continue;

		for (uintmax_t j = 1; j < k; ++j) {
			a = ModularExp(a, ZZ(2L), n);
			if (a == 1) return false;
			if (a == n - 1) break;
		}
		if (a != 1 && a != n - 1) return false;
	}
	return true;
}

bool IsPrime(const int &n, uintmax_t k, prim_test_flag flag) {
	if (flag & MILLER_RABIN_TEST)
		return MillerRabinTest(n, k);
	if (flag & EULER_TEST)
		return EulerTest(n, k);
	if (flag & FERMAT_TEST)
		return FermatTest(n, k);
	throw string("Bad flag sended, unknown flag with code = " + NumberToString(flag));
}

bool IsPrime(const long &n, uintmax_t k, prim_test_flag flag) {
	if (flag & MILLER_RABIN_TEST)
		return MillerRabinTest(n, k);
	if (flag & EULER_TEST)
		return EulerTest(n, k);
	if (flag & FERMAT_TEST)
		return FermatTest(n, k);
	throw string("Bad flag sended, unknown flag with code = " + NumberToString(flag));
}

bool IsPrime(const ZZ &n, uintmax_t k, prim_test_flag flag) {
	if (flag & MILLER_RABIN_TEST)
		return MillerRabinTest(n, k);
	if (flag & EULER_TEST)
		return EulerTest(n, k);
	if (flag & FERMAT_TEST)
		return FermatTest(n, k);
	throw string("Bad flag sended, unknown flag with code = " + NumberToString(flag));
}

int CRT(int *a, int *p, int n) {
  int P = 1;
  for (int i = 0; i < n; ++i)
    P *= p[i];

  int inv_temp, p_temp, final_sol = 0;
  for (int i = 0; i < n; ++i) {
    p_temp = P/p[i];
    inv_temp = FindModularInverse(p_temp, p[i]);
    final_sol += Mod(a[i] * inv_temp * p_temp, P);
  }
  return Mod(final_sol, P);
}

long CRT(long *a, long *p, int n) {
  long P = 1;
  for (int i = 0; i < n; ++i)
    P *= p[i];

  long inv_temp, p_temp, final_sol = 0;
  for (int i = 0; i < n; ++i) {
    p_temp = P/p[i];
    inv_temp = FindModularInverse(p_temp, p[i]);
    final_sol += Mod(a[i] * inv_temp * p_temp, P);
  }
  return Mod(final_sol, P);
}

ZZ CRT(ZZ *a, ZZ *p, int n) {
  ZZ P(1);
  for (int i = 0; i < n; ++i)
    P *= p[i];

  ZZ inv_temp, p_temp, final_sol(0);
  for (int i = 0; i < n; ++i) {
    p_temp = P/p[i];
    inv_temp = FindModularInverse(p_temp, p[i]);
    final_sol += Mod(a[i] * inv_temp * p_temp, P);
  }
  return Mod(final_sol, P);
}


}
