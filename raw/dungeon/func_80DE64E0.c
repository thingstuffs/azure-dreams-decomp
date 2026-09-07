#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((s8 *)(obj) + (offset)))

extern void func_800A2B04(s32, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174084(void *, s32, void *);
extern void func_801744B8(void *);
extern s32 D_8008346C;
extern s32 D_80170E5C;

void func_80173CE0(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 state;
    u16 flags;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto end;
    }
    if (state == 2) {
        goto state_two;
    }
    goto end;

state_zero:
    flags = FIELD(arg2, u16, 0x14);
    if (flags & 0x8000) {
        FIELD(arg2, u16, 0x14) = flags | 0x6000;
        FIELD(arg0, u8, 0x9B) = 2;
        goto end;
    }
    FIELD(arg0, u8, 0x9B) = 1;

state_one:
    if ((FIELD(arg2, s8, 4) == 8) &&
        (FIELD(arg2, u16, 0x14) & 0x1000)) {
        goto run_one;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
run_one:
    func_801744B8(arg3);
    func_800A56E0(0x80C);
    func_80174084(arg0, arg1, arg2);
    FIELD(arg0, u8, 0x9B)++;
    goto end;

state_two:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x400);
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg0, s32 *, 0x8C) = &D_80170E5C;
        D_8008346C = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }

end:
    return;
}

/* MECHANISM: Recover every 0x80173E28 transfer as a local epilogue edge, not a call.
   Keep retail state-block order and four long-lived argument roles in the 0x28 frame.
   2.7.2-cdk-G0 fills the state-two guard slot with move a0,s2, removing 2.8.1's nop. */
