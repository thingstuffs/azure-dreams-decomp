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
extern s32 rand(void);
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
extern void func_80171088(void) __attribute__((noreturn));
extern void func_80171474(void); /* noreturn evidence decl after body: gcc must
    NOT see the barrier here or reorg predicts the beqz taken and fills its slot
    from the target; retail fills from the fallthrough */
extern void func_801714AC(void) __attribute__((noreturn));
extern void func_80171590(void) __attribute__((noreturn));
extern void func_801715B4(void);
extern void func_801717F8(void *, void *, void *, void *);
extern s32 func_80171FA4(void *, void *, void *, void *);
extern void func_80172168(void *, void *, void *, void *);
extern s32 func_80172280(void *, void *, void *, s32);
extern void func_80173F20(void *, void *, void *, void *);
extern void func_80174470(void *, void *, void *, void *);

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
extern u8 D_80170E7C;
extern u8 D_80174C34[];
extern u8 D_80174C3C[];
extern u8 D_80174C44[];
extern u8 D_80174C84[];
extern u8 D_80174C8C[];

void func_80170E7C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 scratch;
    s16 offset[3];
    s8 result;
    u16 state;
    u8 *table;

    if (D_80083462 & 0x1000) {
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_801715B4();
        func_80171590();
        return;
    }

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80174C8C) {
            return;
        }
#ifdef __mips__
        {
            register void *next_state ASM_REG("$5");

            next_state = D_80174C84;
            ASM_TAILSLOT_PIN(next_state);
        }
#endif
        func_80171088();
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80174C8C) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
            func_80171590();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174C84) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_80171590();
            return;
        }

        {
            u32 current_state = FIELD(arg0, u8, 0x9A);
            register u32 actor_state ASM_REG("$17");

            ASM_KEEP(current_state);
            actor_state = 0xE;
#ifndef __mips__
            ASM_KEEP(actor_state);
#endif
            if (current_state != actor_state) {
                table = D_80174C3C;
                if (FIELD(arg2, void *, 0x2C) != table) {
                    FIELD(arg2, void *, 0x2C) = table;
                    func_80047784(arg2,
                        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                FIELD(arg0, u8, 0x9A) = actor_state;
            }
        }

        FIELD(arg0, u16, 0x98) &= 0xFFF3;
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174C44) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            register u8 *high_table ASM_REG("$5");

            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173F20(arg0, arg1, arg2, arg3);
            high_table = D_80174C34;
#ifndef __mips__
            ASM_KEEP(high_table);
#endif
            FIELD(arg2, void *, 0x2C) = high_table;
            func_80047784(arg2,
                high_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_80171590();
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            if ((func_800AAB10(arg0, arg1, arg2, arg3) << 16) != 0) {
                func_80174470(arg0, arg1, arg2, arg3);
            }
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
            if ((func_80172280(arg0, arg1, arg2, 0) << 16) == 0) {
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
        if ((func_80171FA4(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172168(arg0, arg1, arg2, arg3);
        func_80171590();
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
        func_80171590();
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(arg0, arg1, arg2, D_80174C34, &D_80170E7C);
        func_80171590();
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801717F8(arg0, arg1, arg2, arg3);
        func_80171590();
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

    table = D_80174C3C;
    if ((FIELD(arg2, void *, 0x2C) != table) &&
        (FIELD(arg2, void *, 0x2C) != D_80174C34)) {
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, s16, 0xAA) = 1;
        func_801714AC();
        return;
    }

    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        s16 timer = FIELD(arg0, s16, 0xAA) - 1;

        FIELD(arg0, s16, 0xAA) = timer;
        if (timer < 0) {
            FIELD(arg0, s16, 0xAA) = (rand() & 0x1F) + 0x20;
        }
        if (FIELD(arg0, s16, 0xAA) < 2) {
#ifdef __mips__
            {
                register void *next_state ASM_REG("$2");

                next_state = D_80174C3C;
                ASM_TAILSLOT_PIN(next_state);
            }
#endif
            func_80171474();
            /* no return: the call (noreturn at runtime, via maspsx evidence
               only) falls through into the store path, so the target label is
               fallthrough-reached and reorg cannot steal from it */
        }
        FIELD(arg2, void *, 0x2C) = D_80174C34;
        func_80047784(arg2,
            ((u8 *)*(u8 * volatile *)((u8 *)arg2 + 0x2C))[
                ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    if (!func_8003DE58(FIELD(arg2, void *, 8), arg2, offset, 1)) {
        return;
    }
    if (FIELD(arg2, void *, 0x2C) != D_80174C3C) {
        return;
    }

    {
        void *created;
        void *sub;
        void *color;
        u8 *base;

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
        FIELD(sub, u16, 0x14) |= 0xC;
        {
            /* one-read temp BEFORE the byte clears: source order = retail
               emission order (ori,sh,lw,sb,sb,sw) and the two sb sit in the
               lw load-delay shadow with no scheduler motion needed */
            s32 anim = FIELD(base, s32, 4);
            FIELD(sub, u8, 4) = 0;
            FIELD(sub, u8, 5) = 0;
            FIELD(sub, s32, 8) = anim;
        }
    }
}

/* LEAD-18 evidence redeclaration, AFTER the body on purpose: gcc 2.8.1 binds
 * decls top-down, so the call site above compiled without a noreturn barrier
 * (matching retail's compile, which predates the attribute), while the
 * cpp-blind census scanner (tools/gen_noreturn_syms.py scan_text) still
 * harvests the symbol so maspsx's jal->j tail-call conversion fires. */
extern void func_80171474(void) __attribute__((noreturn));
