#include "common.h"
#include "m2c_compat.h"

s32 func_80019D44();         /* extern */
M2C_UNK *func_80019DFC(); /* extern */
extern M2C_UNK D_8001B234;
extern M2C_UNK D_8001C358;
extern M2C_UNK D_8001DE4A;

/* Return the lookup result, or the fallback when the override check succeeds. */
M2C_UNK *func_800162F8(s32 key, M2C_UNK unused, M2C_UNK context) {
    M2C_UNK *result;

    result = func_80019DFC(&D_8001B234, &D_8001C358, key, context);
    if (func_80019D44(&D_8001B234, key, context) != 0) {
        result = &D_8001DE4A;
    }
    return result;
}
