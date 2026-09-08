#include "common.h"

extern void *func_80018044(void *, void *, void *, s32);
extern s32 func_8001894C(s32);

extern u8 D_80018B10[];
extern s32 D_80018E38;
extern u8 D_8001B749[];
extern u8 D_8001BE29[];

/* Returns the entry's generated result or a fallback selected by condition 0x50F. */
void *func_80016774(void *entry, s32 unused, s32 result_arg) {
    if (func_8001894C(*(s16 *)((u8 *)entry + 0x18)) == 0) {
        return func_80018044(D_80018B10, &D_80018E38, entry, result_arg);
    }

    if (func_8001894C(0x50F) != 0) {
        return D_8001BE29;
    }

    return D_8001B749;
}
