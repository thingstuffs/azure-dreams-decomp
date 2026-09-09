#include "common.h"
#include "m2c_compat.h"

typedef struct S_801671AC_0 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_801671AC_0;   /* arg2 in func_801671AC */

typedef struct S_801671AC_1_pre {
    u16 unk_00;
} S_801671AC_1_pre;   /* the 0x2 bytes before obj in func_801671AC, addressed as obj[-1] */

typedef struct S_801671AC_1 {
    u8 pad_00[0x18];
    u16 unk_18;
    u8 pad_1A[0x2];
    u16 unk_1C;
} S_801671AC_1;   /* obj in func_801671AC */


extern M2C_UNK D_800814A0;

/* Pulse the color through three phases and mark the effect finished when its timer expires. */
void func_801671AC(void *state_data, void *unused, void *color) {
    void *state;
    s16 phase;
    s16 remaining;
    s32 red;
    s32 green;
    s32 blue;
    u16 ticks_left;
    u16 flags;
    u16 next_phase;

    flags = ((S_801671AC_0 *)color)->unk_14;
    ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    state = state_data;
    ((S_801671AC_0 *)color)->unk_14 = (u16) (flags & 0xFF7F);
    ticks_left = ((S_801671AC_1 *)state)->unk_18;
    next_phase = ((S_801671AC_1 *)state)->unk_1C;
    ticks_left--;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    next_phase++;
    ((S_801671AC_1 *)state)->unk_1C = next_phase;
    ((S_801671AC_1 *)state)->unk_18 = ticks_left;
    if ((s16) next_phase == 3) {
        ((S_801671AC_1 *)state)->unk_1C = 0U;
    }
    blue = 0x30;
    green = blue;
    phase = (s16) ((S_801671AC_1 *)state)->unk_1C;
    red = 0x30;
    if (phase == 0) {
        red = 0x54;
    }
    if (phase == 1) {
        green = 0x54;
    }
    if (phase == 2) {
        blue = 0x54;
    }
    remaining = (s16) ((S_801671AC_1 *)state)->unk_18;
    if (remaining < 0x14) {
        ((S_801671AC_0 *)color)->unk_0C = (s8) ((red * remaining) / 20);
        ((S_801671AC_0 *)color)->unk_0D = (s8) ((green * (s16) ((S_801671AC_1 *)state)->unk_18) / 20);
        ((S_801671AC_0 *)color)->unk_0E = (s8) ((blue * (s16) ((S_801671AC_1 *)state)->unk_18) / 20);
    } else {
        ((S_801671AC_0 *)color)->unk_0C = (s8) ((red * (0x1E - remaining)) / 10);
        ((S_801671AC_0 *)color)->unk_0D = (s8) ((green * (0x1E - (s16) ((S_801671AC_1 *)state)->unk_18)) / 10);
        ((S_801671AC_0 *)color)->unk_0E = (s8) ((blue * (0x1E - (s16) ((S_801671AC_1 *)state)->unk_18)) / 10);
    }
    if ((s16) ((S_801671AC_1 *)state)->unk_18 <= 0) {
        (*(u16 *)((u8 *)state + -2)) = (u16) (((S_801671AC_1_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
