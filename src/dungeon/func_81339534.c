/* cfail-repair: recovered external dispatch table */
#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800419EC(s32, s32);
extern void func_800A56E0(u32);
extern void *jtbl_80164A38[];
__asm__(".set jtbl_80164A38, 0x80164A38");
extern s32 D_800814A0[3];
extern s16 D_801760D8[5];


typedef struct S_80170534_0_pre {
    u16 unk_00;
} S_80170534_0_pre;   /* the 0x2 bytes before state in func_80170534, addressed as state[-1] */

typedef struct S_80170534_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    u16 unk_18;
} S_80170534_0;   /* state in func_80170534 */

typedef struct S_80170534_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
} S_80170534_1;   /* input in func_80170534 */

/* Advances a timed blinking effect, triggers sounds, and sets completion flags. */
void func_80170534(void *state_data, void *unused, void *color_data) {
    static void *const state_labels[] = {
        &&state_end, &&state_1, &&state_2, &&state_end, &&state_4
    };
    void *state = state_data;
    void *colors;
    void * volatile *dispatch;
    s32 phase;
    s32 bright_shade;
    u16 dim_shade;
    u16 next_phase;
    u16 frame;
    u16 blink_frame;

    phase = ((S_80170534_0 *)state)->unk_12.s;
    if ((u32) phase >= 5) {
        goto state_end;
    }
    colors = color_data;
    ASM_KEEP(colors);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    dispatch = jtbl_80164A38;
    (void)state_labels;
    goto *dispatch[(u32) phase];

state_1:
    frame = ((S_80170534_0 *)state)->unk_18 + 1;
    ((S_80170534_0 *)state)->unk_18 = frame;
    if (!(frame & 3)) {
        func_800419EC(6, 0xC);
        func_800A56E0(0x818);
    }
    if (!(((S_80170534_0 *)state)->unk_18 & 7)) {
        bright_shade = 0xFF;
        if (((S_80170534_1 *)colors)->unk_0C != bright_shade) {
            ((S_80170534_1 *)colors)->unk_0E.s = bright_shade;
            ((S_80170534_1 *)colors)->unk_0D.s = bright_shade;
            ((S_80170534_1 *)colors)->unk_0C = bright_shade;
        } else {
            dim_shade = 0x80;
            ((S_80170534_1 *)colors)->unk_0E.u = dim_shade;
            ((S_80170534_1 *)colors)->unk_0D.u = dim_shade;
            ((S_80170534_1 *)colors)->unk_0C = dim_shade;
        }
    }
    if ((s16) ((S_80170534_0 *)state)->unk_18 == 0x28) {
#ifdef NON_MATCHING
        D_801760D8[0] = 1;
#else
        {
            u8 *flag_page = (u8 *) 0x80170000;
            *(u16 *)((u8 *)&D_801760D8) = 1;
        }
#endif
    }
    if ((s16) ((S_80170534_0 *)state)->unk_18 >= 0x28) {
        next_phase = ((S_80170534_0 *)state)->unk_12.u + 1;
        ((S_80170534_0 *)state)->unk_12.u = next_phase;
        return;
    }
    goto state_end;

state_2:
    blink_frame = ((S_80170534_0 *)state)->unk_18 + 1;
    ((S_80170534_0 *)state)->unk_18 = blink_frame;
    if (!(blink_frame & 3)) {
        func_800A56E0(0x818);
    }
    if (!(((S_80170534_0 *)state)->unk_18 & 7)) {
        bright_shade = 0xFF;
        if (((S_80170534_1 *)colors)->unk_0C != bright_shade) {
            ((S_80170534_1 *)colors)->unk_0E.s = bright_shade;
            ((S_80170534_1 *)colors)->unk_0D.s = bright_shade;
            ((S_80170534_1 *)colors)->unk_0C = bright_shade;
        } else {
            dim_shade = 0x80;
            ((S_80170534_1 *)colors)->unk_0E.u = dim_shade;
            ((S_80170534_1 *)colors)->unk_0D.u = dim_shade;
            ((S_80170534_1 *)colors)->unk_0C = dim_shade;
        }
    }
    if ((s16) ((S_80170534_0 *)state)->unk_18 >= 0x3C) {
        ((S_80170534_0 *)state)->unk_18 = 0U;
        ((S_80170534_0 *)state)->unk_12.s = (s16) ((u16) ((S_80170534_0 *)state)->unk_12.s + 1);
        ((S_80170534_1 *)colors)->unk_0E.u = 0x80;
        ((S_80170534_1 *)colors)->unk_0D.u = 0x80;
        ((S_80170534_1 *)colors)->unk_0C = 0x80;
        return;
    }
    goto state_end;

state_4:
    {
        u8 *flags_page;
        u16 flags = ((S_80170534_0_pre *)state)[-1].unk_00;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        flags_page = (u8 *) 0x80080000;
        ASM_KEEP(flags_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        flags = (u16) (flags | 0x8000);
        ((S_80170534_0_pre *)state)[-1].unk_00 = flags;
#ifdef NON_MATCHING
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
#else
        *(s32 *)(flags_page + 0x14A0) |= 0x8000;
#endif
    }

state_end:
    ;
}
