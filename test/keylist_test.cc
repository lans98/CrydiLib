#include "../src/inc/crydi3.h"
#include <cassert>

NTL_CLIENT 

#undef NDEBUG

int main() {
#ifndef NDEBUG
	printf("Debugging mode!");
#endif
	cout << "Creating objects\n";
	crydi::KeyList<int> keylist_int {2,3,1};	
	crydi::KeyList<ZZ> keylist_zz {ZZ(2),ZZ(3),ZZ(4)};
	cout << "Created objects A and B:\n"
		   << keylist_int << ", size = " << keylist_int.Size() << endl
	     << keylist_zz  << ", size = " << keylist_zz.Size()  << endl;

	try {
		keylist_int[2141];
	} catch (const char* error) {
		cout << "Good! Fail at trying to get no real index (" << error << ")\n";	
	}
	
	try {
		keylist_zz[2411];	
	} catch (const char* error) {
		cout << "Good! Fail at trying to get no real index (" << error << ")\n";
	}

	assert(keylist_int.Size() == 3);
	assert(keylist_zz.Size() == 3);

	assert(!keylist_int.IsEmpty());
	assert(!keylist_zz.IsEmpty());

	crydi::KeyList<int> copy_keylist_int {keylist_int};
	crydi::KeyList<ZZ> copy_keylist_zz {keylist_zz};
	cout << "Created copy of A and B:\n"
		   << copy_keylist_int << endl 
			 << copy_keylist_zz  << endl;

	assert(copy_keylist_int.Size() == 2);
	assert(copy_keylist_zz.Size() == 2);

	assert(!copy_keylist_int.IsEmpty());
	assert(!copy_keylist_int.IsEmpty());

	crydi::KeyList<int> sub_keylist_int {keylist_int.Sub(1)};
	crydi::KeyList<ZZ> sub_keylist_zz {keylist_zz.Sub(1)};
	cout << "Created sub-A and sub-B:\n"
		   << sub_keylist_int << endl 
			 << sub_keylist_zz  << endl;

	assert(sub_keylist_int.Size() == 1);
	assert(sub_keylist_int.Size() == 1);

	assert(!sub_keylist_int.IsEmpty());
	assert(!sub_keylist_int.IsEmpty());

	keylist_int.ExpandTo(5);
	keylist_zz.ExpandTo(3);
	keylist_int.SetKeys(4,2,6,7,8);
	keylist_zz.SetKeys(ZZ(4), ZZ(5), ZZ(7));
	cout << "Changed keys for A anb B:\n"
		   << keylist_int << endl 
			 << keylist_zz  << endl;

	assert(keylist_int.Size() == 5);
	assert(keylist_zz.Size() == 3);

	assert(!keylist_int.IsEmpty());
	assert(!keylist_zz.IsEmpty());

	return 0;
}
