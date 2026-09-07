#include "common.h"

#include "common.h"

extern s32 func_8003C5A4(s32 arg0);
extern s32 D_8006B1A8[];

/* Returns the table value for the lookup key, or zero if no entry is found. */
s32 func_8003C5F0(s32 lookup_key) {
    s32 index = func_8003C5A4(lookup_key);

    if (index < 0) {
        return 0;
    }

    return D_8006B1A8[index];
}
