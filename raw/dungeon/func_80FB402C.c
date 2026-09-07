#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8006649C(s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174250(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80083498[];
extern u8 D_80170F6C[];
extern u8 D_80174424[];
extern u8 D_80175298[];

void func_8017382C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto done;

state_zero:
    {
        register s32 i ASM_REG("$3");
        s32 scaled;
        register s32 index ASM_REG("$2");
        register u8 *entry ASM_REG("$2");
        register u8 *records ASM_REG("$4");
        u8 *table;
        u8 *global;
        void *effect;
        register u8 *child ASM_REG("$5");
        u16 facing;

        i = 0;
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto done;
        }

        FIELD(arg0, u16, 0xAE) = FIELD(arg2, u16, 0x12);
        records = FIELD(arg2, u8 *, 8);
scan_zero:
        scaled = i << 1;
        if (!(FIELD(records, u8, 0) & 0x20)) {
            goto scan_zero_done;
        }
        records += 0xC;
        i++;
        goto scan_zero;
        scan_zero_done:
        index = scaled + i;
        entry = (u8 *)((unsigned long)(index << 2) +
                       (unsigned long)FIELD(arg2, u8 *, 8));
        FIELD(arg0, u16, 0xAC) =
            FIELD(entry, u16, 6) & 0xFFC0;

        table = D_80175298;
        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        global = (u8 *)&D_80083460;
        FIELD(global, u16, 0xA)--;
        effect = func_8003FD64(0x10, D_80083498);
        child = (u8 *)effect + 0x20;
        if (effect != 0) {
            FIELD(effect, void *, 0x10) = D_80174424;
            FIELD(child, s16, 0xA0) = 0;
            facing = FIELD(arg0, u16, 0xAC);
            FIELD(child, s16, 0xA4) = 0x100;
            FIELD(child, s16, 0xA6) = 1;
            FIELD(child, s16, 0xA8) = 8;
            FIELD(child, s16, 0xA2) = (s16)facing >> 6;
            FIELD(arg0, u16, 0x96) = 8;
            FIELD(child, s16, 0x96) = 0;
            FIELD(child, s16, 0x9E) = 0;
        }
        goto increment_state;
    }

state_one:
    {
        s32 angle;
        s32 signed_angle;
        s32 rounded;
        s32 remainder;
        u16 timer;

        angle = FIELD(arg0, u16, 0xAE) << 16;
        signed_angle = angle >> 16;
        rounded = signed_angle;
        if (rounded < 0) {
            rounded += 7;
        }
        remainder = signed_angle - ((rounded >> 3) << 3);
        FIELD(arg2, u16, 0x12) =
            func_8006649C(
                ((((s32)(remainder << 16) >> 18) << 6) + 0x340),
                ((angle >> 19) + 0x100)) -
            FIELD(arg0, u16, 0xAC);

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((s16)timer > 0) {
            if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
                goto done;
            }
        }
        FIELD(arg2, u16, 0x12) = FIELD(arg0, u16, 0xAE) - 0x40;
        goto increment_state;
    }

