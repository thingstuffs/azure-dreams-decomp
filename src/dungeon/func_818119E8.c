#include "common.h"

extern s32 func_80048EE4(void *arg0, s32 arg1);
extern void func_800491CC(s32 arg0, void *arg1, s32 arg2);

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

extern Vec3 D_8002E5E8;

/* Obtains an object handle and initializes its position on success. */
s32 func_800269E8(void *object)
{
    Vec3 *initial_pos;
    s32 handle;
    s32 success = 0;

    handle = func_80048EE4((s8 *)object + 0x74, 4);
    *(s32 *)((s8 *)object + 0x70) = handle;
    if (handle != 0) {
        register s32 call_arg ASM_REG("$4") = handle;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        initial_pos = &D_8002E5E8;
        *(s32 *)((s8 *)object + 0x54) = initial_pos->x;
        *(s32 *)((s8 *)object + 0x58) = initial_pos->y;
        *(s32 *)((s8 *)object + 0x5C) = initial_pos->z;
        func_800491CC(call_arg, (s8 *)object + 0x54, 4);
        success = 1;
    }
    return success;
}
