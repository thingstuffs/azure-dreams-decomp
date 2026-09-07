#include "common.h"

extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_80404DBC(s32 arg0);
extern void func_804077D4(s32 arg0);

extern u8 D_8040086C[];
extern u8 D_80400894[];
extern s32 D_8008DAB4[3];
extern s32 D_8008DAB0[4];

void func_802F14DC(void *arg0) {
    u16 temp_v0;
    s32 temp_v1;

    if (arg0 == 0) {
        func_8007C040(D_8040086C, D_80400894, 0x183);
        func_8007BEF0(1);
    }

    func_80404DBC(*(s32 *)((u8 *)arg0 + 0x40));
    func_804077D4(*(s32 *)((u8 *)arg0 + 0x44));

    temp_v0 = *(u16 *)((u8 *)arg0 + 0x1E);
    temp_v1 = D_8008DAB4[0];
    temp_v0 |= 0x8000;
    temp_v1 |= 0x8000;
    *(u16 *)((u8 *)arg0 + 0x1E) = temp_v0;
    D_8008DAB0[1] = temp_v1;
}
