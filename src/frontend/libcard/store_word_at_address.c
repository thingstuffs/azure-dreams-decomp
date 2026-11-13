#include "common.h"
#include "frontend/libcard.h"

/* Stores a value at the destination address. */
void store_word_at_address(s32 *dest, s32 value) {
    *dest = value;
}