state_two:
    {
        s32 i;
        s32 scaled;
        register s32 index ASM_REG("$2");
        register u8 *entry ASM_REG("$2");
        u8 *records;
        register u8 *table ASM_REG("$5");
        u8 *late_table;
        u8 *early_counter;
        u8 *status_base;
        u8 *late_counter;
        void *effect;
        u8 *child;
        void *random_arg;
        register u16 facing ASM_REG("$3");

        if (FIELD(arg0, s16, 0xAC) == 0) {
            i = 0;
            records = FIELD(arg2, u8 *, 8);
scan_two:
            scaled = i << 1;
            if (!(FIELD(records, u8, 0) & 0x20)) {
                goto scan_two_done;
            }
            records += 0xC;
            i++;
            goto scan_two;
scan_two_done:
            index = scaled + i;
            entry = (u8 *)((unsigned long)(index << 2) +
                           (unsigned long)FIELD(arg2, u8 *, 8));
            FIELD(arg0, u16, 0xAC) =
                FIELD(entry, u16, 6) & 0xFFC0;
        }

        if ((s16)func_80042900(arg3, 1) != 0) {
            goto state_two_active;
        }

        table = D_80175298;
        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        effect = func_8003FD64(0x10, D_80083498);
        child = (u8 *)effect + 0x20;
        if (effect != 0) {
            FIELD(effect, void *, 0x10) = D_80174424;
            FIELD(child, s16, 0xA0) = 0;
            facing = FIELD(arg0, u16, 0xAC);
            FIELD(child, s16, 0xA4) = 0x100;
            FIELD(child, s16, 0xA6) = 1;
            FIELD(child, s16, 0xA8) = 8;
            FIELD(child, s16, 0xA2) = (s16)facing >> 6;
            FIELD(arg0, u16, 0x96) = 8;
            FIELD(child, s16, 0x96) = 0;
            FIELD(child, s16, 0x9E) = 1;
        }

        FIELD(arg0, u16, 0xAE) = FIELD(arg2, u16, 0x12) + 0x40;
        early_counter = (u8 *)&D_80083460;
        FIELD(early_counter, u16, 0xA)++;

increment_state:
        FIELD(arg0, u8, 0x9B)++;
        goto done;

state_two_active:
        status_base = (u8 *)&D_80083460;
        if (FIELD(status_base, u16, 2) & 0x1000) {
            goto done;
        }
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }

        if (FIELD(arg3, u8, 0x25) == 0) {
            if (FIELD(status_base, u16, 2) & 0x2008) {
                goto done;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto done;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            goto done;
        }

        {
            u32 flags;

            flags = FIELD(arg3, u32, 0x1C);
            if (flags & 0x100) {
                func_800AA258(arg0, arg1, arg2, arg3);
                goto done;
            }
            if (flags & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                func_80174250(arg0, arg1, arg2, arg3);
                goto done;
            }
        }

        if (FIELD(arg3, s8, 0x6D) == 0) {
            goto done;
        }
        if ((s16)func_800A2C34(arg3) != 0) {
            if ((s16)func_8009A180(
                    arg3, (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                goto done;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((s16)func_80042900(arg3, 1) != 0) {
            s8 tile;

            random_arg = D_80082E80;
            tile = FIELD(arg2, s8, 0x26);
            if ((tile != FIELD(D_80082E80, s8, 0x26)) || (tile < 0)) {
                s32 r;

                r = (s16)func_8009FD40(D_80082E80, arg2);
                random_arg = arg3;
                if (r >= 2) {
                    goto second_call;
                }
            }
            if (!(func_800A6D30(random_arg) & 7)) {
                func_80042B68(arg3, 1);
            }
        }

        random_arg = arg3;
second_call:
        if ((s16)func_80042900(random_arg, 1) != 0) {
            goto done;
        }

        late_table = D_80175298;
        FIELD(arg2, u8 *, 0x2C) = late_table;
        func_80047784(
            arg2,
            late_table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        effect = func_8003FD64(0x10, D_80083498);
        child = (u8 *)effect + 0x20;
        if (effect != 0) {
            FIELD(effect, void *, 0x10) = D_80174424;
            FIELD(child, s16, 0xA0) = 0;
            facing = FIELD(arg0, u16, 0xAC);
            FIELD(child, s16, 0xA4) = 0x100;
            FIELD(child, s16, 0xA6) = 1;
            FIELD(child, s16, 0xA8) = 8;
            FIELD(child, s16, 0xA2) = (s16)facing >> 6;
            FIELD(arg0, u16, 0x96) = 8;
            FIELD(child, s16, 0x96) = 0;
            FIELD(child, s16, 0x9E) = 1;
        }
        late_counter = (u8 *)&D_80083460;
        FIELD(late_counter, u16, 0xA)++;
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg0, u16, 0xAE) = FIELD(arg2, u16, 0x12) + 0x40;
        goto done;
    }

state_three:
    {
        s32 angle;
        s32 signed_angle;
        s32 rounded;
        s32 remainder;
        u16 timer;
        u8 *global;

        angle = FIELD(arg0, u16, 0xAE) << 16;
        signed_angle = angle >> 16;
        rounded = signed_angle;
        if (rounded < 0) {
            rounded += 7;
        }
        remainder = signed_angle - ((rounded >> 3) << 3);
        FIELD(arg2, u16, 0x12) =
            func_8006649C(
                ((((s32)(remainder << 16) >> 18) << 6) + 0x340),
                ((angle >> 19) + 0x102)) -
            FIELD(arg0, u16, 0xAC);

        if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
            timer = FIELD(arg0, u16, 0x96) - 1;
            FIELD(arg0, u16, 0x96) = timer;
            if ((s16)timer > 0) {
                goto done;
            }
        }

        global = (u8 *)&D_80083460;
        FIELD(global, u16, 0xA)--;
        FIELD(arg3, u32, 0x1C) &= ~0x200;
        FIELD(arg0, void *, 0x8C) = D_80170F6C;
        FIELD(arg2, u16, 0x12) = FIELD(arg0, u16, 0xAE);
    }

done:
    return;
}
