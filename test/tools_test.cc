#include "../src/inc/crydi3.h"
#include <cassert>

NTL_CLIENT

#undef NDEBUG

int main() {
#ifndef NDEBUG
	printf("Debugging mode!");
#endif
	int ia, ib;
	ZZ  za, zb;
	
	ia = crydi::RandomInt(2, numeric_limits<int>::max());
	ib = crydi::RandomInt(2, numeric_limits<int>::max());
	za = RandomLen_ZZ(1024);
	zb = RandomLen_ZZ(1024);

	assert(ia == (ib*(ia/ib) + crydi::Mod(ia,ib)));
	assert(za == (zb*(za/zb) + crydi::Mod(za,zb)));

	// Euclid gcd test
	int gcd_int = crydi::Gcd(ia, ib, crydi::EUCLID_GCD);
	ZZ  gcd_zz  = crydi::Gcd(za, zb, crydi::EUCLID_GCD);
	assert(crydi::Mod(ia, gcd_int) == 0 && crydi::Mod(ib, gcd_int) == 0);
	assert(crydi::Mod(za, gcd_zz) == 0 && crydi::Mod(zb, gcd_zz) == 0);

	// Stein gcd test 
	gcd_int = crydi::Gcd(ia, ib, crydi::STEIN_GCD);
	gcd_zz = crydi::Gcd(za, zb, crydi::STEIN_GCD);
	assert(crydi::Mod(ia, gcd_int) == 0 && crydi::Mod(ib, gcd_int) == 0);
	assert(crydi::Mod(za, gcd_zz) == 0 && crydi::Mod(zb, gcd_zz) == 0);

	int ix, iy;
	ZZ  zx, zy;
	crydi::EuclidExtendedGcd(ia, ib, gcd_int, ix, iy);
	crydi::EuclidExtendedGcd(za, zb, gcd_zz , zx, zy);
	int bezout_int = (ia*ix) + (ib*iy);
	ZZ  bezout_zz  = (za*zx) + (zb*zy);
	assert(bezout_int == gcd_int);
	assert(bezout_zz  == gcd_zz );

	while (crydi::Gcd(ia,ib) != 1) {
		ia = crydi::RandomInt(2, numeric_limits<int>::max());
		ib = crydi::RandomInt(2, numeric_limits<int>::max());
	}

	while (crydi::Gcd(za,zb) != 1) {
		za = RandomLen_ZZ(1024);
		zb = RandomLen_ZZ(1024);
	}

	int inv_int = crydi::FindModularInverse(ia, ib);
	assert(crydi::Mod(inv_int*ia, ib) == 1);

	ZZ  inv_zz  = crydi::FindModularInverse(za, zb);
	assert(crydi::Mod(inv_zz*za, zb) == 1);

	int exp_int = crydi::RandomInt(2, numeric_limits<int>::max());
	ZZ  exp_zz  = RandomLen_ZZ(512); 
	int mod_exp_int = crydi::ModularExp(ia, exp_int, ib);
	ZZ  mod_exp_zz  = crydi::ModularExp(za, exp_zz , zb);
	ZZ  zz_lib_mod_exp;
	PowerMod(zz_lib_mod_exp, za, exp_zz, zb);
	assert(mod_exp_zz == zz_lib_mod_exp);

	return 0;
}
