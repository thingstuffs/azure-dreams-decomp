#include "common.h"

typedef s32 (*Callback)(s32);

extern void *D_80016000[3];

s32 func_80018A54(void) {
    register s32 *dst;
    s32 value;

    do {
        dst = (s32 *)(*(u8 *volatile *)((u8 *)D_80016000[0] + 0x38) + 0x3188);
    } while (0);
    ASM_KEEP(dst);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    if ((*(Callback *)(*(u8 **)((u8 *)D_80016000[0] + 0x20) + 0x54))(2) & 1) {
        value = 0x15;
    } else {
        value = 0x13;
    }
    do {
        *dst = value;
    } while (0);
    return 1;
}
