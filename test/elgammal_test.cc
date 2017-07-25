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

#include "crydi3.h"

using namespace std;
using namespace NTL;

int main() {
  crydi::KeyList<ZZ> keys = crydi::GenElgammalKeys(1024);
  string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()!.,-’ ";
  crydi::ElGammalCrypto<ZZ> elgammal(alpha, keys);
  cout << "Public key 1 (share this): " << elgammal.GetFirstPublicKey() << endl;
  cout << "Public key 2 (share this): " << elgammal.GetSecondPublicKey() << endl;
  cout << "Share them with: " << elgammal.GetModulus() << endl;
  cout << "Private key (never share this): " << elgammal.GetPrivateKey() << endl;
  string msg = "Hello! My name is Ana. I am twenty-five years old. I live in Miami, Florida with my husband and two children. I have one son in kindergarten and one daughter in first grade. They both attend public school. My husband is a mechanic. On weekends, he works at a restaurant as a dishwasher. The restaurant usually gets more customers on weekends, so they need extra people to wash dishes. It is Rodrigo’s turn to speak. He is nervous. He doesn’t want to be here but he has no choice. He has lost his job, his home, his family and most of his friends. He takes a deep breath, gets up and walks to the podium at the front of the room. He adjusts the microphone and looks at the group of people in front of him. They begin to clap and shout words of encouragement. Rodrigo takes deep breaths to relax and grips the sides of the podium to stop his hands from shaking. When the clapping stops he summons up his courage and speaks.I have a brother and a sister. My brother is 17 and is in his last year of High School. He loves sports and going to parties. He never takes me to any parties but sometimes he takes my sister and me to the beach. My sister’s name is Jane. She is 11. She loves reading and playing soccer. She reads one or two books every week and watches every soccer game on TV. She gets into trouble at school all the time because she doesn’t do her homework. She pretends to pay attention in class but reads her books under the desk. My parents sometimes make my brother help her with her homework. Very often he just does her homework for her so that he can go out with his girlfriend.";

  printf("Mensaje inicial: %s\n", msg.c_str());

  msg = elgammal.Encrypt(crydi::MsgToNumForm(msg, alpha));
  printf("Mensaje encriptado: %s\n", msg.c_str());

  msg = elgammal.Decrypt(msg);
  printf("Mensaje desencriptado: %s\n", msg.c_str());

  msg = crydi::NumFormToMsg(msg, alpha);
  printf("Final: %s\n", msg.c_str());

  return 0;
}
