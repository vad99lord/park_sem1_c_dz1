#ifndef PARK_SEM1_C_DZ1_RANDOM_UTILS_H
#define PARK_SEM1_C_DZ1_RANDOM_UTILS_H



// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
long random_at_most(long max);

// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [-max, max]
long random_at_most_signed(long max);


#endif //PARK_SEM1_C_DZ1_RANDOM_UTILS_H
