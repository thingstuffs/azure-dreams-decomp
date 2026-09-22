#include "common.h"

extern void func_80022F14(void *a, void *b);
extern s32 D_8002765C[];

register u8 *dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

/* Checks the object's guard field, initializes its state, and installs its dispatch table. */
void func_80027684(void *object) {
    register u8 *guard_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    guard_value = (u8 *)(u32)*(s32 *)((s8 *)object + 0x3C);
    if (guard_value != 0) {
        dispatch_result = (u8 *)0x80020000;
        dispatch_result += 0x789C;
        goto install;
    }
    dispatch_result = (u8 *)0x80020000;
    ASM_MEM_BARRIER();
    *(s32 *)((s8 *)object + 0x40) = 1;
    func_80022F14((s8 *)object - 0x20, (s8 *)object + 0x38);
    *(s32 *)((s8 *)object + 0x38) = 1;
    dispatch_result = (u8 *)D_8002765C;
install:
    *(u8 **)((s8 *)object - 0x10) = dispatch_result;
}
