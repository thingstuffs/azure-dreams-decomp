#include "common.h"

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_80099844(void *arg0, void *arg1);
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
