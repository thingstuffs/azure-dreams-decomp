#include "common.h"
#include "frontend/card.h"

/* Stores a value at the destination address. */
void card_dev_store_word(s32 *dest, s32 value) {
    *dest = value;
}
