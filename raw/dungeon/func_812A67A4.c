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
extern void func_80172168(void) __attribute__((noreturn));
extern void func_801724F0(void) __attribute__((noreturn));
extern void func_80172510(void);
extern void func_801726C8(void *, void *, void *, void *);
extern s32 func_80172E10(void *, void *, void *, void *);
extern void func_801730A8(void *, void *, void *, void *);
extern s32 func_801731CC(void *, void *, void *, void *);
extern void func_80175078(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170818[];
extern u8 D_80171FA4[];
extern u8 D_80175C30[];
extern u8 D_80175C38[];
extern u8 D_80175C88[];
extern u8 D_80175C90[];
extern u8 D_80175CA0[];
extern u8 D_80175CA8[];

void func_80171FA4(void *arg0, void *arg1, void *arg2, void *arg3)
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
        func_80172510();
        func_801724F0();
        return;
    }
    if (FIELD(arg3, u8, 0x25) == 0) {
        void *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80175C90) {
            return;
        }
        table = D_80175CA0;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            ((u8 *)table)[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        func_801724F0();
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80175C90) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
            func_801724F0();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80175CA0) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_801724F0();
            return;
        }

        ASM_KEEP(arg0);
        {
            u8 current_state = FIELD(arg0, u8, 0x9A);
            register u32 actor_state ASM_REG("$3") = 0xE;
            register void *current ASM_REG("$3");
            void *table;

#ifndef __mips__
            ASM_KEEP(actor_state);
#endif
            if (current_state != actor_state) {
                FIELD(arg0, u8, 0x9A) = actor_state;
                FIELD(arg0, s16, 0xB6) = 0;
            }
            ASM_KEEP(arg0);
            current = FIELD(arg2, void *, 0x2C);
            ASM_KEEP(current);
            if (current == D_80175CA8) {
                if (FIELD(arg2, u16, 0x14) & 0xE000) {
#ifdef __mips__
                    register void *state_table ASM_REG("$5");
                    state_table = D_80175C30;
                    ASM_TAILSLOT_PIN(state_table);
#endif
                    func_80172168();
                }
            } else {
                table = D_80175C30;
                if (current != table) {
                    ASM_KEEP(current);
                    FIELD(arg2, void *, 0x2C) = table;
                    func_80047784(arg2,
                        ((u8 *)table)[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                    FIELD(arg2, u8, 5) = 1;
                    FIELD(arg0, s16, 0xA2) = 0;
                    FIELD(arg0, s16, 0x9E) = 0;
                }
            }
        }

        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175C38) != 0) {
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
            func_80175078(arg0, arg1, arg2, arg3);
            func_801724F0();
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
            goto case_12;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801731CC(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = FIELD(arg3, u16, 0x46) | 0x4000;
            FIELD(arg3, u16, 0x46) = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        state = FIELD(arg3, u16, 0x46) & 0x3FFF;
        if ((u32)(state - 1) >= 12) {
            goto generic;
        }
        (void)jt_keep;
        goto *D_80170818[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80172E10(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_801730A8(arg0, arg1, arg2, arg3);
        func_801724F0();
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            register void *player ASM_REG("$3");
            s16 coordinate;

        coordinate = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
            &scratch);
        player = D_800814A8;
#ifndef __mips__
        ASM_KEEP(player);
#endif
        FIELD(arg3, s16, 0x2A) = coordinate;
        if (FIELD(player, u8, 0x9A) == 0x11) {
            goto case_123;
        }
        }

jt_c12:
case_12:
        func_800A9A0C(arg3);
        func_801724F0();
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(arg0, arg1, arg2, D_80175C88, D_80171FA4);
        func_801724F0();
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801726C8(arg0, arg1, arg2, arg3);
        func_801724F0();
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
