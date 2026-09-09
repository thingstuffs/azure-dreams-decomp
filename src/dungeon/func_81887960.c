#include "common.h"

typedef struct S_80025160_0_pre {
    u16 unk_00;
} S_80025160_0_pre;   /* the 0x2 bytes before arg0 in func_80025160, addressed as arg0[-1] */

typedef struct S_80025160_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xA];
    s16 unk_16;
    union { volatile u16 s; u16 u; s16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    union { volatile u16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80025160_0;   /* arg0 in func_80025160 */

typedef struct S_80025160_1 {
    u8 pad_00[0x6];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80025160_1;   /* arg2 in func_80025160 */

typedef struct S_80025160_2 {
    u8 pad_00[0x6328];
    s16 unk_6328;
} S_80025160_2;   /* flag_page in func_80025160 */

typedef struct S_80025160_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80025160_3;   /* flags_page in func_80025160 */


#define COUNTER D_80026326.counter

typedef struct Global26326 {
    u16 counter;
    s16 flag;
    u16 unused[3];
} Global26326;

typedef struct Global26328 {
    s16 flag;
    u16 unused[4];
} Global26328;

typedef struct Global814A0 {
    s32 flags;
    s32 unused[2];
} Global814A0;

extern void func_8002569C(s32, s32, s32, s32, void *);
extern u8 D_80020000[0x10000];
extern Global26326 D_80026326;
extern Global26328 D_80026328;
extern Global814A0 D_800814A0;

/* Advances the effect state, updates its motion, and sets its display color. */
void func_80025160(void *effect, s32 context, S_80025160_1 *visual) {
    s16 state;
    s32 one;
    u16 value;
    u16 angle;
    u16 damped_value;
    s32 effect_param;
    s32 angle_shifted;
    void *owner;
    u8 *flag_page;
    u8 *flags_page;

    one = 1;
    COUNTER = COUNTER + 1;
    state = ((S_80025160_0 *)effect)->unk_0A.s;

    if (state == one) {
        goto state_1;
    }
    value = state < 2;
    if (value == 0) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    visual->unk_0C = 0x20;
    goto set_remaining_colors;

state_ge_2:
    value = 2;
    if (state == value) {
        goto state_2;
    }
    value = 3;
    if (state == value) {
        goto state_3;
    }
    visual->unk_0C = 0x20;
    goto set_remaining_colors;

state_0:
    value = visual->unk_06.s + 0x80;
    visual->unk_06.s = value;
    if ((s16)value <= 0x100) {
        goto set_colors;
    }
    visual->unk_06.s = 0x100;
    if (((S_80025160_0 *)effect)->unk_22 < 0x61) {
        damped_value = ((S_80025160_0 *)effect)->unk_18.s;
        angle = ((S_80025160_0 *)effect)->unk_1C.s;
        effect_param = ((S_80025160_0 *)effect)->unk_16;
        damped_value = damped_value - ((s32)(damped_value << 16) >> 19);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle = angle + 0x80;
        owner = (u8 *)effect - 0x20;
        ((S_80025160_0 *)effect)->unk_1C.u = angle;
        angle_shifted = angle << 16;
        ((S_80025160_0 *)effect)->unk_18.u = damped_value;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_8002569C(context, effect_param, ((S_80025160_0 *)effect)->unk_18.p,
                     angle_shifted >> 16, owner);
    }
    ((S_80025160_0 *)effect)->unk_0A.u++;
    if (((S_80025160_0 *)effect)->unk_22 == 0x6F) {
        D_80026328.flag = one;
        goto set_colors;
    }
    goto set_colors;

state_1:
    flag_page = (u8 *)0x80020000;
    if (((S_80025160_2 *)flag_page)->unk_6328 == 0) {
        goto state_1_zero;
    }
    visual->unk_06.u = -0x100;
    ((S_80025160_0 *)effect)->unk_1A = 0x10;
    ((S_80025160_0 *)effect)->unk_0A.u++;
    goto set_colors;

state_2:
    value = ((S_80025160_0 *)effect)->unk_1A - 1;
    ((S_80025160_0 *)effect)->unk_1A = value;
    if ((value << 16) > 0) {
        goto set_colors;
    }
    ((S_80025160_0 *)effect)->unk_0A.u++;

state_3:
    value = visual->unk_06.s + 0x80;
    visual->unk_06.s = value;
    if ((value << 16) >= 0) {
        flags_page = (u8 *)0x80080000;
        ((S_80025160_0_pre *)effect)[-1].unk_00 |= 0x8000;
        ((S_80025160_3 *)flags_page)->unk_14A0 |= 0x8000;
    }

state_1_zero:
set_colors:
    visual->unk_0C = 0x20;
set_remaining_colors:
    visual->unk_0D = 0x40;
    visual->unk_0E = 0xE0;
}
