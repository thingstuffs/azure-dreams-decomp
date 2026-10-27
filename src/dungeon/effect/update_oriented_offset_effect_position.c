#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800B328C_0_pre {
    u16 unk_00;
} S_800B328C_0_pre;   /* the 0x2 bytes before arg0 in update_oriented_offset_effect_position, addressed as arg0[-1] */

typedef struct S_800B328C_0 {
    void * unk_00;
    s32 unk_04;
    u8 pad_08[0x84];
    s16 unk_8C;
    u16 unk_8E;
} S_800B328C_0;   /* arg0 in update_oriented_offset_effect_position */

   /* arg1 in update_oriented_offset_effect_position */



typedef struct S_800B328C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B328C_4;   /* ((S_800B328C_0 *)arg0)->unk_00 in update_oriented_offset_effect_position */


void create_attenuating_moving_effect(); /* extern */

/* Update the position from a base and offset, and mark completion or timeout. */
void update_oriented_offset_effect_position(void *state, MovingPosition *position) {
    GteShortVector offset;
    u16 new_position[3];
    s16 old_x;
    s16 old_y;
    s32 old_z_shifted;
    u16 new_x;
    u16 new_y;
    u16 new_z;
    u16 ticks_left;
    MovingPosition *base_position;
    SpriteFrameState *offset_source;

    offset_source = ((S_800B328C_4 *)(((S_800B328C_0 *)state)->unk_00))->unk_0C;
    if (resolve_record_orientation_or_fallback(offset_source->source, offset_source, &offset, 0) != 0) {
        base_position = ((S_800B328C_4 *)(((S_800B328C_0 *)state)->unk_00))->unk_08;
        if (((S_800B328C_0 *)state)->unk_8C != 0) {
            old_x = (s16) position->x;
            old_y = (s16) position->y;
            old_z_shifted = position->z << 0x10;
            new_x = base_position->x + ((u16)offset.vx);
            position->x = new_x;
            new_position[0] = new_x;
            new_y = base_position->y + ((u16)offset.vy);
            position->y = new_y;
            new_position[1] = new_y;
            new_z = base_position->z + ((u16)offset.vz);
            position->z = new_z;
            new_position[2] = new_z;
            create_attenuating_moving_effect(((S_800B328C_0 *)state)->unk_00, old_x, old_y, old_z_shifted >> 0x10, new_position,
                ((S_800B328C_0 *)state)->unk_04, 2, 0x800, 1);
        } else {
            position->x = (u16) (base_position->x + ((u16)offset.vx));
            position->y = (u16) (base_position->y + ((u16)offset.vy));
            position->z = (u16) (base_position->z + ((u16)offset.vz));
            ((S_800B328C_0 *)state)->unk_8C = 1;
        }
    } else if (((S_800B328C_0 *)state)->unk_8C != 0) {
        (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800B328C_0_pre *)state)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    if (ticks_left = ((S_800B328C_0 *)state)->unk_8E - 1, ((S_800B328C_0 *)state)->unk_8E = ticks_left,
        ((s16) ticks_left < 0)) {
        (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800B328C_0_pre *)state)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
