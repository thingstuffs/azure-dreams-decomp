#include "common.h"

typedef s32 (*func_80018760_fn)(void *);

extern s8 D_80016000[];
extern s32 D_8001BE60;

s32 func_80018760(void) {
    register void *temp_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *temp_v0_2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    func_80018760_fn temp_v0_fn;
    u32 temp_v0_3;
    void *temp_v1;
    void *temp_a1;
    u32 temp_a0;

    temp_v0 = *(void **)D_80016000;
    temp_v0_2 = *(void **)((s8 *)temp_v0 + 0x20);
    temp_v0_fn = *(func_80018760_fn *)((s8 *)temp_v0_2 + 0x50);
    temp_v0_3 = (u32) temp_v0_fn(&D_8001BE60);

    temp_v1 = *(void **)D_80016000;
    temp_a1 = *(void **)((s8 *)temp_v1 + 0x38);
    temp_a0 = *(u32 *)((s8 *)temp_a1 + 0x2D5C);

    if (temp_a0 >= temp_v0_3) {
        *(u32 *)((s8 *)temp_a1 + 0x2D5C) = temp_a0 - temp_v0_3;
        return 1;
    }
    return 0;
}
