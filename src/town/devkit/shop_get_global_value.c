#include "common.h"

/* Returns the global value stored at 0x80701FB8. */
s32 read_stored_runtime_word(void) {
    return *(s32 *)0x80701FB8;
}
