#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
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
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171060(void) __attribute__((noreturn));
extern void func_80171430(void);
extern void func_80171468(void) __attribute__((noreturn));
extern void func_8017154C(void) __attribute__((noreturn));
extern void func_80171570(void);
extern void func_801717B4(void *, void *, void *, void *);
extern s32 func_80171FC0(void *, void *, void *, void *);
extern void func_80172184(void *, void *, void *, void *);
extern s32 func_8017229C(void *, void *, void *, s32);
extern void func_80173EF4(void *, void *, void *, void *);

extern s32 D_80045340;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80083498[];
extern u8 D_800D79B0[];
extern u8 D_800DEA68[];
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170E54;
extern u8 D_80174140[];
extern u8 D_80174148[];
extern u8 D_80174150[];
extern u8 D_80174188[];
extern u8 D_80174190[];

void func_80170E54(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
        &&normal_state, &&timer_table_reload,
    };
    s32 scratch;
    s16 offset[3];
    s8 result;
    u16 state;
    u8 *table;

    if (D_80083462 & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171570();
        func_8017154C();
        return;
    }

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80174190) {
            return;
        }
        {
            register void *next_state ASM_REG("$5");

            next_state = D_80174188;
            ASM_TAILSLOT_PIN(next_state);
        }
        func_80171060();
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80174190) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
            func_8017154C();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174188) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_8017154C();
            return;
        }

normal_state:
        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            table = D_80174148;
            if (FIELD(arg2, void *, 0x2C) != table) {
                FIELD(arg2, void *, 0x2C) = table;
                func_80047784(arg2,
                    table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
            FIELD(arg0, u8, 0x9A) = 0xE;
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174150) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            u8 *high_table;

            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173EF4(arg0, arg1, arg2, arg3);
            high_table = D_80174140;
            FIELD(arg2, void *, 0x2C) = high_table;
            func_80047784(arg2,
                high_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_8017154C();
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
            if ((func_8017229C(arg0, arg1, arg2, 0) << 16) == 0) {
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
        goto *D_80170808[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80171FC0(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172184(arg0, arg1, arg2, arg3);
        func_8017154C();
        return;

jt_c5:
jt_c6:
jt_c7:
        {
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
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(arg3);
        func_8017154C();
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(arg0, arg1, arg2, D_80174140, &D_80170E54);
        func_8017154C();
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801717B4(arg0, arg1, arg2, arg3);
        func_8017154C();
        return;
    }

    if (!(FIELD(arg3, u32, 0x1C) & 0x2000)) {
        s32 index = result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
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

    if (D_80083462 & 0x2000) {
        return;
    }
    if (FIELD(arg2, u16, 0x14) & 0x40) {
        return;
    }

    table = D_80174148;
    if ((FIELD(arg2, void *, 0x2C) != table) &&
        (FIELD(arg2, void *, 0x2C) != D_80174140)) {
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, s16, 0xAA) = 1;
        func_80171468();
        return;
    }

    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        s16 timer = FIELD(arg0, s16, 0xAA) - 1;

        FIELD(arg0, s16, 0xAA) = timer;
        if (timer < 0) {
            FIELD(arg0, s16, 0xAA) = (func_80069EF8() & 0x1F) + 0x20;
        }
        if (FIELD(arg0, s16, 0xAA) < 2) {
            {
                register void *next_state ASM_REG("$2");

                next_state = D_80174148;
                ASM_TAILSLOT_PIN(next_state);
            }
            func_80171430();
        }
        FIELD(arg2, void *, 0x2C) = D_80174140;
timer_table_reload:
        func_80047784(arg2,
            FIELD(arg2, u8 *, 0x2C)[
                ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    if (!func_8003DE58(FIELD(arg2, void *, 8), arg2, offset, 1)) {
        return;
    }
    if (FIELD(arg2, void *, 0x2C) != D_80174148) {
        return;
    }

    {
        void *created;
        void *sub;
        void *color;
        u8 *base;
        s32 base_word;

        created = func_8003FD64(0x112, D_80083498);
        FIELD(arg0, void *, 0xA0) = created;
        arg2 = created;
        if (arg2 == 0) {
            return;
        }
        func_8004491C(arg2, &D_80045340);
        color = (void *)0x00808080;
        FIELD(arg2, void *, 0x10) = D_800D79B0;
        FIELD(FIELD(arg2, void *, 8), u16, 2) =
            FIELD(arg1, u16, 2) + offset[0];
        FIELD(FIELD(arg2, void *, 8), u16, 6) =
            FIELD(arg1, u16, 6) + offset[1];
        FIELD(FIELD(arg2, void *, 8), u16, 0xA) =
            FIELD(arg1, u16, 0xA) + offset[2];
        sub = FIELD(arg2, void *, 0xC);
        base = D_800DEA68;
        FIELD(arg2, u8, 0xBB) = 0;
        FIELD(sub, s16, 0x1E) = 0xC00;
        FIELD(sub, s16, 0x1C) = 0xC00;
        FIELD(sub, void *, 0xC) = color;
        FIELD(sub, void *, 0) = base;
        FIELD(sub, volatile u16, 0x14) |= 0xC;
        base_word = FIELD(base, volatile s32, 4);
        FIELD(sub, volatile u8, 4) = 0;
        FIELD(sub, volatile u8, 5) = 0;
        FIELD(sub, volatile s32, 8) = base_word;
    }
}

extern void func_80171430(void) __attribute__((noreturn));
