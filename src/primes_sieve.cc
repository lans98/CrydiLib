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

#include "inc/primes_sieve.h"

namespace crydi {

PrimesSieve::PrimesSieve(uintmax_t limit, bool printit):
    limit(limit) {
			if (printit) {
				flags |= PRINT_IT;
				file_out = new ofstream("primes.dat");
			}
		}

void PrimesSieve::RegularSieve() {
	uintmax_t sqrt_limit = static_cast<uintmax_t>(sqrt(limit));
	// Borremos el barray si es que flags esta con SEG_SIEVE
	// Por defecto el BitArray usa como tipo de contenedor el tipo
	// char, y -1 represetado como bits es 11111111 (todo true)
	if (flags & SEG_SIEVE) delete[] barray;
	barray = new BitArray<>(limit + 1, -1);

	// Solo se recorre hasta sqrt(n) ya que no habra ningun 
	// multiplo mayor de sqrt(n) que filtrar en la criba
	for (uintmax_t i = 2; i <= sqrt_limit; ++i) {
		// Si fue marcado como compuesto vamos a la siguiente iteración
		if (!barray->At(i)) continue;
		// Si es primo marquemos todos los multiplos de i que caben 
		// en la criba.
		for (uintmax_t j = i * i; j <= limit; j += i) {
			barray->Set(j, 0);
		}
	}

	// Cambia las banderas, quitamos que fue hecha con el metodo de criba
	// segmentada, y configuramos las flags para saber que fue hecho con 
	// el metodo de criba regular
	flags &= ~SEG_SIEVE;
	flags |=  REG_SIEVE;

	// Si es que la criba fue creada para imprimir los números (default)
	// Recorremos el array imprimimos y contamos cuantos primos hay.
	if (!(flags & PRINT_IT)) return;
	for (uintmax_t i = 2; i <= limit; ++i) {
		if (!barray->At(i)) continue;
		(*file_out) << i << " ";
	}
}

void PrimesSieve::SegmentedSieve() {
	uintmax_t sqrt_limit = static_cast<uintmax_t>(sqrt(limit));
	uintmax_t segment_size = sqrt_limit;
	
	if (flags & REG_SIEVE) delete barray;
	barray = new BitArray<>[2]{
		// BitArray que contendra los primos más pequeños menores
		// que sqrt(n), acceder con 0
		BitArray<>(sqrt_limit + 1, -1),

		// BitArray representado un segmento de criba de tamaño de 
		// segment_size, usado multiples veces durante todo el 
		// proceso (osea no se crean más segmento, este es utilizado
		// siempre).
		BitArray<>(segment_size, -1),
	};


	barray[PRIMES] = BitArray<>(sqrt_limit + 1, -1);

	for (uintmax_t i = 2; i * i <= sqrt_limit; ++i) {
		if (!barray[PRIMES].At(i)) continue;
		for (uintmax_t j = i * i; j <= sqrt_limit; j += i) {
			barray[PRIMES].Set(j, 0);
		}
	}

	for (uintmax_t low = 0; low <= limit; low += segment_size) {
	
	}
}

}
