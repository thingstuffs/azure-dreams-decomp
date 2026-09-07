#include "common.h"

extern s32 func_80047FD8(void *arg0);
extern void func_804033EC(void *arg0);
extern s32 D_8008DAB4[3];
extern s32 D_8008DAB4_2[3];
__asm__(".set D_8008DAB4, 0x8008DAB4");
__asm__(".set D_8008DAB4_2, 0x8008DAB4");
extern u8 D_80409508[];

s32 func_8001C43C(s32 arg0) {
    void *temp_v1;
    u8 *sub = D_80409508 + 0x20;

    if (func_80047FD8(sub - 0x20) != 0) {
        if (arg0 != 0) {
            temp_v1 = *(void **)(sub + 0x14);
            *(u16 *)((u8 *)temp_v1 + 0x1E) = (u16) (*(u16 *)((u8 *)temp_v1 + 0x1E) | 0x2000);
        }
        func_804033EC(sub);
        *(u16 *)(sub - 2) = (u16) (*(u16 *)(sub - 2) | 0x8000);
        D_8008DAB4_2[0] = D_8008DAB4[0] | 0x8000;
    }
    return *(s32 *)sub;
}
