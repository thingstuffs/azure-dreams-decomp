#include "common.h"

extern void func_70088BD0(void);
extern volatile struct { s32 v; s32 pad[2]; } D_800814A0;

void func_7FDD1970(void *arg0) {
    if (*(u16 *)((s8 *)arg0 - 2) & 0x2000) {
        func_70088BD0();
        *(u16 *)((s8 *)arg0 - 2) = *(u16 *)((s8 *)arg0 - 2) | 0x8000;
        D_800814A0.v = D_800814A0.v | 0x8000;
    }
}
