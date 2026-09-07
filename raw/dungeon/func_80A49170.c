#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4();
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_8017140C[];
extern u8 D_8017586C[];

void func_80172970(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const switch_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_none,
        &&special_1, &&special_2, &&special_3
    };
    s32 state;
    s32 special;
    s32 special_test;
    s32 kind;
    register u8 *choice ASM_REG("$16");
    void *object;
    register void *record ASM_REG("$3");
    s32 x;
    s32 y;
    u16 timer;

    state = FIELD(arg0, u8, 0x9B);
    special = 0;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    goto done;

state_0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if ((u32)kind >= 7U) {
            goto kind_none;
        }
        (void)switch_keep;
        goto *(((void **)D_80170838)[kind]);

special_3:
        special = 1;
        goto kind_3;
special_2:
        special = 1;
        goto kind_2;
special_1:
        special = 1;
        goto kind_1;
    }

    kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (kind == 2) {
        goto kind_2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto kind_1;
        }
        choice = 0;
        goto have_choice;
    }
    if (kind != 3) {
        choice = 0;
        goto have_choice;
    }

kind_3:
    choice = (u8 *)arg3 + 0xE;
    goto have_choice;
kind_2:
    choice = (u8 *)arg3 + 0xB;
    goto have_choice;
kind_1:
    choice = (u8 *)arg3 + 8;
    goto have_choice;
kind_none:
    choice = 0;

have_choice:
    ASM_KEEP(choice);
    if (*choice != 0) {
        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        special_test = special;
        ASM_KEEP(special_test);
        if (special_test != 0) {
            object = D_800814A8;
            FIELD(arg3, void *, 0x60) = object;
            goto copy_existing;
        }

        if (D_8006DE24[(*choice * 20) + 0x12] == 2) {
            object = FIELD(arg3, void *, 0x60);
            if (object == 0) {
                goto move_setup;
            }
copy_existing:
            record = FIELD(object, void *, -0x14);
            ASM_KEEP(record);
            FIELD(arg3, u8, 0x72) = FIELD(record, u8, 0x24);
            FIELD(arg3, u8, 0x73) = FIELD(record, u8, 0x25);
            goto apply_move;
        }

        FIELD(arg3, void *, 0x60) =
            func_800A05A4(arg3,
                          FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25),
                          FIELD(arg3, s16, 0x2A), 0x10);
        ASM_SCHED_BARRIER();
        x = FIELD(arg3, s8, 0x72);
        y = FIELD(arg3, s8, 0x73);
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        FIELD(arg3, u8, 0x72) = x;
        FIELD(arg3, u8, 0x73) = y;

move_setup:
apply_move:
        FIELD(arg0, u16, 0x98) |= 0x1000;
        if (func_800A94A0(arg3, choice, special,
                          (u16 *)((u8 *)arg0 + 0x98)) == 0) {
            goto done;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        FIELD(arg0, u16, 0x96) = 0xE;
        FIELD(arg0, u8, 0x9B)++;
        goto done;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_8017140C;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto done;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_2:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s32)(timer << 16) > 0) {
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto done;
        }
    }
    FIELD(arg0, u16, 0x98) |= 0x80;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, u8 *, 0x2C) != D_8017586C) {
        FIELD(arg2, u8 *, 0x2C) = D_8017586C;
        func_80047784(
            arg2,
            D_8017586C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    {
        s32 *globals = &D_80083460;

        if (FIELD(globals, s32, 0xC) != 0) {
            goto done;
        }
        FIELD(globals, u16, 0xA)--;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, void *, 0x8C) = D_8017140C;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) > 0) {
        FIELD(arg3, u8, 0x6D)--;
    }
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}

/* MECHANISM: The 0x38 frame naturally holds args in s3/s4/s2/s1, with s5 state and s0 choice.
   Carrying the loaded object through the copy join removes a redundant lw+nop pair.
   A kept special-test copy restores move v0,s5; a schedule fence orders the result store.
   Holding the copied record in v1 closes the final four register-field substitutions. */
