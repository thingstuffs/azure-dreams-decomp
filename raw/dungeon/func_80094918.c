#include "common.h"

extern void *D_800E3D7C;
extern s32 D_800E296C;

extern void func_8009A028(void *arg0);

void func_8009A078(void)
{
    void *a0;
    void *v1;
    void *s0;

    a0 = D_800E3D7C;
    do {
        v1 = *(void **)((u8 *)a0 + 0x5C);
        s0 = (u8 *)v1 + 0x20;
        if (!(*(s32 *)((u8 *)a0 + 0x14) & 0x4000)) {
            v1 = (u8 *)a0 - 0x20;
            *(u16 *)((u8 *)v1 + 0x1E) = (u16)(*(u16 *)((u8 *)v1 + 0x1E) | 0x1000);
            func_8009A028(a0);
        }
        a0 = s0;
    } while (a0 != D_800E3D7C);

    D_800E296C = D_800E296C | 0x10000000;
}
