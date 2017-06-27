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
	crydi::Crypto<long> *cesar = new crydi::CesarCrypto<long>;
	cesar->SetAlpha("abcdefghijklmnopqrstuvwxyz");
	cesar->SetKeys({3});

	cout << "CesarCrypto creado:"
		   << "Llaves: " << cesar->GetKeys() << endl;

	string msg {"hola"};
	string encrypted {cesar->Encrypt(msg)};
	string decrypted {cesar->Decrypt(encrypted)};

	cout << "Mensaje: " << msg << endl 
		   << "Encriptado: " << encrypted << endl 
			 << "Desencriptado: " << decrypted << endl;


	crydi::Crypto<ZZ> *cesar_zz = new crydi::CesarCrypto<ZZ>;
	cesar_zz->SetAlpha("abcdefghijklmnopqrstuvwxyz");
	cesar_zz->SetKeys({ZZ(3)});

	encrypted = cesar_zz->Encrypt(msg);
	decrypted = cesar_zz->Decrypt(encrypted);

	cout << "Mensaje: " << msg << endl 
		   << "Encriptado: " << encrypted << endl 
			 << "Desencriptado: " << decrypted << endl;

	return 0;
}
