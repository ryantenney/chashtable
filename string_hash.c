/* http://www.cse.yorku.ca/~oz/hash.html */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PER_LOOP (8)

// macro HASH_SDBM is the equivalent of
//   hash(i) = hash(i - 1) * 65599 + str[i];
#define HASH_INIT (0)
#define HASH_SDBM(h) (h << 6) + (h << 16) - h

// macro HASH_DJB2M is the equivalent of
//   hash(i) = hash(i - 1) * 33 + str[i];
//#define HASH_INIT (5381)
//#define HASH_DJB2(h) ((h << 5) + h)

#define HASH_STEP(h, s) h = *s++ + HASH_SDBM(h);

// loop unwound version using a duff device
extern unsigned long string_hash(register unsigned char *s, const size_t l)
{
	register unsigned long h = HASH_INIT;                    // hash
	register unsigned int n = (l + PER_LOOP - 1) / PER_LOOP; // n

	switch (l % PER_LOOP) {
		case 0: do { HASH_STEP(h, s)
		case 7:      HASH_STEP(h, s)
		case 6:      HASH_STEP(h, s)
		case 5:      HASH_STEP(h, s)
		case 4:      HASH_STEP(h, s)
		case 3:      HASH_STEP(h, s)
		case 2:      HASH_STEP(h, s)
		case 1:      HASH_STEP(h, s)
				} while (--n);
	}

	return h;
}
