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
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171D58(void) __attribute__((noreturn));
extern void func_80171D7C(void);
extern void func_80171FE8(void *, void *, void *, void *);
extern s32 func_801727B8(void *, void *, void *, void *);
extern void func_8017297C(void *, void *, void *, void *);
extern s32 func_80172A94(void *, void *, void *, s32);
extern void func_80174258(void *, void *, void *, void *);
extern void func_80174798(void *, void *, void *, void *);
extern void func_801751C0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_801717F4;
extern u8 D_80175988[];
extern u8 D_80175998[];
extern u8 D_801759D0[];
extern u8 D_801759E0[];
extern u8 D_801759E8[];

void func_801717F4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    register void *p0 ASM_REG("$17");
    register void *p1 ASM_REG("$19");
    register void *p2 ASM_REG("$16");
    register void *p3 ASM_REG("$18");
    s32 scratch;
    s32 result;
    u16 state;
    u32 initial_flags = D_80083462;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (initial_flags & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171D7C();
        func_80171D58();
        return;
    }

    ASM_KEEP(p0);
    ASM_KEEP(p1);
    ASM_KEEP(p2);
    ASM_KEEP(p3);

    if (FIELD(arg3, u8, 0x25) == 0) {
        u8 *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_801759E8) {
            return;
        }
        table = D_801759E0;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        func_80171D58();
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_801759E8) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
            func_80171D58();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_801759E0) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_80171D58();
            return;
        }

        {
            u32 current_state = FIELD(arg0, u8, 0x9A);
            register u32 actor_state ASM_REG("$20");

            ASM_KEEP(current_state);
            actor_state = 0xE;
            if (current_state != actor_state) {
                u8 *table = D_80175988;

                if (FIELD(arg2, void *, 0x2C) != table) {
                    FIELD(arg2, void *, 0x2C) = table;
                    func_80047784(arg2,
                        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                FIELD(arg0, s16, 0x9E) = 0;
                FIELD(arg0, s16, 0xA0) = 0x14;
                FIELD(arg0, u8, 0x9A) = actor_state;
            }
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175998) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80174258(arg0, arg1, arg2, arg3);
            FIELD(arg2, void *, 0x2C) = D_80175988;
            func_80047784(arg2,
                D_80175988[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, s32, 0x90) = 0;
            func_80171D58();
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            if ((s16)func_800AAB10(arg0, arg1, arg2, arg3) != 0) {
                func_801751C0(arg0, arg1, arg2, arg3);
            }
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
            if ((s16)func_80172A94(arg0, arg1, arg2, 0) == 0) {
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
        goto *D_80170808[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((s16)func_801727B8(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_8017297C(arg0, arg1, arg2, arg3);
        ASM_KEEP(p0);
        func_80171D58();
        return;

jt_c10:
        func_80174798(arg0, arg1, arg2, arg3);
        func_80171D58();
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            register void *player ASM_REG("$3");
            s16 direction;

            direction = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                &scratch);
            player = D_800814A8;
#ifndef __mips__
            ASM_KEEP(player);
#endif
            FIELD(arg3, s16, 0x2A) = direction;
            if (FIELD(player, u8, 0x9A) == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }

jt_c12:
special_cleanup:
        func_800A9A0C(arg3);
        func_80171D58();
        return;

jt_c1:
jt_c2:
jt_c3:
aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_801759D0, &D_801717F4);
        func_80171D58();
        return;

jt_c4:
jt_c11:
ordinary_cleanup:
        func_80171FE8(arg0, arg1, arg2, arg3);
        func_80171D58();
        return;
    }

    if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(FIELD(arg3, u32, 0x1C) & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25)) != 0) {
                    FIELD(arg3, s16, 0x2A) = func_800A0818(
                        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                        FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25),
                        &scratch);
                }
            }
        }
    }
}
