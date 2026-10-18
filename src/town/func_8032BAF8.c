#include "common.h"
#include "m2c_compat.h"

s32 resolve_entry_flag();         /* extern */
s32 apply_entry_position(); /* extern */
extern M2C_UNK D_8001B234;
extern M2C_UNK D_8001C358;
extern M2C_UNK D_8001DE4A;

/* Return the lookup result, or the fallback when the override check succeeds. */
M2C_UNK *lookup_with_override_fallback(s32 key, s32 unused, s32 context) {
    M2C_UNK *result;

    result = apply_entry_position(&D_8001B234, &D_8001C358, key, context);
    if (resolve_entry_flag(&D_8001B234, key, context) != 0) {
        result = &D_8001DE4A;
    }
    return result;
}
