#include "common.h"

extern s32 func_80042900(void *entry, s32 effect_id);
extern void func_80042B68(void *object, s32 value);
extern void func_80099844(void *object, void *value);
extern s8 D_800E0DF5[];

/* Handle a nonzero type 2 query result and always return success. */
s32 func_800B6228(void *object) {
    if ((func_80042900(object, 2) << 16) != 0) {
        func_80042B68(object, 2);
        func_80099844(object, D_800E0DF5);
        return 1;
    }
    return 1;
}
