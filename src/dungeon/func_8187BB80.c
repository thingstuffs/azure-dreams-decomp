#include "common.h"

typedef struct S_8187BB80_0 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x1A];
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x8];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x7];
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; } unk_40;   /* overlapping accesses */
    u8 pad_44[0x8];
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 pad_50[0x8];
    s16 unk_58;
    u16 unk_5A;
    u8 pad_5C[0x2];
    u16 unk_5E;
    s16 unk_60;
    u16 unk_62;
    u8 pad_64[0x2];
    u16 unk_66;
} S_8187BB80_0;   /* obj in func_8187BB80 */

typedef struct S_8187BB80_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_8187BB80_1;   /* aux in func_8187BB80 */



extern s16 D_8002694C;
extern s32 D_800814A0;
extern void *D_80024038[];

extern void func_80025560(void) __attribute__((noreturn));
extern void func_800255AC(void) __attribute__((noreturn));

/* Advance the effect animation, fade its colors, and mark it for removal when its lifetime ends. */
void func_8187BB80(void *effect_data, s32 unused_arg, void *color_data) {
    u8 *colors = color_data;
    register s32 tick_limit;
    s32 phase_state;

    D_8002694C = 1;
    ((S_8187BB80_0 *)effect_data)->unk_02.u--;

    if (((S_8187BB80_0 *)effect_data)->unk_40.at00.v == 0) {
        s32 mid_y;
        u16 mid_x;

        ((S_8187BB80_0 *)effect_data)->unk_20.s =
            (((S_8187BB80_0 *)effect_data)->unk_1E.s + ((S_8187BB80_0 *)effect_data)->unk_58) / 2;
        mid_y = (((S_8187BB80_0 *)effect_data)->unk_2A.s + ((S_8187BB80_0 *)effect_data)->unk_60) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_2C.s = mid_y;
        mid_x = *(volatile u16 *)(effect_data + 0x20);
        ((S_8187BB80_0 *)effect_data)->unk_66 = mid_y;
        ((S_8187BB80_0 *)effect_data)->unk_62 = mid_y;
        ((S_8187BB80_0 *)effect_data)->unk_5E = mid_x;
        ((S_8187BB80_0 *)effect_data)->unk_5A = mid_x;
    }

    phase_state = ((S_8187BB80_0 *)effect_data)->unk_40.at00.v;
    tick_limit = 1;
    if (phase_state == tick_limit) {
        ((S_8187BB80_0 *)effect_data)->unk_20.s =
            (((S_8187BB80_0 *)effect_data)->unk_1E.s + ((S_8187BB80_0 *)effect_data)->unk_58) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_20.s =
            (((S_8187BB80_0 *)effect_data)->unk_1E.s + ((S_8187BB80_0 *)effect_data)->unk_20.s) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_2C.s =
            (((S_8187BB80_0 *)effect_data)->unk_2A.s + ((S_8187BB80_0 *)effect_data)->unk_60) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_2C.s =
            (((S_8187BB80_0 *)effect_data)->unk_2A.s + ((S_8187BB80_0 *)effect_data)->unk_2C.s) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_5A = ((S_8187BB80_0 *)effect_data)->unk_5E =
            ((S_8187BB80_0 *)effect_data)->unk_20.u;
        ((S_8187BB80_0 *)effect_data)->unk_62 = ((S_8187BB80_0 *)effect_data)->unk_66 =
            ((S_8187BB80_0 *)effect_data)->unk_2C.u;
    }

    if (*(volatile s32 *)(effect_data + 0x40) == 0x10000) {
        u32 start_x = ((S_8187BB80_0 *)effect_data)->unk_1E.u;
        u32 start_y = ((S_8187BB80_0 *)effect_data)->unk_2A.u;

        ((S_8187BB80_0 *)effect_data)->unk_5E = start_x;
        ((S_8187BB80_0 *)effect_data)->unk_5A = start_x;
        ((S_8187BB80_0 *)effect_data)->unk_66 = start_y;
        ((S_8187BB80_0 *)effect_data)->unk_62 = start_y;
    }

    if (((S_8187BB80_0 *)effect_data)->unk_40.at00u.v == tick_limit) {
        s32 phase;
        static void *const phase_labels[] = {
            &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
            &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8
        };

        (void)phase_labels;
        ((S_8187BB80_0 *)effect_data)->unk_40.at00u.v = 0;
        phase = ((S_8187BB80_0 *)effect_data)->unk_40.at02.v;
        if ((u32)phase >= 9) {
            goto jt_c8;
        }
        goto *D_80024038[(u32)phase];

jt_c0:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 1;
        return func_800255AC();

jt_c1: {
            u32 phase_value = ((S_8187BB80_0 *)effect_data)->unk_4C;
            s32 next_phase = 2;
            ASM_KEEP(phase_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(next_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_80025560();
        }

jt_c2: {
            u32 phase_value = ((S_8187BB80_0 *)effect_data)->unk_4C;
            s32 next_phase = 3;
            ASM_KEEP(phase_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(next_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_80025560();
        }

jt_c3: {
            u32 phase_value = ((S_8187BB80_0 *)effect_data)->unk_4C;
            s32 next_phase = 4;
            ASM_KEEP(phase_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(next_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_80025560();
        }

jt_c4:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 5;
        ((S_8187BB80_0 *)effect_data)->unk_4C = 0x80;
        ((S_8187BB80_0 *)effect_data)->unk_4D += 0x20;
        return func_800255AC();

jt_c5: {
            u32 phase_value = ((S_8187BB80_0 *)effect_data)->unk_4C;
            s32 next_phase = 6;
            ASM_KEEP(phase_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(next_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_80025560();
        }

jt_c6:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 7;
        ((S_8187BB80_0 *)effect_data)->unk_4C += 0x20;
        return func_800255AC();

jt_c7:
        ((S_8187BB80_0 *)effect_data)->unk_4E = 0;
        ((S_8187BB80_0 *)effect_data)->unk_4F = 0;
        ((S_8187BB80_1 *)colors)->unk_0D = 0xFF;
        ((S_8187BB80_1 *)colors)->unk_0C = 0xFF;
        ((S_8187BB80_1 *)colors)->unk_0E = 0;
        ((S_8187BB80_0 *)effect_data)->unk_37 = 0xFF;
        ((S_8187BB80_0 *)effect_data)->unk_36 = 0xFF;
        ((S_8187BB80_0 *)effect_data)->unk_38 = 0;
        ((S_8187BB80_1 *)colors)->unk_14 |= 0xC;
        return func_800255AC();
    } else {
        ((S_8187BB80_0 *)effect_data)->unk_40.at00p.v++;
    }

jt_c8:
    if (((S_8187BB80_0 *)effect_data)->unk_02.s < 30) {
        ((S_8187BB80_1 *)colors)->unk_0C =
            (((S_8187BB80_0 *)effect_data)->unk_36 * ((S_8187BB80_0 *)effect_data)->unk_02.s) / 30;
        ((S_8187BB80_1 *)colors)->unk_0D =
            (((S_8187BB80_0 *)effect_data)->unk_37 * ((S_8187BB80_0 *)effect_data)->unk_02.s) / 30;
        ((S_8187BB80_1 *)colors)->unk_0E =
            (((S_8187BB80_0 *)effect_data)->unk_38 * ((S_8187BB80_0 *)effect_data)->unk_02.s) / 30;
    }

    if (((S_8187BB80_0 *)effect_data)->unk_02.s <= 0) {
        (*(u16 *)((u8 *)effect_data + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
