#include "common.h"

#include "common.h"
#include "engine/object.h"

/* Writes zero through the supplied 32-bit word pointer. */
void runtime_clear_value(s32 *value) {
    *value = 0;
}
