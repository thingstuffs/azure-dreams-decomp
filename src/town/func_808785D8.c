#include "common.h"

/* Returns the global value stored at 0x80701FB8. */
s32 shop_get_global_value(void) {
    return *(s32 *)0x80701FB8;
}
