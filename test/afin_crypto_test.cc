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

#include "../src/inc/crydi3.h"

NTL_CLIENT 

#undef NDEBUG

int main(int argc, char *argv[]) {

#ifndef NDEBUG
	printf("Debugging mode!");
#endif

	crydi::Crypto<long> *afin = new crydi::AfinCrypto<long>;
	afin->SetAlpha("abcdefghijklmnopqrstuvwxyz");
	afin->SetKeys({7,1});

	cout << "AfinCrypto creado con:"
		   << "Llaves: " << afin->GetKeys() << endl;

	string msg {"what"};
	string encrypted {afin->Encrypt(msg)};
	string decrypted {afin->Decrypt(encrypted)};

	cout << "Mensaje: " << msg << endl 
		   << "Encriptado: " << encrypted << endl 
			 << "Desencriptado: " << decrypted << endl;

	crydi::Crypto<ZZ> *afin_zz = new crydi::AfinCrypto<ZZ>;
	afin_zz->SetAlpha("abcdefghijklmnopqrstuvwxyz");
	afin_zz->SetKeys({ZZ(7), ZZ(1)});

	encrypted = afin_zz->Encrypt(msg);
	decrypted = afin_zz->Decrypt(encrypted);

	cout << "Mensaje: " << msg << endl 
		   << "Encriptado: " << encrypted << endl 
			 << "Desencriptado: " << decrypted << endl 
			 << "Desencriptaado del mensaje original:" << afin->Decrypt(msg) << endl;


	return 0;
}
