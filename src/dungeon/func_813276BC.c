#include "common.h"

extern s32 D_80174704;
extern s32 func_800C07AC(s32);

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
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        *(s8 *)((s8 *)status + 0xB0) = flag;
        flag = 60;
        *(s8 *)((s8 *)status + 0xB1) = flag;
        return;
    }
    return 0;
}
