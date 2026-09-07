#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_801713D4(void);
extern void func_8017162C(void *, void *, void *, void *);
extern s32 func_80171DD8(void *, void *, void *, void *);
extern void func_80171F9C(void *, void *, void *, void *);
extern s32 func_801720B4(void *, void *, void *, s32);
extern void func_80173AC0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *const D_80170808[];
extern u8 D_80173D0C[];
extern u8 D_80173D14[];
extern u8 D_80173D1C[];
extern u8 D_80173D3C[];
extern u8 D_80173D44[];
extern u8 D_80173D4C[];

void func_80170E5C(void *in0, void *in1, void *in2, void *in3)
{
    register void *arg0 ASM_REG("$19");
    register void *arg1 ASM_REG("$16");
    register void *arg2 ASM_REG("$17");
    register void *arg3 ASM_REG("$18");
    u8 *table;
    s32 result;
    s32 scratch;
    s16 countdown;
    u32 initial_flags = D_80083462;

    arg0 = in0;
    arg1 = in1;
    arg2 = in2;
    arg3 = in3;

    if (initial_flags & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_801713D4();
        return;
    }

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80173D4C) {
            return;
        }
        FIELD(arg2, void *, 0x2C) = D_80173D44;
        func_80047784(arg2,
            D_80173D44[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80173D4C) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80173D44)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            u8 state = 0xE;

            if (FIELD(arg2, void *, 0x2C) != D_80173D0C) {
                register s32 delay_value ASM_REG("$2") = 10;

                ASM_KEEP(delay_value);
                FIELD(arg0, s16, 0xA4) = delay_value;
                FIELD(arg2, void *, 0x2C) = D_80173D14;
                func_80047784(arg2,
                    D_80173D14[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            FIELD(arg0, u8, 0x9A) = state;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80173D1C)) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173AC0(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, u8, 0x26) = result;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto special_cleanup;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(arg3,
                        (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            FIELD(arg3, u16, 0x46) |= 0x4000;
            if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        {
            static void *const sw_keep[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            u32 swi = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;

            if (swi >= 12) {
                goto ordinary_cleanup;
            }
            (void)sw_keep;
            goto *D_80170808[swi];
        }

handler_case:
        if ((s16)func_80171DD8(arg0, arg1, arg2, arg3) == 0) {
            func_80171F9C(arg0, arg1, arg2, arg3);
        }
        return;

coords_case:
        {
            u8 *origin = D_80082E80;
            void *global;
            s32 direction;

            direction = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                &scratch);
            global = D_800814A8;
            FIELD(arg3, s16, 0x2A) = direction;
            if (FIELD(global, u8, 0x9A) == 0x11) {
                goto aaf_cleanup;
            }
        }

special_cleanup:
        func_800A9A0C(arg3);
        return;

aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_80173D3C, func_80170E5C);
        return;

ordinary_cleanup:
        func_8017162C(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(FIELD(arg3, u32, 0x1C) & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(FIELD(arg2, u8, 0x24),
                        FIELD(arg2, u8, 0x25), FIELD(origin, u8, 0x24),
                        FIELD(origin, u8, 0x25)) != 0) {
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                        &scratch);
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
    table = D_80173D0C;
    if (FIELD(arg2, void *, 0x2C) == table) {
        return;
    }
    countdown = FIELD(arg0, u16, 0xA4) - 1;
    FIELD(arg0, s16, 0xA4) = countdown;
    if (countdown > 0) {
        return;
    }
    FIELD(arg0, s16, 0xA4) = -1;

    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(arg2,
        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
}
