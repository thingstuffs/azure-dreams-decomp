#include "common.h"

extern void func_800276d0(void) __attribute__((noreturn));
extern void func_80022F14(void *a, void *b);
extern s32 D_8002765C[];

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

/* Checks the object's guard field, initializes its state, and installs its dispatch table. */
void func_80027684(void *object) {
#ifndef NON_MATCHING
    register u8 *guard_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    guard_value = (u8 *)(u32)*(s32 *)((s8 *)object + 0x3C);
    if (guard_value != 0) {
        dispatch_result = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result += 0x789C;
        func_800276d0();
    }
    dispatch_result = (u8 *)0x80020000;
    __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
#else
    if (*(s32 *)((s8 *)object + 0x3C) != 0) {
        func_800276d0();
    }
#endif
    __asm__ __volatile__("" ::: "memory");
    *(s32 *)((s8 *)object + 0x40) = 1;
    func_80022F14((s8 *)object - 0x20, (s8 *)object + 0x38);
    *(s32 *)((s8 *)object + 0x38) = 1;
#ifndef NON_MATCHING
    dispatch_result = (u8 *)D_8002765C;
    *(u8 **)((s8 *)object - 0x10) = dispatch_result;
#else
    *(s32 **)((s8 *)object - 0x10) = D_8002765C;
#endif
}
