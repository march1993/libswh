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

#ifndef SHA256_H
#define SHA256_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


// the maximum data can be hashed depends on the range of `size_t`
// output: 256 bits
extern void sha256(size_t n, const unsigned char input[n], unsigned char output[32]);


#ifdef __cplusplus
}
#endif


#endif // SHA256_H