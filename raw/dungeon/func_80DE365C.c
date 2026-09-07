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
extern s32 func_800A6D30(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171420(void *, void *, void *, void *);
extern void func_80171B68(void);
extern s32 func_80171E10(void *, void *, void *, void *);
extern void func_80171FD4(void *, void *, void *, void *);
extern s32 func_801720EC(void *, void *, void *, void *);
extern void func_8017236C(void *, void *, void *, void *);
extern void func_801737DC(void *, void *, void *, void *);
extern s32 func_80173E48(void *, void *, void *, s32);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *const D_80170808[];
extern u8 D_80174520[];
extern u8 D_80174530[];
extern u8 D_80174538[];
extern u8 D_80174548[];
extern u8 D_80174560[];

void func_80170E5C(void *in0, void *in1, void *in2, void *in3)
{
    register void *p0 ASM_REG("$17");
    register void *p1 ASM_REG("$19");
    register void *p2 ASM_REG("$18");
    register void *p3 ASM_REG("$16");
    u8 *table;
    s32 result;
    s32 scratch;
    u32 initial_flags = D_80083462;

    p0 = in0;
    p1 = in1;
    p2 = in2;
    p3 = in3;
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (initial_flags & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171B68();
        return;
    }

    ASM_KEEP(p0);
    ASM_KEEP(p1);
    ASM_KEEP(p2);
    ASM_KEEP(p3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80174538) {
            return;
        }
        FIELD(arg2, void *, 0x2C) = D_80174530;
        func_80047784(arg2,
            D_80174530[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80174538) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174530)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        {
            register s32 state ASM_REG("$20");
            s32 actor_state;

            actor_state = FIELD(arg0, u8, 0x9A);
            ASM_KEEP(actor_state);
            state = 0xE;
            ASM_KEEP(state);

            if (actor_state != state) {
                table = D_80174520;
                if (FIELD(arg2, void *, 0x2C) != table) {
                    FIELD(arg2, void *, 0x2C) = table;
                    func_80047784(arg2,
                        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                FIELD(arg0, u8, 0x9A) = state;
            }
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174548)) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_801737DC(arg0, arg1, arg2, arg3);
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
            if ((s16)func_80173E48(arg0, arg1, arg2, 0) == 0) {
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
                &&movement_case,
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
        if ((s16)func_80171E10(arg0, arg1, arg2, arg3) == 0) {
            func_80171FD4(arg0, arg1, arg2, arg3);
        }
        return;

movement_case:
        if (FIELD(arg3, u32, 0x1C) & 0x400) {
            register s32 value ASM_REG("$2");

            value = FIELD(arg3, s32, 0x14);
            ASM_KEEP(value);

            if (value >= 0) {
                FIELD(arg3, s32, 0x14) = value | 0x80000000;
                FIELD(arg3, u16, 0x2A) += (func_800A6D30(arg0) & 7) << 9;
            }
        }
        if ((s16)func_801720EC(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_8017236C(arg0, arg1, arg2, arg3);
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
        func_800AAF00(arg0, arg1, arg2, D_80174560, func_80170E5C);
        return;

ordinary_cleanup:
        func_80171420(arg0, arg1, arg2, arg3);
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
    table = D_80174520;
    if (FIELD(arg2, void *, 0x2C) == table) {
        return;
    }

update_table:
    ASM_KEEP(table);
    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(arg2,
        *(u8 *)((u32)(((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) +
            (u32)table),
        0);
}
