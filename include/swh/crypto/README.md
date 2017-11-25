# 1. sha256.h
Implementation of sha256 hash algorithm. see [sha256-384-512.pdf](http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf)


## depends
No depends.

## model
No model.

## functions

* sha256
   ```C
   void sha256(size_t n, const unsigned char input[n], unsigned char output[32]);
   ```
   Calculate the sha256 hash of input which is n-bytes long .

