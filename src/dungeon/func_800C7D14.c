#include "common.h"

typedef struct S_800CD474_0_pre {
    u16 unk_00;
} S_800CD474_0_pre;   /* the 0x2 bytes before arg0 in func_800CD474, addressed as arg0[-1] */

typedef struct S_800CD474_0 {
    s32 unk_00;
    s16 unk_04;
    u16 unk_06;
    s16 unk_08;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
} S_800CD474_0;   /* arg0 in func_800CD474 */

typedef struct S_800CD474_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CD474_1;   /* arg1 in func_800CD474 */

typedef struct S_800CD474_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_800CD474_2;   /* arg2 in func_800CD474 */

typedef struct S_800CD474_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CD474_3;   /* global_base in func_800CD474 */



extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s32 func_800CD6AC();
extern s32 D_800814A0;
extern s32 D_80083460;

/* Advance a falling effect through impact, flashing, and fade-out. */
void func_800CD474(void *effect, S_800CD474_1 *motion, S_800CD474_2 *primitive) {
    s16 state;
    s32 color;
    u16 sound_timer;
    u16 hold_timer;
    u16 fade_timer;
    u16 target_y;
    s32 *effect_counts;

    state = ((S_800CD474_0 *)effect)->unk_04;
    if (state == 0) {
        motion->unk_14 += 0x20000;
        sound_timer = ((S_800CD474_0 *)effect)->unk_06 - 1;
        ((S_800CD474_0 *)effect)->unk_06 = sound_timer;
        if ((sound_timer << 16) == 0) {
            func_800A56E0(0x701);
        }
        if ((motion->unk_08.at02.v + 0x10) >= ((S_800CD474_0 *)effect)->unk_0A.s) {
            func_800419EC(8, 8);
            target_y = ((S_800CD474_0 *)effect)->unk_0A.u;
            motion->unk_14 = 0;
            motion->unk_08.at02.v = target_y;
            ((S_800CD474_0 *)effect)->unk_06 = 8;
            ((S_800CD474_0 *)effect)->unk_04 = (u16)((S_800CD474_0 *)effect)->unk_04 + 1;
            func_800A56E0(0x612);
        }
        color = 0x404040;
        if (((S_800CD474_0 *)effect)->unk_0C & 1) {
            color = 0x808080;
        }
        primitive->unk_0C.at00.v = color;
    } else if (state == 1) {
        color = 0x404040;
        if (((S_800CD474_0 *)effect)->unk_0C & 1) {
            color = 0x808080;
        }
        primitive->unk_0C.at00.v = color;
        hold_timer = ((S_800CD474_0 *)effect)->unk_06 - 1;
        ((S_800CD474_0 *)effect)->unk_06 = hold_timer;
        if ((hold_timer << 16) <= 0) {
            ((S_800CD474_0 *)effect)->unk_06 = 0x10;
            primitive->unk_0C.at00.v = 0x808080;
            ((S_800CD474_0 *)effect)->unk_04 = (u16)((S_800CD474_0 *)effect)->unk_04 + 1;
            if (((S_800CD474_0 *)effect)->unk_08 == 0) {
                func_800CD6AC(((S_800CD474_0 *)effect)->unk_00, 0x10);
            }
        }
    } else {
        primitive->unk_0C.at00u.v = primitive->unk_0C.at00u.v -
                               (primitive->unk_0C.at00u.v / (s16)((S_800CD474_0 *)effect)->unk_06);
        primitive->unk_0C.at01.v = primitive->unk_0C.at01.v -
                               (primitive->unk_0C.at01.v / (s16)((S_800CD474_0 *)effect)->unk_06);
        primitive->unk_0C.at02.v = primitive->unk_0C.at02.v -
                               (primitive->unk_0C.at02.v / (s16)((S_800CD474_0 *)effect)->unk_06);
        fade_timer = ((S_800CD474_0 *)effect)->unk_06 - 1;
        ((S_800CD474_0 *)effect)->unk_06 = fade_timer;
        if ((fade_timer << 16) <= 0) {
            ((S_800CD474_0_pre *)effect)[-1].unk_00 |= 0x8000;
            D_800814A0 |= 0x8000;
            effect_counts = &D_80083460;
            ((S_800CD474_3 *)effect_counts)->unk_0A -= 1;
        }
    }
    motion->unk_08.at00.v += motion->unk_14;
    ((S_800CD474_0 *)effect)->unk_0C += 1;
}
