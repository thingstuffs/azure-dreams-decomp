#include "common.h"

extern s32 func_80042900(void *entry, s32 effect_id);
extern void func_80042B68(void *object, s32 value);
extern void dungeonAdjustSourceValueAndFinalize(void *object, void *value);
extern s8 D_800E0DF5[];

/* Handle a nonzero type 2 query result and always return success. */
s32 dungeonHandleTypeTwoQueryResult(void *object) {
    if ((func_80042900(object, 2) << 16) != 0) {
        func_80042B68(object, 2);
        dungeonAdjustSourceValueAndFinalize(object, D_800E0DF5);
        return 1;
    }
    return 1;
}
