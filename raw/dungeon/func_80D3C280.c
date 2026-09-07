#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_800D6068(void *, void *, void *, void *);
extern void func_801708B8(void *, void *, void *);
extern void func_801717D0(void *, void *, void *, void *, void *);
extern void func_80171C9C(void) __attribute__((noreturn));
extern void func_80172050() __attribute__((noreturn));
extern void func_80172144(void);
extern void func_801723F8(void *, void *, void *, void *);
extern s32 func_80172BB0(void *, void *, void *, void *);
extern void func_80172D88(void *, void *, void *, void *);
extern s32 func_80172EA8(void *, void *, void *, s32);
extern void func_80174A68(void *, void *, void *, void *);
extern void func_801754AC(void *, void *, void *, void *);
extern void func_80175F44(void *, void *, void *, s32, s32);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E23E0[];
extern u8 D_800E23F8[];
extern u8 D_800E2418[];
extern u8 D_800E2420[];
extern u8 D_800E2428[];
extern s8 D_800E2970[];
extern void *D_80170820[];
extern u8 D_80171A80[];
extern void *D_800E3D7C[];

void func_80171A80(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 scratch;
    s8 result;
    u16 state;

    if (D_80083462 & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80172144();
        return;
    }

    if (FIELD(arg3, u8, 0x25) == 0) {
        if (FIELD(arg0, u8, 0xB5) == 0) {
            void *table;

            func_800AA79C(arg0, arg1, arg2, arg3);
            if (FIELD(arg2, void *, 0x2C) == D_800E2428) {
                return;
            }
            table = D_800E2420;
            FIELD(arg2, void *, 0x2C) = table;
            func_80047784(arg2,
                ((u8 *)table)[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        } else {
            func_80175F44(arg0, arg1, arg2, 0, 0);
            return;
        }
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_800E2428) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_800E2420) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg0, volatile u8, 0x9A) != 0xE) {
            FIELD(arg0, volatile u8, 0x9A) = 0xE;
        }
        if (FIELD(arg0, u8, 0xB5) == 0) {
            void *table = D_800E23E0;

            if (FIELD(arg2, void *, 0x2C) != table) {
                FIELD(arg2, void *, 0x2C) = table;
                func_80047784(arg2,
                    ((u8 *)table)[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
                FIELD(arg2, u8, 5) = 1;
                (void)FIELD(arg0, volatile u8, 0xB0);
                FIELD(arg0, s16, 0x9E) = 0;
                FIELD(arg0, s16, 0xA2) = 0;
                func_80171C9C();
                return;
            }
            if (FIELD(arg0, u8, 0xB0) == 0) {
                func_801708B8(arg0, arg1, arg2);
            }
            if (FIELD(arg0, u8, 0xB5) == 0) {
                FIELD(arg3, u32, 0x1C) |= 0x40000;
                FIELD(arg0, u16, 0x98) &= 0xFFF7;
            }
        }

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_800E23F8) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            s16 delta;

            func_800AA888(arg0, arg1, arg2, arg3);
            delta = FIELD(arg0, u16, 0x92) - FIELD(arg0, u16, 0xA2);
            FIELD(arg0, s16, 0xA2) = 0;
            FIELD(arg0, s16, 0x9E) = 0;
            FIELD(arg0, s16, 0x92) = delta;
            func_80174A68(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, u8, 0x26) = result;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto jt_c12;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172EA8(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = FIELD(arg3, u16, 0x46) | 0x4000;
            FIELD(arg3, u16, 0x46) = state;
            if (!(state & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        state = FIELD(arg3, u16, 0x46) & 0x3FFF;
        if ((u32)(state - 1) >= 12) {
            goto ordinary_cleanup;
        }
        (void)jt_keep;
        goto *D_80170820[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80172BB0(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172D88(arg0, arg1, arg2, arg3);
        return;

jt_c1:
        if (FIELD(arg0, u8, 0xB5) == 0) {
            func_801754AC(arg0, arg1, arg2, arg3);
            return;
        }
        ((s32 *)__builtin_alloca(0))[-2] = 0;
        func_80172050();
        return;

jt_c2:
        if (FIELD(arg0, u8, 0xB5) == 0) {
            func_800D6068(arg0, arg1, arg2, arg3);
            return;
        }
        ((s32 *)__builtin_alloca(0))[-2] = 0;
        func_80172050();
        return;

jt_c5:
jt_c6:
jt_c7:
        if (FIELD(arg0, u8, 0xB5) == 0) {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                &scratch);
            player = D_800814A8;
            FIELD(arg3, s16, 0x2A) = coordinate;
            if (FIELD(player, u8, 0x9A) == 0x11) {
                goto coords_continue;
            }
        } else {
            goto global_continue;
        }

jt_c12:
        func_800A9A0C(arg3);
        return;

coords_continue:
        if (FIELD(arg0, u8, 0xB5) == 0) {
            func_801717D0(arg0, arg1, arg2, D_800E2418, D_80171A80);
            return;
        }
global_continue:
        {
            void *global = D_800E3D7C[0];

            if (FIELD(global, u16, 0xA6) != 0) {
                goto ordinary_cleanup;
            }
            FIELD(global, u16, 0xA6) = 2;
            func_80175F44(arg0, arg1, arg2, 1, 2);
            return;
        }

jt_c3:
        if (FIELD(arg0, u8, 0xB5) == 0) {
            func_800AAF00(arg0, arg1, arg2, D_800E2418, D_80171A80);
            return;
        } else {
            register s32 fifth ASM_REG("$2") = 1;

            ASM_KEEP(fifth);
            func_80175F44(arg0, arg1, arg2,
                ({ ASM_CLOBBER("$2"); 1; }), fifth);
            return;
        }

jt_c4:
jt_c10:
jt_c11:
ordinary_cleanup:
        func_801723F8(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(FIELD(arg3, u32, 0x1C) & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25)) << 16) != 0) {
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                        &scratch);
                }
            }
        }
    }
}
