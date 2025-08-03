#pragma once

#include <stdint.h>

typedef void (*seed_func)(void*, uint64_t, uint64_t);
typedef uint32_t (*rand_func)(void*);
