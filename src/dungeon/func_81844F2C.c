#include "common.h"

typedef struct S_81844F2C_0_pre {
    u16 unk_00;
} S_81844F2C_0_pre;   /* the 0x2 bytes before base in func_8002472C, addressed as base[-1] */

typedef struct S_81844F2C_0 {
    void * unk_00;
    u16 unk_04;
    union { u16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x1A];
    union { u16 s; u16 u; s16 p; } unk_2A;   /* accessed as both */
    union { volatile u16 s; s16 u; u16 p; } unk_2C;   /* accessed as both */
} S_81844F2C_0;   /* base in func_8002472C */

typedef struct S_81844F2C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_81844F2C_1;   /* entity in func_8002472C */

typedef struct S_81844F2C_2 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_81844F2C_2;   /* base + (call_a0 * 4) in func_8002472C */

typedef struct S_81844F2C_3 {
    u8 pad_00[0x14];
    volatile u32 unk_14;
} S_81844F2C_3;   /* cursor in func_8002472C */

typedef struct S_81844F2C_4 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_81844F2C_4;   /* page in func_8002472C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Updates an effect_base's position, colors, countdown, and completion flags. */
void func_8002472C(s32 effect) {
    u8 *effect_base;   /* SITE-FOR-PIN TRADE 2026-09-22: the
                                            `func_80024808(effect, effect_base, saved_state)`
                                            tail pseudo-call is gone; its argument setup was the
                                            only thing putting the struct pointer in $a1.  Without
                                            it gcc keeps the parameter in $a0, the `move $a1,$a0`
                                            never appears and every colour in the row shifts
                                            (residue: 78/79 words, 35 subs + 1 indel). */
    u8 *color_cursor;
    u16 saved_state;
    u32 position;
    u32 step;
    s32 state;
    u32 color_delta;
    u8 *flag_page;

    ASM_KEEP(effect);
    effect_base = (u8 *)effect;
    flag_page = ((S_81844F2C_0 *)effect_base)->unk_00;
    ((S_81844F2C_1 *)flag_page)->unk_52 =
        (u16)(((S_81844F2C_1 *)flag_page)->unk_52 | 0x8000);

    position = ((S_81844F2C_0 *)effect_base)->unk_04;
    step = ((S_81844F2C_0 *)effect_base)->unk_0C;
    effect = ((S_81844F2C_0 *)effect_base)->unk_2A.s;
    position += step;
    ((S_81844F2C_0 *)effect_base)->unk_04 = (u16)position;
    position = ((S_81844F2C_0 *)effect_base)->unk_06.s;
    step = ((S_81844F2C_0 *)effect_base)->unk_0E;
    saved_state = ((S_81844F2C_0 *)effect_base)->unk_2C.s;
    position += step;
    state = ((S_81844F2C_0 *)effect_base)->unk_2C.u;
    effect -= 1;
    ((S_81844F2C_0 *)effect_base)->unk_2A.u = (u16)effect;
    ((S_81844F2C_0 *)effect_base)->unk_06.u = (u16)position;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2_done;
    }
    return;

state_0:
    effect = 7 - (s16)effect;
    if (effect < 5) {
        ((S_81844F2C_2 *)(effect_base + (effect * 4)))->unk_14 = 0x00808080;
    } else {
        effect = 4;
        color_delta = 0xFFDFDFE0;
        color_cursor = effect_base + 0x10;
        do {
            effect -= 1;
            ((S_81844F2C_3 *)color_cursor)->unk_14 += color_delta;
            color_cursor -= 4;
        } while (effect >= 0);
    }

    if (((S_81844F2C_0 *)effect_base)->unk_2A.p > 0) {
        return;
    }
    ((S_81844F2C_0 *)effect_base)->unk_2A.s = 3;
    ((S_81844F2C_0 *)effect_base)->unk_2C.p += 1;
    return;

state_1:
    if ((effect << 16) > 0) {
        return;
    }
    position = saved_state + 1;
    ((S_81844F2C_0 *)effect_base)->unk_2C.p = (u16)position;
    return;

state_2_done:
    flag_page = (u8 *)0x80080000;
    ((S_81844F2C_0_pre *)effect_base)[-1].unk_00 =
        (u16)(((S_81844F2C_0_pre *)effect_base)[-1].unk_00 | 0x8000);
    ((S_81844F2C_4 *)flag_page)->unk_14A0 |= 0x8000;
}
