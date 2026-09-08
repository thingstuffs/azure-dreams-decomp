#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017382C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u16 s; s16 u; } unk_AC;   /* accessed as both */
    u16 unk_AE;
} S_8017382C_0;   /* arg0 in func_8017382C */


typedef struct S_8017382C_2 {
    u8 unk_00;
} S_8017382C_2;   /* records in func_8017382C */

typedef struct S_8017382C_3 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_8017382C_3;   /* entry in func_8017382C */


typedef struct S_8017382C_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017382C_5;   /* global in func_8017382C */

typedef struct S_8017382C_6 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8017382C_6;   /* effect in func_8017382C */

typedef struct S_8017382C_7 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    s16 unk_A0;
    s16 unk_A2;
    s16 unk_A4;
    s16 unk_A6;
    s16 unk_A8;
} S_8017382C_7;   /* child in func_8017382C */

typedef struct S_8017382C_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017382C_8;   /* early_counter in func_8017382C */

typedef struct S_8017382C_9 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8017382C_9;   /* status_base in func_8017382C */



typedef struct S_8017382C_12 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017382C_12;   /* late_counter in func_8017382C */



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

    state = ((S_8017382C_0 *)arg0)->unk_9B;
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
        s32 i;
        s32 scaled;
        s32 index;
        u8 *entry;
        register u8 *records ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *table;
        u8 *global;
        void *effect;
        register u8 *child ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u16 facing;

        i = 0;
        if (!(((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000)) {
            goto done;
        }

        ((S_8017382C_0 *)arg0)->unk_AE = ((Rec_func_800AA258_arg2 *)arg2)->unk_12;
        records = ((Rec_func_800AA258_arg2 *)arg2)->unk_08;
scan_zero:
        scaled = i << 1;
        if (!(((S_8017382C_2 *)records)->unk_00 & 0x20)) {
            goto scan_zero_done;
        }
        records += 0xC;
        i++;
        goto scan_zero;
        scan_zero_done:
        index = scaled + i;
        entry = (u8 *)((unsigned long)(index << 2) +
                       (unsigned long)((Rec_func_800AA258_arg2 *)arg2)->unk_08);
        ((S_8017382C_0 *)arg0)->unk_AC.s =
            ((S_8017382C_3 *)entry)->unk_06 & 0xFFC0;

        table = D_80175298;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);

        global = (u8 *)&D_80083460;
        ((S_8017382C_5 *)global)->unk_0A--;
        effect = func_8003FD64(0x10, D_80083498);
        child = (u8 *)effect + 0x20;
        if (effect != 0) {
            ((S_8017382C_6 *)effect)->unk_10 = D_80174424;
            ((S_8017382C_7 *)child)->unk_A0 = 0;
            facing = ((S_8017382C_0 *)arg0)->unk_AC.s;
            ((S_8017382C_7 *)child)->unk_A4 = 0x100;
            ((S_8017382C_7 *)child)->unk_A6 = 1;
            ((S_8017382C_7 *)child)->unk_A8 = 8;
            ((S_8017382C_7 *)child)->unk_A2 = (s16)facing >> 6;
            ((S_8017382C_0 *)arg0)->unk_96 = 8;
            ((S_8017382C_7 *)child)->unk_96 = 0;
            ((S_8017382C_7 *)child)->unk_9E = 0;
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

        angle = ((S_8017382C_0 *)arg0)->unk_AE << 16;
        signed_angle = angle >> 16;
        rounded = signed_angle;
        if (rounded < 0) {
            rounded += 7;
        }
        remainder = signed_angle - ((rounded >> 3) << 3);
        ((Rec_func_800AA258_arg2 *)arg2)->unk_12 =
            func_8006649C(
                ((((s32)(remainder << 16) >> 18) << 6) + 0x340),
                ((angle >> 19) + 0x100)) -
            ((S_8017382C_0 *)arg0)->unk_AC.s;

        timer = ((S_8017382C_0 *)arg0)->unk_96 - 1;
        ((S_8017382C_0 *)arg0)->unk_96 = timer;
        if ((s16)timer > 0) {
            if (!(((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0x8000)) {
                goto done;
            }
        }
        ((Rec_func_800AA258_arg2 *)arg2)->unk_12 = ((S_8017382C_0 *)arg0)->unk_AE - 0x40;
        goto increment_state;
    }

state_two:
    {
        s32 i;
        s32 scaled;
        s32 index;
        u8 *entry;
        u8 *records;
        u8 *table;
        u8 *late_table;
        u8 *early_counter;
        u8 *status_base;
        u8 *late_counter;
        void *effect;
        u8 *child;
        void *random_arg;
        register u16 facing ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        if (((S_8017382C_0 *)arg0)->unk_AC.u == 0) {
            i = 0;
            records = ((Rec_func_800AA258_arg2 *)arg2)->unk_08;
scan_two:
            scaled = i << 1;
            if (!(((S_8017382C_2 *)records)->unk_00 & 0x20)) {
                goto scan_two_done;
            }
            records += 0xC;
            i++;
            goto scan_two;
scan_two_done:
            index = scaled + i;
            entry = (u8 *)((unsigned long)(index << 2) +
                           (unsigned long)((Rec_func_800AA258_arg2 *)arg2)->unk_08);
            ((S_8017382C_0 *)arg0)->unk_AC.s =
                ((S_8017382C_3 *)entry)->unk_06 & 0xFFC0;
        }

        if ((s16)func_80042900(arg3, 1) != 0) {
            goto state_two_active;
        }

        table = D_80175298;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);

        effect = func_8003FD64(0x10, D_80083498);
        child = (u8 *)effect + 0x20;
        if (effect != 0) {
            ((S_8017382C_6 *)effect)->unk_10 = D_80174424;
            ((S_8017382C_7 *)child)->unk_A0 = 0;
            facing = ((S_8017382C_0 *)arg0)->unk_AC.s;
            ((S_8017382C_7 *)child)->unk_A4 = 0x100;
            ((S_8017382C_7 *)child)->unk_A6 = 1;
            ((S_8017382C_7 *)child)->unk_A8 = 8;
            ((S_8017382C_7 *)child)->unk_A2 = (s16)facing >> 6;
            ((S_8017382C_0 *)arg0)->unk_96 = 8;
            ((S_8017382C_7 *)child)->unk_96 = 0;
            ((S_8017382C_7 *)child)->unk_9E = 1;
        }

        ((S_8017382C_0 *)arg0)->unk_AE = ((Rec_func_800AA258_arg2 *)arg2)->unk_12 + 0x40;
        early_counter = (u8 *)&D_80083460;
        ((S_8017382C_8 *)early_counter)->unk_0A++;

increment_state:
        ((S_8017382C_0 *)arg0)->unk_9B++;
        goto done;

state_two_active:
        status_base = (u8 *)&D_80083460;
        if (((S_8017382C_9 *)status_base)->unk_02 & 0x1000) {
            goto done;
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
            if (((S_8017382C_9 *)status_base)->unk_02 & 0x2008) {
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

            flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32;
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

        if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
            goto done;
        }
        if ((s16)func_800A2C34(arg3) != 0) {
            if ((s16)func_8009A180(
                    arg3, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                goto done;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((s16)func_80042900(arg3, 1) != 0) {
            s8 tile;

            random_arg = D_80082E80;
            tile = ((Rec_func_800AA258_arg2 *)arg2)->unk_26.as_s8;
            if ((tile != ((Rec_D_80082E80 *)D_80082E80)->unk_26.as_s8) || (tile < 0)) {
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
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = late_table;
        func_80047784(
            arg2,
            late_table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);

        effect = func_8003FD64(0x10, D_80083498);
        child = (u8 *)effect + 0x20;
        if (effect != 0) {
            ((S_8017382C_6 *)effect)->unk_10 = D_80174424;
            ((S_8017382C_7 *)child)->unk_A0 = 0;
            facing = ((S_8017382C_0 *)arg0)->unk_AC.s;
            ((S_8017382C_7 *)child)->unk_A4 = 0x100;
            ((S_8017382C_7 *)child)->unk_A6 = 1;
            ((S_8017382C_7 *)child)->unk_A8 = 8;
            ((S_8017382C_7 *)child)->unk_A2 = (s16)facing >> 6;
            ((S_8017382C_0 *)arg0)->unk_96 = 8;
            ((S_8017382C_7 *)child)->unk_96 = 0;
            ((S_8017382C_7 *)child)->unk_9E = 1;
        }
        late_counter = (u8 *)&D_80083460;
        ((S_8017382C_12 *)late_counter)->unk_0A++;
        ((S_8017382C_0 *)arg0)->unk_9B++;
        ((S_8017382C_0 *)arg0)->unk_AE = ((Rec_func_800AA258_arg2 *)arg2)->unk_12 + 0x40;
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

        angle = ((S_8017382C_0 *)arg0)->unk_AE << 16;
        signed_angle = angle >> 16;
        rounded = signed_angle;
        if (rounded < 0) {
            rounded += 7;
        }
        remainder = signed_angle - ((rounded >> 3) << 3);
        ((Rec_func_800AA258_arg2 *)arg2)->unk_12 =
            func_8006649C(
                ((((s32)(remainder << 16) >> 18) << 6) + 0x340),
                ((angle >> 19) + 0x102)) -
            ((S_8017382C_0 *)arg0)->unk_AC.s;

        if (!(((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0x8000)) {
            timer = ((S_8017382C_0 *)arg0)->unk_96 - 1;
            ((S_8017382C_0 *)arg0)->unk_96 = timer;
            if ((s16)timer > 0) {
                goto done;
            }
        }

        global = (u8 *)&D_80083460;
        ((S_8017382C_5 *)global)->unk_0A--;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~0x200;
        ((S_8017382C_0 *)arg0)->unk_8C = D_80170F6C;
        ((Rec_func_800AA258_arg2 *)arg2)->unk_12 = ((S_8017382C_0 *)arg0)->unk_AE;
    }

done:
    return;
}
