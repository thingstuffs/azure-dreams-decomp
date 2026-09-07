#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80171A18(void);
extern void func_80171C34(void *, void *, void *, void *);
extern s32 func_8017237C(void *, void *, void *, void *);
extern void func_80172548(void *, void *, void *, void *);
extern s32 func_80172628(void *, void *, void *, s32);
extern void func_80173E00(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_801740E0[];
extern u8 D_801740E8[];
extern u8 D_801740F0[];
extern u8 D_80174140[];
extern u8 D_80174150[];
extern u8 D_80174158[];

void func_801714D4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    register void *p0 ASM_REG("$16") = arg0;
    register void *p1 ASM_REG("$19") = arg1;
    register void *p2 ASM_REG("$17") = arg2;
    register void *p3 ASM_REG("$18") = arg3;
    s16 sp18;
    s32 flags;
    s32 kind;
    s8 tile;
    s16 angle;
    u16 field46;
    void *fifth;
    void *owner;

#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (D_80083462 & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 14;
        func_80171A18();
        return;
    }

    ASM_KEEP(p0);
    ASM_KEEP(p1);
    ASM_KEEP(p2);
    ASM_KEEP(p3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, u8 *, 0x2C) == D_80174158) {
            return;
        }
        FIELD(arg2, u8 *, 0x2C) = D_80174150;
        func_80047784(
            arg2,
            D_80174150[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, u8 *, 0x2C) == D_80174158) {
            FIELD(arg0, u8, 0x9A) = 13;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_801740F0) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg0, u8, 0x9A) != 14) {
            FIELD(arg0, u8, 0x9A) = 14;
        }

        if ((FIELD(arg2, u8 *, 0x2C) != D_801740E0) &&
            (FIELD(arg2, u8 *, 0x2C) != D_801740E8)) {
            FIELD(arg2, u8 *, 0x2C) = D_801740E0;
            func_80047784(
                arg2,
                D_801740E0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg2, u8, 5) = 1;
            FIELD(arg0, s16, 0xA2) = 0;
            FIELD(arg0, s16, 0x9E) = 0;
        }

        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174140) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            FIELD(arg0, u16, 0x92) -= FIELD(arg0, u16, 0xA2);
            FIELD(arg0, s16, 0xA2) = 0;
            FIELD(arg0, s16, 0x9E) = 0;
            func_80173E00(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, s8, 0x26) = tile;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto jt_c12;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }
        field46 = FIELD(arg3, u16, 0x46);
        if ((field46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172628(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            field46 = FIELD(arg3, u16, 0x46) | 0x4000;
            FIELD(arg3, u16, 0x46) = field46;
            if ((field46 & 0x8000) == 0) {
                goto jt_default;
            }
        }

        kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if ((u32)kind >= 12U) {
            goto jt_default;
        }
        (void)jt_keep;
        goto *D_80170808[kind];

jt_c8:
jt_c9:
        if ((s16)func_8017237C(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_80172548(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        angle = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        owner = D_800814A8;
        FIELD(arg3, s16, 0x2A) = angle;
        if (FIELD(owner, u8, 0x9A) == 0x11) {
            goto jt_c1;
        }

jt_c12:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
        fifth = (void *)func_801714D4;

jt_call:
        func_800AAF00(arg0, arg1, arg2, 0, fifth);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_80171C34(arg0, arg1, arg2, arg3);
        return;
    }

    flags = FIELD(arg3, u32, 0x1C);
    if (flags & 0x2000) {
        return;
    }
    if (tile >= 0) {
        if (D_800E2970[tile].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    {
        u8 *origin = D_80082E80;

        if ((s16)func_8009FD7C(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                origin[0x24], origin[0x25]) == 0) {
            return;
        }
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            origin[0x24], origin[0x25], &sp18);
    }
}
