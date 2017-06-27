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
		shift >>= 1;
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
		shift >>= 1;
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
	if (x < 0) x = Mod(x, b);
	return x;
}

ZZ FindModularInverse(ZZ a, ZZ b) {
	ZZ mcd, x, y;
	EuclidExtendedGcd(a, b, mcd, x, y);
	if (x < 0) x = Mod(x, b);
	return x;
}

int RandomInt(int a, int b) {
	random_device random__device;
	mt19937 eng(random__device());
	uniform_int_distribution<> distr(a, b);
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

void FirstNPrimes(int n) {

}

void FirstNPrimes(ZZ n) {

}

bool IsPrime(int number) {
	return false;
}

bool IsPrime(ZZ number) {
	return false;
}

}
