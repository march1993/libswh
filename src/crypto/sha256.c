/**
The functionality of this file is described in corresponding `README.md`.
Copyright (C) 2017  https://github.com/march1993

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <swh/crypto/sha256.h>

#define BLOCK_SIZE 64 // 512 bits

static const uint32_t INITIAL_HASH[8] = {

	0x6a09e667UL,
	0xbb67ae85UL,
	0x3c6ef372UL,
	0xa54ff53aUL,
	0x510e527fUL,
	0x9b05688cUL,
	0x1f83d9abUL,
	0x5be0cd19UL,

};

static const uint32_t K[64] = {

	0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
	0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
	0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
	0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
	0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
	0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
	0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
	0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
	0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
	0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
	0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
	0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
	0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
	0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
	0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
	0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL,

};

static inline uint32_t R(const uint32_t x, const size_t n) {

	return x >> n;

}

static inline uint32_t S(const uint32_t x, const size_t n) {

	return (x >> n) | (x << (32 - n));

}

static inline uint32_t sigma0(const uint32_t x) {

	return S(x, 7) ^ S(x, 18) ^ R(x, 3);

}

static inline uint32_t sigma1(const uint32_t x) {

	return S(x, 17) ^ S(x, 19) ^ R(x, 10);

}

static inline uint32_t Sigma0(const uint32_t x) {

	return S(x, 2) ^ S(x, 13) ^ S(x, 22);

}

static inline uint32_t Sigma1(const uint32_t x) {

	return S(x, 6) ^ S(x, 11) ^ S(x, 25);

}

static inline uint32_t Ch(const uint32_t x, const uint32_t y, const uint32_t z) {

	return (x & y) ^ ((~x) & z);

}

static inline uint32_t Maj(const uint32_t x, const uint32_t y, const uint32_t z) {

	return (x & y) ^ (x & z) ^ (y & z);

}


// little, big endian conversion
static void fill_length(size_t n, unsigned char target[8]) {

	uint64_t l = n;
	l = l * 8ULL; // in bits

	target[7] = l % 0x100ULL; l = l >> 8;
	target[6] = l % 0x100ULL; l = l >> 8;
	target[5] = l % 0x100ULL; l = l >> 8;
	target[4] = l % 0x100ULL; l = l >> 8;
	target[3] = l % 0x100ULL; l = l >> 8;
	target[2] = l % 0x100ULL; l = l >> 8;
	target[1] = l % 0x100ULL; l = l >> 8;
	target[0] = l % 0x100ULL; l = l >> 8;

}

static void fill_block(const unsigned char in[64], uint32_t out[16]) {

	for (size_t i = 0; i < 16; i++) {

		uint32_t
			n0 = in[i * 4 + 0],
			n1 = in[i * 4 + 1],
			n2 = in[i * 4 + 2],
			n3 = in[i * 4 + 3];

		out[i] = (n0 << 24) + (n1 << 16) + (n2 << 8) + (n3 << 0);

	}

}

static void fill_hash(const uint32_t in[8], unsigned char output[32]) {

	for (size_t i = 0; i < 8; i++) {

		uint32_t w = in[i];

		output[i * 4 + 3] = w % 0x100ULL; w = w >> 8;
		output[i * 4 + 2] = w % 0x100ULL; w = w >> 8;
		output[i * 4 + 1] = w % 0x100ULL; w = w >> 8;
		output[i * 4 + 0] = w % 0x100ULL; w = w >> 8;

	}


}

static void compression_function(const uint32_t block[16], const uint32_t previous[8], uint32_t output[8]) {

	// prepare W[64]
	uint32_t W[64];
	for (size_t i = 0; i < 16; i++) {

		W[i] = block[i];

	}
	for (size_t i = 16; i < 64; i++) {

		W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i -16];

	}

	memcpy(output, previous, 32);


	uint32_t
		* a = output + 0,
		* b = output + 1,
		* c = output + 2,
		* d = output + 3,
		* e = output + 4,
		* f = output + 5,
		* g = output + 6,
		* h = output + 7;

	// loop j = 0 to 63
	for (size_t j = 0; j < 64; j++) {

		unsigned
			T1 = * h + Sigma1(* e) + Ch(* e, * f, * g) + K[j] + W[j],
			T2 = Sigma0(* a) + Maj(* a, * b, * c);

		* h = * g;
		* g = * f;
		* f = * e;
		* e = * d + T1;
		* d = * c;
		* c = * b;
		* b = * a;
		* a = T1 + T2;

	}

}

static void block_function(const unsigned char input[64], uint32_t result[8]) {

	uint32_t cur_block[16];
	uint32_t next_result[8];

	fill_block(input, cur_block);
	compression_function(cur_block, result, next_result);

	for (size_t j = 0; j < 8; j++) {

		result[j] += next_result[j];

	}

}





void sha256(size_t n, const unsigned char input[n], unsigned char output[32]) {

	/**
	 *	Step.1: padding
	 */
	// pad: 512 bits
	unsigned char
		pad_block0[64] = {0},
		pad_block1[64] = {0};

	size_t n_block = n / BLOCK_SIZE;
	bool need_pad1 = (n % 64) > (64 - 8 - 1);

	for (size_t i = n_block * BLOCK_SIZE; i < n; i++) {

		size_t offset = i - n_block * BLOCK_SIZE;
		pad_block0[offset] = input[i];

	}

	// pad 1
	size_t offset = n - n_block * BLOCK_SIZE;
	pad_block0[offset] = 0x80;


	// pad message length
	unsigned char * target = (need_pad1 ? pad_block1 : pad_block0) + 64 - 8;
	fill_length(n, target);

	/**
	 *	Step.2 iterating
	 */

	// initial hash
	uint32_t result[8];
	memcpy(result, INITIAL_HASH, sizeof(result));

	for (size_t i = 0; i < n_block; i++) {

		block_function(input + i * BLOCK_SIZE, result);

	}

	// pad_block0
	block_function(pad_block0, result);

	// pad_block1
	if (need_pad1) {

		block_function(pad_block1, result);

	}

	fill_hash(result, output);

}