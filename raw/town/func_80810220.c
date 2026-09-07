#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))
#define NORETURN

extern s32 func_80252550(void *, void *);
extern void func_8052AEB8(void) NORETURN;
extern void func_8052B030() __attribute__((noreturn));
extern u32 D_80012BCC[4];
extern u8 D_805300C4[0x100];
extern u32 D_80530100[];
__asm__(".set D_80530100, 0x80530100");

void func_80810220(void *arg0, void *arg1, void *arg2) {
    void *child;
    s32 called;
    s16 state;
    u16 flags;

    child = FIELD(arg0, void *, 4);
    called = 0;

    if (FIELD(child, s16, 0x18) == 0) {
        FIELD(arg0, s16, 0) = 0;
    }

    if (D_80012BCC[0] >= 1000U) {
        if (func_80252550(D_805300C4, arg1) != 0) {
            called = 1;
            func_8052AEB8();
        }
        FIELD(arg2, s32, 8) = D_80530100[FIELD(arg0, s16, 0x54) + 3];
    }

    state = FIELD(arg0, s16, 0);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_8052B030();
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_8052B030();
    return;

state_0: {
        s32 value;
        value = FIELD(arg1, s32, 8) - 0x80000;
        FIELD(arg1, s32, 8) = value;
        if (value <= 0) {
            FIELD(arg1, s32, 8) = 0;
            FIELD(arg2, s32, 0xC) = 0x808080;
            FIELD(arg0, s16, 0) = 1;
            func_8052B030();
        }
        goto done;
    }

state_1: {
        register s32 called_v0 ASM_REG("$2");
        called_v0 = called;
        if (called_v0 != 0 && FIELD(FIELD(arg0, void *, 4), s16, 0x22) == 3) {
            FIELD(child, u16, 0x20) |= 1;
            FIELD(arg2, s32, 8) = D_80530100[FIELD(arg0, s16, 0x54) + 6];
            FIELD(child, s16, 0x22) = FIELD(arg0, u16, 0x54);
        }
        if (FIELD(child, s16, 0x22) != 3) {
            if (FIELD(FIELD(arg0, void *, 4), s16, 0x22) ==
                FIELD(arg0, s16, 0x54)) {
                FIELD(arg0, s16, 0) = 3;
                func_8052B030();
                return;
            }
            FIELD(arg0, s16, 0) = 2;
            func_8052B030();
        }
        goto done;
    }

state_2: {
        s32 value;
        value = FIELD(arg1, s32, 8) + 0x80000;
        FIELD(arg1, s32, 8) = value;
        if (value > 0x3FFFFF) {
            FIELD(arg1, s32, 8) = 0x400000;
            func_8052B030();
        }
        goto done;
    }

state_3:
        flags = FIELD(child, u16, 0x20);
        if (flags & 1) {
            FIELD(child, u16, 0x20) = flags | 1;
            FIELD(arg2, s32, 8) = D_80530100[FIELD(arg0, s16, 0x54) + 6];
        }
done:
    return;
}
