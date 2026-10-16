#include "common.h"
#include "m2c_compat.h"

s32 townResolveEntryFlag();         /* extern */
s32 townApplyEntryPosition(); /* extern */
extern M2C_UNK D_8001B234;
extern M2C_UNK D_8001C358;
extern M2C_UNK D_8001DE4A;

/* Return the lookup result, or the fallback when the override check succeeds. */
M2C_UNK *townLookupWithOverrideFallback(s32 key, s32 unused, s32 context) {
    M2C_UNK *result;

    result = townApplyEntryPosition(&D_8001B234, &D_8001C358, key, context);
    if (townResolveEntryFlag(&D_8001B234, key, context) != 0) {
        result = &D_8001DE4A;
    }
    return result;
}
