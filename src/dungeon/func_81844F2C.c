#include "common.h"

typedef struct S_81844F2C_0_pre {
    u16 unk_00;
} S_81844F2C_0_pre;   /* the 0x2 bytes before base in func_8002472C, addressed as base[-1] */

typedef struct S_81844F2C_0 {
    void * unk_00;
    u16 unk_04;
    union { u16 s; volatile u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x1A];
    union { u16 s; volatile u16 u; s16 p; } unk_2A;   /* accessed as both */
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
    volatile u32 unk_14A0;
} S_81844F2C_4;   /* page in func_8002472C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Updates an effect's position, colors, countdown, and completion flags. */
void func_8002472C(void *effect_data) {
    register u8 *effect ASM_REG("$5");   /* SITE-FOR-PIN TRADE 2026-09-22: the
                                            `func_80024808(tick_or_index, effect, saved_state)`
                                            tail pseudo-call is gone; its argument setup was the
                                            only thing putting the struct pointer in $a1.  Without
                                            it gcc keeps the parameter in $a0, the `move $a1,$a0`
                                            never appears and every colour in the row shifts
                                            (residue: 78/79 words, 35 subs + 1 indel). */
    u8 *color_cursor;
    register s32 tick_or_index;
    register u32 saved_state ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u32 position;
    u32 step;
    s32 state;
    u32 color_delta;
    S_81844F2C_1 *entity;
    u8 *flag_page;

    effect = effect_data;
    ASM_KEEP(effect);   /* SITE-FOR-PIN TRADE 2026-09-22: pins the copy in place.  With the
                           pseudo-call gone gcc copy-propagates `effect_data` into the first
                           load and sinks the `move $a1,$a0` six words down, below the entity
                           update (words 0-6).  ASM_REG("$5") alone was only measured on a
                           different spelling of the `state >= 2` block, so no clean one-pin
                           number exists for this text. */
    entity = ((S_81844F2C_0 *)effect)->unk_00;
    entity->unk_52 =
        (u16)(entity->unk_52 | 0x8000);

    position = ((S_81844F2C_0 *)effect)->unk_04;
    step = ((S_81844F2C_0 *)effect)->unk_0C;
    tick_or_index = ((S_81844F2C_0 *)effect)->unk_2A.s;
    position += step;
    ((S_81844F2C_0 *)effect)->unk_04 = (u16)position;
    position = ((S_81844F2C_0 *)effect)->unk_06.s;
    step = ((S_81844F2C_0 *)effect)->unk_0E;
    saved_state = ((S_81844F2C_0 *)effect)->unk_2C.s;
    position += step;
    state = ((S_81844F2C_0 *)effect)->unk_2C.u;
    ASM_KEEP(tick_or_index);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    tick_or_index -= 1;
    ((S_81844F2C_0 *)effect)->unk_2A.u = (u16)tick_or_index;
    ((S_81844F2C_0 *)effect)->unk_06.u = (u16)position;

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_at_least_2;
    }
    if (state == 0) {
        goto state_0;
    }
    return;

state_at_least_2:
    if (state == 2) {
        goto state_2_done;
    }
    return;

state_0:
    tick_or_index = 7 - (s16)tick_or_index;
    if (tick_or_index < 5) {
        ((S_81844F2C_2 *)(effect + (tick_or_index * 4)))->unk_14 = 0x00808080;
    } else {
        tick_or_index = 4;
        color_delta = 0xFFDFDFE0;
        color_cursor = effect + 0x10;
        do {
            tick_or_index -= 1;
            ((S_81844F2C_3 *)color_cursor)->unk_14 += color_delta;
            color_cursor -= 4;
        } while (tick_or_index >= 0);
    }

    if (((S_81844F2C_0 *)effect)->unk_2A.p > 0) {
        return;
    }
    ((S_81844F2C_0 *)effect)->unk_2A.s = 3;
    ((S_81844F2C_0 *)effect)->unk_2C.p += 1;
    return;

state_1:
    if ((tick_or_index << 16) > 0) {
        return;
    }
    position = saved_state + 1;
    ((S_81844F2C_0 *)effect)->unk_2C.p = (u16)position;
    return;

state_2_done:
    flag_page = (u8 *)0x80080000;
    ((S_81844F2C_0_pre *)effect)[-1].unk_00 =
        (u16)(((S_81844F2C_0_pre *)effect)[-1].unk_00 | 0x8000);
    ((S_81844F2C_4 *)flag_page)->unk_14A0 |= 0x8000;
}
