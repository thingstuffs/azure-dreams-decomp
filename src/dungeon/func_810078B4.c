#include "common.h"

typedef struct S_801730B4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801730B4_0;   /* arg0 in func_801730B4 */

typedef struct S_801730B4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801730B4_1;   /* arg2 in func_801730B4 */

typedef struct S_801730B4_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801730B4_2;   /* arg3 in func_801730B4 */

typedef struct S_801730B4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801730B4_3;   /* counter_base in func_801730B4 */

typedef struct S_801730B4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801730B4_4;   /* global_base in func_801730B4 */

typedef struct S_801730B4_5 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x12];
    u16 unk_A6;
    u8 pad_A8[0xA];
    u16 unk_B2;
} S_801730B4_5;   /* copy_arg0 in func_801730B4 */

typedef struct S_801730B4_6 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801730B4_6;   /* owner in func_801730B4 */

typedef struct S_801730B4_7 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_801730B4_7;   /* origin in func_801730B4 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173834(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171058[];
extern u8 D_801748E0[];
extern u8 D_801748E8[];

void func_801730B4(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    void *arg0 = in_arg0;
    void *arg1 = in_arg1;
    void *arg2 = in_arg2;
    void *arg3 = in_arg3;
    s32 flags;
    u16 current_value;
    u16 old_value;
    register u8 *page_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *global_base ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 state;

    state = ((S_801730B4_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((S_801730B4_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_801748E0;
    func_80047784(arg2,
        D_801748E0[((D_80083228 + ((S_801730B4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;
        u16 counter_value;

        counter_value = ((S_801730B4_3 *)counter_base)->unk_0A;
        counter_value--;
        ((S_801730B4_3 *)counter_base)->unk_0A = counter_value;
    }
    goto increment_state;

state_one:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        page_base = (u8 *)0x80080000;
        goto state_one_active;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_801748E8;
    func_80047784(arg2,
        D_801748E8[((D_80083228 + ((S_801730B4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801730B4_2 *)arg3)->unk_1C.s |= 0x40000;
    if (!(((S_801730B4_1 *)arg2)->unk_14 & 0x8000)) {
        goto increment_counter;
    }
    ((S_801730B4_2 *)arg3)->unk_1C.s &= ~0x200;
    goto assign_callback;

state_one_active:
    ASM_KEEP(page_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    global_base = page_base + 0x3460;
    {
        if (((S_801730B4_4 *)global_base)->unk_02 & 0x1000) {
            goto done;
        }
        if (((S_801730B4_2 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }
        if (((S_801730B4_2 *)arg3)->unk_25 == 0) {
            if (((S_801730B4_4 *)global_base)->unk_02 & 0x2008) {
                goto done;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }
        flags = ((S_801730B4_2 *)arg3)->unk_1C.u;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }
        if (flags & 0x80000) {
            void *copy_arg0;

            func_800AA888(arg0, arg1, arg2, arg3);
            copy_arg0 = arg0;
            ASM_KEEP(copy_arg0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            current_value = ((S_801730B4_5 *)copy_arg0)->unk_92;
            old_value = ((S_801730B4_5 *)copy_arg0)->unk_A6;
            ((S_801730B4_5 *)copy_arg0)->unk_A6 = 0;
            ((S_801730B4_5 *)copy_arg0)->unk_B2 = 0;
            ((S_801730B4_5 *)copy_arg0)->unk_92 = current_value - old_value;
            func_80173834(copy_arg0, arg1, arg2, arg3);
            goto done;
        }
        if (((S_801730B4_2 *)arg3)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            void *owner = D_800814A8;

            if ((func_8009A180(arg3,
                    (u8 *)((S_801730B4_6 *)owner)->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }
        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin = D_80082E80;
            s8 tile = ((S_801730B4_1 *)arg2)->unk_26;

            if (((tile == ((S_801730B4_7 *)origin)->unk_26) && (tile >= 0)) ||
                ((s16)func_8009FD40(origin, arg2) < 2)) {
                if (!(func_800A6D30() & 7)) {
                    func_80042B68(arg3, 1);
                }
            }
        }
        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto done;
        }
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_801748E8;
    func_80047784(arg2,
        D_801748E8[((D_80083228 + ((S_801730B4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    {
        u32 late_flags;

        late_flags = ((S_801730B4_2 *)arg3)->unk_1C.s;
        late_flags |= 0x40000;
        ((S_801730B4_2 *)arg3)->unk_1C.s = late_flags;
    }
    if (((S_801730B4_1 *)arg2)->unk_14 & 0x8000) {
        ((S_801730B4_2 *)arg3)->unk_1C.u &= ~0x200;
        goto assign_callback;
    }

increment_counter:
    {
        u8 *counter_base = (u8 *)&D_80083460;
        register u16 counter_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        counter_value = ((S_801730B4_3 *)counter_base)->unk_0A;
        counter_value++;
        ((S_801730B4_3 *)counter_base)->unk_0A = counter_value;
    }

increment_state:
    ((S_801730B4_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    if (!(((S_801730B4_1 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base = (u8 *)&D_80083460;

        ((S_801730B4_3 *)counter_base)->unk_0A--;
    }

clear_callback:
    ((S_801730B4_2 *)arg3)->unk_1C.u &= ~0x200;

assign_callback:
    ((S_801730B4_0 *)arg0)->unk_8C = D_80171058;

done:
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    return;
}
