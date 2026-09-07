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
extern void func_801713E0(void) __attribute__((noreturn));
extern void func_80171414(void) __attribute__((noreturn));
extern void func_80171438(void);
extern void func_8017167C(void *, void *, void *, void *);
extern s32 func_80171E28(void *, void *, void *, void *);
extern void func_8017208C(void *, void *, void *, void *);
extern s32 func_80172230(void *, void *, void *, s32);
extern void func_80173A84(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170EA8;
extern u8 D_80174038[];
extern u8 D_80174040[];
extern u8 D_80174070[];
extern u8 D_80174080[];
extern u8 D_80174088[];

void func_80170EA8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 *table;
    s32 result;
    s32 scratch;
    u32 initial_flags = D_80083462;

    if (initial_flags & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171438();
        func_80171414();
        return;
    }

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) != D_80174088) {
#ifdef __mips__
            register void *state ASM_REG("$5");
            state = D_80174080;
            ASM_TAILSLOT_PIN(state);
#endif
            func_801713E0();
        }
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80174088) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            func_80171414();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174080)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_80171414();
            return;
        }

        ASM_KEEP(arg0);
        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            u8 state = 0xE;

            table = D_80174038;
            if (FIELD(arg2, void *, 0x2C) != table) {
                FIELD(arg2, void *, 0x2C) = table;
                func_80047784(arg2,
                    table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            FIELD(arg0, u8, 0x9A) = state;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174040)) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173A84(arg0, arg1, arg2, arg3);
            func_80171414();
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
        if (FIELD(arg2, u16, 0x24) == D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(arg3,
                        (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172230(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            FIELD(arg3, u16, 0x46) |= 0x4000;
            if (!(FIELD(arg3, u16, 0x46) & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

#ifdef __mips__
        {
            static void *volatile dispatch_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&case8_setup, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            s32 dispatch_index;

            dispatch_index = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
            if ((u32)dispatch_index >= 12) {
                goto ordinary_cleanup;
            }
            goto *D_80170808[dispatch_index];
        }
case8_setup:
#else
        switch (FIELD(arg3, u16, 0x46) & 0x3FFF) {
        case 8:
#endif
            FIELD(arg0, volatile u16, 0x98) |= 0x8000;
            if (FIELD(arg3, u32, 0x1C) & 0x2000) {
                if ((FIELD(arg3, u16, 0x46) & 0x3FFF) == 8) {
                    FIELD(arg0, volatile u16, 0x98) &= 0x7FFF;
                }
            }

#ifdef __mips__
handler_case:
#else
        case 9:
#endif
            if ((s16)func_80171E28(arg0, arg1, arg2, arg3) == 0) {
                func_8017208C(arg0, arg1, arg2, arg3);
                func_80171414();
            }
            return;

#ifdef __mips__
coords_case:
#else
        case 5:
        case 6:
        case 7:
#endif
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
            goto special_cleanup;
        }
#ifndef __mips__
        case 1:
        case 2:
        case 3:
            goto aaf_cleanup;

        case 12:
            goto special_cleanup;

        default:
            goto ordinary_cleanup;
        }
#endif

special_cleanup:
        func_800A9A0C(arg3);
        func_80171414();
        return;

aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_80174070, &D_80170EA8);
        func_80171414();
        return;

ordinary_cleanup:
        func_8017167C(arg0, arg1, arg2, arg3);
        func_80171414();
        return;
    } else if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
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
    table = D_80174038;
    if (FIELD(arg2, void *, 0x2C) == table) {
        return;
    }
    /* Zero-operand reorg barrier (byte-invisible): blocks gcc dbr from
     * stealing the following `lui %hi(D_80083228)` into the beq delay slot
     * (retail keeps the nop here). Must NOT be ASM_KEEP(table): a "+r" on
     * `table` launders its symbol_ref identity, and the array-index PLUS
     * then loses constant-second canonicalization, rotating the final
     * `addu $2,$2,$5` into `addu $2,$5,$2` (the wave-16 distance-1 wall). */
    ASM_SCHED_BARRIER();
    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(arg2,
        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
}
