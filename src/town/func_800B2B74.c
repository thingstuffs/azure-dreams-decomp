#include "common.h"
#ifndef NULL
#define NULL 0
#endif
extern void *func_800B0214(s32);
extern s32 D_800AFD00[4];

void *func_800B02D4(s32 arg0) {
    void *v0 = func_800B0214(arg0);
    if (v0 != NULL) {
        void *v1 = *(void **)((u8 *)v0 + 0xBC);
        *(void **)((u8 *)v0 + 0x10) = D_800AFD00;
        *(s16 *)((u8 *)v1 + 6) = 0x1000;
    }
    return v0;
}
