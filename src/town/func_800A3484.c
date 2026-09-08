#include "common.h"

extern s16 func_800A20D8();
extern s32 D_800A0C30;

/* Update the entity step state and switch handlers when the result is zero. */
void func_800A0BE4(void *entity) {
    s16 step_result;
    s32 uninitialized_arg;

    step_result = func_800A20D8(entity, *(s32 *)((u8 *)entity + 0x98), uninitialized_arg, *(s16 *)((u8 *)entity + 0x90));
    *(s16 *)((u8 *)entity + 0x90) = step_result;
    if ((step_result << 0x10) == 0) {
        *(void **)((u8 *)entity + 0x50) = &D_800A0C30;
    }
}
