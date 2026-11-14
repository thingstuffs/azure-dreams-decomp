#include "common.h"

#include "engine/object.h"

/* Writes zero through the supplied 32-bit word pointer. */
void clear_word(s32 *value) {
    *value = 0;
}
