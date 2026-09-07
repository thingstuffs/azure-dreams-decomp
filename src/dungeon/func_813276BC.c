#include "common.h"

extern s32 D_80174704;
extern s32 func_800C07AC(s32);
extern void func_8016EEFC(void) __attribute__((noreturn));

s32 func_8016EEBC(void) {
    s32 result;
    s32 flag;
    void *status;

    status = (void *)(D_80174704 + 0x20);
    result = func_800C07AC(D_80174704);
    *(s32 *)((s8 *)status + 0xA4) = result;
    if (result != 0) {
        result = 1;
        flag = result;
        ASM_KEEP(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        *(s8 *)((s8 *)status + 0xB0) = flag;
        flag = 60;
        *(s8 *)((s8 *)status + 0xB1) = flag;
        func_8016EEFC();
    }
    return 0;
}
