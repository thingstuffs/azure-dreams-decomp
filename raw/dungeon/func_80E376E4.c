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

extern void func_80171278(void) __attribute__((noreturn));
extern void func_80171408(void) __attribute__((noreturn));
extern void func_8017143C(void) __attribute__((noreturn));
extern void func_80171460(void);
extern void func_801716A4(void *, void *, void *, void *);
extern s32 func_80171E38(void *, void *, void *, void *);
extern void func_80171FFC(void *, void *, void *, void *);
extern s32 func_80172114(void *, void *, void *, s32);
extern void func_801737B8(void *, void *, void *, void *);
extern void func_80173C40(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170EE4[];
extern u8 D_801765D8[];
extern u8 D_801765E0[];
extern u8 D_80176650[];
extern u8 D_80176660[];
extern u8 D_80176678[];

void func_80170EE4(void *arg0_, void *arg1_, void *arg2_, void *arg3_)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    register void *arg0 ASM_REG("$17") = arg0_;
    register void *arg1 ASM_REG("$19") = arg1_;
    register void *arg2 ASM_REG("$16") = arg2_;
    register void *arg3 ASM_REG("$18") = arg3_;
    u32 initial_flags = D_80083462;
    s16 sp18;
    s32 flags;
    s32 kind;
    s8 tile;
    s16 result;
    u16 field46;
    u8 *table;
    void *origin;
    void *actor;

    if (initial_flags & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 14;
        func_80171460();
        func_8017143C();
    }

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, u8 *, 0x2C) == D_80176650) {
            return;
        }
        {
            register void *state ASM_REG("$5");
            state = D_80176678;
            ASM_TAILSLOT_PIN(state);
            func_80171408();
        }
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, u8 *, 0x2C) == D_80176650) {
            FIELD(arg0, u8, 0x9A) = 13;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_8017143C();
        }
        if (func_800AA924(arg0, arg1, arg2, D_80176678) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_8017143C();
        }

        ASM_KEEP(arg0);
        {
            u8 current_state = 14;
            if (FIELD(arg0, u8, 0x9A) != current_state) {
                if (FIELD(arg2, u8 *, 0x2C) != D_801765D8) {
                    FIELD(arg2, u8 *, 0x2C) = D_801765D8;
                    func_80047784(
                        arg2,
                        D_801765D8[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                FIELD(arg0, u8, 0x9A) = current_state;
            }
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_801765E0) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_801737B8(arg0, arg1, arg2, arg3);
            func_8017143C();
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
            if ((s16)func_80172114(arg0, arg1, arg2, 0) == 0) {
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

jt_c9:
        if ((s16)func_80171E38(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        {
            register void *tail_a0 ASM_REG("$4") = arg0;
            register void *tail_a1 ASM_REG("$5") = arg1;
            ASM_KEEP(tail_a0);
            ASM_TAILSLOT_PIN(tail_a1);
            func_80171278();
        }

jt_c8:
        if (!(FIELD(arg3, u32, 0x14) & 0x20000000)) {
            func_80173C40(arg0, arg1, arg2, arg3);
            func_8017143C();
        }
        func_80171FFC(arg0, arg1, arg2, arg3);
        func_8017143C();

jt_c5:
jt_c6:
jt_c7:
        result = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        actor = D_800814A8;
        FIELD(arg3, s16, 0x2A) = result;
        if (FIELD(actor, u8, 0x9A) == 0x11) {
            goto jt_call;
        }

jt_c12:
        func_800A9A0C(arg3);
        func_8017143C();

jt_c1:
jt_c2:
jt_c3:
jt_call:
        func_800AAF00(arg0, arg1, arg2, D_80176660, D_80170EE4);
        func_8017143C();

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_801716A4(arg0, arg1, arg2, arg3);
        func_8017143C();
    }

    flags = FIELD(arg3, u32, 0x1C);
    if (!(flags & 0x2000)) {
        if ((tile < 0) ||
            !(((DungeonRecord *)D_800E2970)[tile].flags & 2)) {
            if (!(flags & 0x430)) {
                origin = D_80082E80;
                if ((s16)func_8009FD7C(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25)) != 0) {
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25), &sp18);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (FIELD(arg2, u16, 0x14) & 0x40) {
        return;
    }
    table = D_801765D8;
    if (FIELD(arg2, u8 *, 0x2C) == table) {
        return;
    }
    ASM_KEEP(arg2);
    FIELD(arg2, u8 *, 0x2C) = table;
    func_80047784(
        arg2,
        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
}
