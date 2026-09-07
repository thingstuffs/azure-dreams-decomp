#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270();
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DA840(u16 *, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170838[];
extern u8 D_80170E7C;
extern u8 D_80174D4C[];
extern u8 D_80174D94[];
extern u8 D_80174D9C[];
extern u8 D_80174DA4[];

void func_80172AB4(void *arg0_in, void *arg1_in, void *arg2_in, void *arg3_in)
{
    static void *const switch_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_none,
        &&special_1, &&special_2, &&special_3
    };
    u8 *choice;
    s32 state;
    s32 special;
    s32 kind;
    void *object;
    register void *arg0 ASM_REG("$19") = arg0_in;
    register void *arg1 ASM_REG("$20") = arg1_in;
    register void *arg2 ASM_REG("$18") = arg2_in;
    register void *arg3 ASM_REG("$17") = arg3_in;
    register void *record ASM_REG("$3");
    register s32 x ASM_REG("$2");
    s32 y;
    u16 position[3];
    u16 next;

    ASM_KEEP4_NV(arg0, arg1, arg2, arg3);

    state = FIELD(arg0, u8, 0x9B);
    special = 0;
    if (state == 3) {
        goto state_3;
    }
    if (state < 4) {
        if (state == 1) {
            goto state_1;
        }
        if (state >= 2) {
            goto state_2;
        }
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    {
        register s32 five ASM_REG("$2") = 5;

        ASM_KEEP_NV(five);
        if (state == five) {
            goto state_5;
        }
    }
    if (state < 5) {
        goto state_4;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if ((u32)kind >= 7U) {
            goto kind_none;
        }
        (void)switch_keep;
        goto *D_80170838[kind];

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
    if (*choice != 0) {
        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        ASM_SCHED_BARRIER();
        {
            register s32 special_test ASM_REG("$2") = special;

            ASM_KEEP(special_test);
            if (special_test != 0) {
                object = D_800814A8;
                FIELD(arg3, void *, 0x60) = object;
                goto copy_existing;
            }
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
        x = FIELD(arg3, s8, 0x72);
        y = FIELD(arg3, s8, 0x73);
        ASM_KEEP(x);
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
        position[0] = FIELD(arg1, u16, 2);
        position[1] = FIELD(arg1, u16, 6);
        position[2] = FIELD(arg1, u16, 0xA);
        if (func_800A94A0(arg3, choice, special,
                          (u16 *)((u8 *)arg0 + 0x98)) == 0) {
            goto done;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(position, (s16)(((s32)*choice - 1) % 3));
        goto advance_state;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = &D_80170E7C;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto done;

state_1:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        goto done;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174D9C;
    func_80047784(
        arg2,
        D_80174D9C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, u16, 0x96) = 8;
    FIELD(arg1, s32, 0x14) = 0xFFF00000;
    goto advance_state;

state_2:
    FIELD(arg1, s32, 0x14) += 0x10000;
    next = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = next;
    if ((s32)(next << 16) > 0) {
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174DA4;
    func_80047784(
        arg2,
        D_80174DA4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg1, s32, 0x14) = 0;
    goto advance_state;

state_3:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto done;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_4:
    if (!(((FIELD(arg2, s8, 4) == 1) &&
           (FIELD(arg2, u16, 0x14) & 0x1000)) ||
          (FIELD(arg2, u16, 0x14) & 0xE000))) {
        goto done;
    }
    FIELD(arg0, u16, 0x96) = 3;
    FIELD(arg0, u16, 0x98) |= 0x80;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174D9C;
    func_80047784(
        arg2,
        D_80174D9C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) |= 0x08000000;

advance_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_5:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174D94;
    func_80047784(
        arg2,
        D_80174D94[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u8, 0x9B) = 0xFF;
    goto done;

state_ff:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, u8 *, 0x2C) != D_80174D4C) {
        FIELD(arg2, u8 *, 0x2C) = D_80174D4C;
        func_80047784(
            arg2,
            D_80174D4C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    {
        u8 *globals = (u8 *)&D_80083460;

        if (FIELD(globals, s32, 0xC) != 0) {
            goto done;
        }
        FIELD(globals, u16, 0xA)--;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, void *, 0x8C) = &D_80170E7C;
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
