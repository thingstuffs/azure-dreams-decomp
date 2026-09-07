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
extern s16 func_800A0818();
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_801713B0(void) __attribute__((noreturn));
extern void func_801713D4(void *);
extern void func_8017162C(void *, void *, void *, void *);
extern s32 func_80171DD8(void *, void *, void *, void *);
extern void func_80171F9C(void *, void *, void *, void *);
extern s32 func_801720B4(void *, void *, void *, s32);
extern void func_80173D64(void *, void *, void *, void *);
extern void func_8017526C(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170E70[];
extern u8 D_80175A54[];
extern u8 D_80175A5C[];
extern u8 D_80175A8C[];
extern u8 D_80175A94[];
extern u8 D_80175A9C[];

void func_80170E70(void *in0, void *in1, void *in2, void *in3)
{
    u8 *effect_tbl;
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    register void *arg0 ASM_REG("$17") = in0;
    register void *arg1 ASM_REG("$19") = in1;
    register void *arg2 ASM_REG("$16") = in2;
    register void *arg3 ASM_REG("$18") = in3;
    register s32 state ASM_REG("$20");
    register u32 origin_page ASM_REG("$2");
#ifdef __mips__
    register u8 *stack_base ASM_REG("$29");
#endif
    s16 sp18;
    s16 path_result;
    s32 flags;
    s32 kind;
    s8 tile;
    s32 late_a0;
    s32 late_a1;
    s32 current_state;
    u16 field46;
    void *fifth;
    void *owner;

    if (D_80083462 & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 14;
        func_801713D4(arg0);
        func_801713B0();
    }

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80175A9C) {
            return;
        }
        {
            u8 *et = D_80175A94;
            FIELD(arg2, void *, 0x2C) = et;
            func_80047784(
                arg2,
                et[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80175A9C) {
            FIELD(arg0, u8, 0x9A) = 13;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_801713B0();
        }
        if (func_800AA924(arg0, arg1, arg2, D_80175A94) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_801713B0();
        }

        current_state = FIELD(arg0, u8, 0x9A);
        ASM_KEEP(current_state);
        state = 14;
        if (current_state != state) {
            u8 *effect = D_80175A54;

            if (FIELD(arg2, void *, 0x2C) != effect) {
                FIELD(arg2, void *, 0x2C) = effect;
                func_80047784(
                    arg2,
                    effect[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            FIELD(arg0, u8, 0x9A) = state;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175A5C) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173D64(arg0, arg1, arg2, arg3);
            func_801713B0();
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            if ((s16)func_800AAB10(arg0, arg1, arg2, arg3) != 0) {
                func_8017526C(arg0, arg1, arg2, arg3);
            }
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
            if ((s16)func_801720B4(arg0, arg1, arg2, 0) == 0) {
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
        if ((s16)func_80171DD8(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_80171F9C(arg0, arg1, arg2, arg3);
        func_801713B0();

jt_c5:
jt_c6:
jt_c7:
        path_result = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        owner = D_800814A8;
        FIELD(arg3, s16, 0x2A) = path_result;
        if (FIELD(owner, u8, 0x9A) == 0x11) {
            fifth = D_80170E70;
            goto jt_call;
        }

jt_c12:
        func_800A9A0C(arg3);
        func_801713B0();

jt_c1:
jt_c2:
jt_c3:
        fifth = D_80170E70;

jt_call:
        func_800AAF00(arg0, arg1, arg2, D_80175A8C, fifth);
        func_801713B0();

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_8017162C(arg0, arg1, arg2, arg3);
        func_801713B0();
    }

    flags = FIELD(arg3, u32, 0x1C);
    if ((flags & 0x2000) == 0) {
        if ((tile < 0) ||
            ((((DungeonRecord *)D_800E2970)[tile].flags & 2) == 0)) {
            if ((flags & 0x430) == 0) {
                origin_page = 0x80080000;
                ASM_KEEP(origin_page);
                arg0 = (void *)(origin_page + 0x2E80);
                if ((s16)func_8009FD7C(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(arg0, u8, 0x24), FIELD(arg0, u8, 0x25)) != 0) {
#ifdef __mips__
                    late_a0 = FIELD(arg2, u8, 0x24);
                    late_a1 = FIELD(arg2, u8, 0x25);
                    FIELD(stack_base, s16 *, 0x10) = &sp18;
                    ASM_KEEP(stack_base);
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        late_a0, late_a1,
                        FIELD(arg0, u8, 0x24), FIELD(arg0, u8, 0x25));
#else
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(arg0, u8, 0x24), FIELD(arg0, u8, 0x25), &sp18);
#endif
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
    effect_tbl = D_80175A54;
    if (FIELD(arg2, void *, 0x2C) == effect_tbl) {
        return;
    }
    ASM_KEEP(arg2);
    {
        u8 *et = effect_tbl;
        FIELD(arg2, void *, 0x2C) = et;
        func_80047784(
            arg2,
            et[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
}
