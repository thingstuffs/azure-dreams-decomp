#include "common.h"

extern void func_80022F14(void *a, void *b);
extern u8 D_8002765C[];
extern u8 D_8002789C[];

/* Checks the object's guard field, initializes its state, and installs its dispatch table. */
void func_80027684(void *object) {
    void *handler;

    if (*(s32 *)((s8 *)object + 0x3C) != 0) {
        handler = D_8002789C;
    } else {
        *(s32 *)((s8 *)object + 0x40) = 1;
        func_80022F14((s8 *)object - 0x20, (s8 *)object + 0x38);
        *(s32 *)((s8 *)object + 0x38) = 1;
        handler = D_8002765C;
    }
    *(void **)((s8 *)object - 0x10) = handler;
}
