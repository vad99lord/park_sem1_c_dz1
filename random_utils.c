#include <stdlib.h>
#include "random_utils.h"


// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
long random_at_most(long max) {
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
            num_bins = (unsigned long) max + 1,
            num_rand = (unsigned long) RAND_MAX + 1,
            bin_size = num_rand / num_bins,
            defect = num_rand % num_bins;

    long x;
    do {
        x = random();
    }
        // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long) x);

    // Truncated division is intentional
    return x / bin_size;
}

//fills int array with random values
long random_at_most_signed(long max) {
    //sign is -1 or 1;
    int sign = -1 + 2 * random_at_most(1);
    return sign * random_at_most(max);
}