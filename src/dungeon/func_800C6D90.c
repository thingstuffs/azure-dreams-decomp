#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_800CC4F0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_800CC4F0_0;   /* arg1 in update_directional_trap_effect */

typedef struct S_800CC4F0_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    s16 unk_06;
    s16 unk_08;
} S_800CC4F0_1;   /* arg0 in update_directional_trap_effect; pointer addresses record offset 0x2 */


s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern void * create_tile_center_quad_effect(s16 tile_x, s16 tile_y, s16 z, s16 tail_value, s16 render_mode, u16 tail_config);

/* Updates directional motion, emits paired effects, and marks completion when the timer expires. */
void update_directional_trap_effect(void *effect_data, S_800CC4F0_0 *position) {
    u16 ticks_left;

    position->unk_0E = (u16) (position->unk_0E + (func_80064584(((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06)
        >> 6));
    position->unk_12 = (u16) (position->unk_12 + (func_800644B8(((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06)
        >> 6));
    if (((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_08 == 0) {
        create_tile_center_quad_effect((u16) position->unk_02 >> 6, (u16) position->unk_06 >> 6, position->unk_0A,
            ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06, 0, 1);
        create_tile_center_quad_effect((u16) position->unk_02 >> 6, (u16) position->unk_06 >> 6, position->unk_0A,
            ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_06, 1, 1);
    }
    ticks_left = ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_04 - 1;
    ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800CC4F0_1 *)((u8 *)effect_data - 0x2))->unk_00 = (u16) (((S_800CC4F0_1 *)((u8 *)effect_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
