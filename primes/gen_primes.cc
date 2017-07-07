#include <crydi3/crydi3.h>

int main() {
	crydi::PrimesSieve p(65000);
	p.RegularSieve();
	return 0;
}
