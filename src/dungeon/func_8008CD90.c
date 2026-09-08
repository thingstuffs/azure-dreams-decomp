#include "common.h"

extern void *D_8008ACDC[];
extern void *D_8008EAC8[];
extern u32 D_8008346C[];
extern void func_80092534(void *arg0, void *arg1);
extern s32 func_800A1C58(void *arg0, void *arg1);

void func_800924F0(void *arg0, void *arg1, void *arg2, void *arg3) {
    if (!(*(s32 *)((u8 *)arg3 + 0x1C) & 0x100000)) {
        if (*(u16 *)((u8 *)arg2 + 0x14) & 0xE000) {
            void *dead;
            dead = D_8008ACDC;
            ASM_TAILSLOT_PIN(dead);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80092534(arg3, arg0);
            return;
        }
        return;
    }

    *(void **)((u8 *)arg0 + 0x8C) = D_8008EAC8;
    if ((func_800A1C58(arg3, arg0) << 16) == 0) {
        D_8008346C[0] = 0;
    }
}
