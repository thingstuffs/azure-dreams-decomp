#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Triple {
    u32 e[3];
} Triple;

extern Triple D_80526670;
extern Triple D_80526688;
extern u8 D_801328C8[];
extern u8 D_8005860C[];
extern u8 D_8005888C[];
extern u8 D_8052B5A4[];
extern u8 D_8052BAAC[];
extern u8 D_8052BB00[];
extern u8 D_8052BB98[];

extern s32 func_800351A8(s32, s32);
extern void *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);
extern void func_8003F8A8(s32);
extern void func_80050BFC(s32, void *);
extern u32 func_80071494(void);
extern void func_8052B4E8(void) __attribute__((noreturn));

s32 func_808106E0(void)
{
    u8 *anchor = 0;
    Triple positions0 = D_80526670;
    Triple positions1 = D_80526688;
    u8 *object;
    register u8 *part ASM_REG("$18");
    register u8 *selected ASM_REG("$2");
    s32 i;
    s32 y_first;
    register s32 y_second ASM_REG("$20");
    s32 y_third;

    func_80050BFC(0x552, &D_80526688);
    func_8003F8A8(7);
    func_800351A8(0x3E, 0);

    object = func_800374FC(0x136, D_801328C8);
    i = 2;
    if (object != 0) {
        anchor = object + 0x20;
        FIELD(object, void *, 0x10) = D_8052B5A4;
        FIELD(object, s16, 0x2A) = 0x1E;
        FIELD(object, u16, 0x24) = func_80071494() & 3;
        FIELD(object, u16, 0x2C) |= 4;
    }

    y_first = 0xD0;
    do {
        object = func_800374FC(1, D_801328C8);
        if (object != 0) {
            FIELD(object, void *, 0x10) = D_8052BAAC;
            func_8003BC18(object, D_8005860C);
            FIELD(object, u16, 0x36) = 0xB4;
            FIELD(object, u16, 0x38) = 3;
            FIELD(object, u16, 0x3A) = 0x7C80;
            FIELD(object, s16, 0x34) = y_first;
            FIELD(object, u32, 0x30) = 0x00808080;
            FIELD(object, u32, 0x24) = positions0.e[i];
            FIELD(object, void *, 0x2C) = anchor;
        }
        i--;
        y_first -= 0x58;
    } while (i >= 0);

    i = 2;
    y_second = 0xD8;
    do {
        object = func_800374FC(1, D_801328C8);
        if (object != 0) {
            FIELD(object, void *, 0x10) = D_8052BB00;
            func_8003BC18(object, D_8005860C);
            FIELD(object, u16, 0x36) = 0xC4;
            FIELD(object, u16, 0x38) = 3;
            FIELD(object, u16, 0x3A) = 0x7C80;
            FIELD(object, s16, 0x34) = y_second;
            FIELD(object, u32, 0x30) = 0x00808080;
            FIELD(object, u32, 0x24) = positions1.e[i];

            part = object + 0x20;
            if (i != 1) {
                if (i < 2) {
                    selected = anchor + 6;
                    if (i != 0) {
                        ASM_KEEP(part);
                        FIELD(part, void *, 0xC) = anchor;
                        func_8052B4E8();
                    }
                } else {
                    if (i == 2) {
                        selected = anchor + 10;
                    } else {
                        ASM_KEEP(part);
                        FIELD(part, void *, 0xC) = anchor;
                        func_8052B4E8();
                    }
                }
            } else {
                selected = anchor + 8;
            }
            FIELD(object, void *, 0x28) = selected;
            FIELD(part, void *, 0xC) = anchor;
            ASM_KEEP(selected);
            ASM_KEEP(part);
        }
        i--;
        y_second -= 0x58;
    } while (i >= 0);
    ASM_KEEP(y_second);

    i = 2;
    y_third = 0xCC;
    do {
        object = func_800374FC(1, D_801328C8);
        i--;
        if (object != 0) {
            FIELD(object, void *, 0x10) = D_8052BB98;
            func_8003BC18(object, D_8005888C);
            FIELD(object, u16, 0x2E) = 0xB0;
            FIELD(object, u16, 0x30) = 0x50;
            FIELD(object, u16, 0x32) = 0x20;
            FIELD(object, s16, 0x2C) = y_third;
            FIELD(object, u16, 0x34) = 2;
            FIELD(object, u32, 0x28) = 0x00404040;
            FIELD(object, void *, 0x24) = anchor;
            FIELD(object, u16, 0x36) |= 1;
        }
        y_third -= 0x58;
    } while (i >= 0);

    return 0;
}

/* MECHANISM: Declare the held s3 anchor before two independent 12-byte stack locals to match the 0x48 prologue.
   Spell the i == 2 arm in retail CFG order so the dying compare and selected pointer share v0.
   Tied ASM_KEEP at each noreturn use preserves s2+0xC instead of CSE-folding it to s0+0x2C. */
