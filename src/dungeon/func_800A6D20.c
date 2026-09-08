#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800A2B04();              /* extern */
s16 func_800BCB04();                   /* extern */
extern s32 D_80083460[3];

typedef struct S_800AC480_0 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
} S_800AC480_0;   /* arg0 in func_800AC480 */

typedef struct S_800AC480_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AC480_1;   /* arg2 in func_800AC480 */


typedef struct S_800AC480_3 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_800AC480_3;   /* arg3 in func_800AC480 */

typedef struct S_800AC480_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC480_4;   /* global_base in func_800AC480 */

/* Update movement toward the target tile and finalize position and height when the timer expires. */
s32 func_800AC480(S_800AC480_0 *move_state, Rec_D_800E3D7C *motion, S_800AC480_1 *target_tile, S_800AC480_3 *height_state) {
    s32 delta;
    s32 coord;
    s32 *global_base;
    s32 x_step;
    s16 ticks_left;
    s16 next_ticks;
    s16 target_height;

    ticks_left = move_state->unk_96;
    if (ticks_left != 0) {
        delta = target_tile->unk_24 << 6;
        coord = motion->unk_00.at02_s16.v;
        coord -= 0x20;
        delta -= coord;
        x_step = (delta << 0x10) / ticks_left;
        coord = motion->unk_04.at02_s16.v;
        motion->unk_0C.as_s32 = x_step;
        delta = target_tile->unk_25 << 6;
        coord -= 0x20;
        delta -= coord;
        motion->unk_10.at00_s32.v = (delta << 0x10) / (s16) move_state->unk_96;
    }
    next_ticks = (u16) move_state->unk_96 - 1;
    move_state->unk_96 = next_ticks;
    if ((next_ticks << 0x10) <= 0) {
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, target_tile->unk_24, target_tile->unk_25);
        target_height = func_800BCB04((target_tile->unk_24 << 6) | 0x20, (target_tile->unk_25 << 6) | 0x20, (s16) (height_state->unk_88 - 0x20));
        if (target_height < 0x200) {
            move_state->unk_92 = (u16) (move_state->unk_92 + (height_state->unk_88 - target_height));
            height_state->unk_88 = (u16) target_height;
        }
        global_base = D_80083460;
        ASM_KEEP(global_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_800AC480_4 *)global_base)->unk_0A = (u16) (((S_800AC480_4 *)global_base)->unk_0A - 1);
        return 1;
    }
    return 0;
}

/* MECHANISM: Explicit s32 delta/coord/x_step lifetimes preserve each coord-0x20
   subtraction and hoist the second lh into the first division's load-delay gap.
   Direct 0/1 returns plus a kept absolute D_80083460 base produce the retail
   v0 delay-slot value and a0-based lhu/sh tail without changing the 0x20 frame. */
