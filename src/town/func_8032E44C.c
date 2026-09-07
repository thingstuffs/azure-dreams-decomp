#include "common.h"

typedef s32 (*Callback)(void *);

extern s8 D_80016000[];

s32 func_80018C4C(void *arg0, s32 arg1) {
    register s32 total ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    Callback callback;

    total = 0;
    while (((u8 *)arg0)[1] != 0) {
        if (((u8 *)arg0)[3] & 0x20) {
            if (arg1 == 0) {
                void *object;

                object = *(void **)D_80016000;
                object = *(void **)((u8 *)object + 0x20);
                callback = *(Callback *)((u8 *)object + 0x50);
            } else {
                void *object;

                object = *(void **)D_80016000;
                object = *(void **)((u8 *)object + 0x20);
                callback = *(Callback *)((u8 *)object + 0x6C);
            }
            total += callback(arg0);
        }
        arg0 += 4;
    }
    return total;
}
