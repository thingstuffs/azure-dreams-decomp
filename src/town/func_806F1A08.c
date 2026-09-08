#include "common.h"

extern s32 func_800177BC();
extern void *D_80016000;
extern s32 D_80017D64;

s32 func_806F1A08(void) {
    void *ptr;
    register s32 *value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    func_800177BC(0xFE5);
    ptr = D_80016000;
    value = &D_80017D64;
    ptr = *(void **)((s8 *)ptr + 0x1C);
    *(s32 **)((s8 *)ptr + 0x40) = value;
    return 0;
}
