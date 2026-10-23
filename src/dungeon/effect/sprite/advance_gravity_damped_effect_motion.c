#include "common.h"
#include "dungeon/effect/sprite.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80921A44_2_pre {
    u16 unk_00;
} S_80921A44_2_pre;   /* the 0x2 bytes before arg0 in func_80921A44, addressed as arg0[-1] */

/* cfail-repair: tf7-phase1-cache-v3 */
extern void advance_sprite_animation_and_textures(void *, void *, s32, s32);
/* Advance position, damp horizontal motion, and propagate object status flags. */
void advance_damped_animated_sprite(void *entry, ObjectPosition *motion, SpriteFrameState *object) {
    s32 velocity_y;
    s32 velocity_x;

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += 0xFFFE8000;
    velocity_x = motion->velocity_x;
    velocity_y = motion->velocity_y;
    motion->velocity_x = (velocity_x * 4) / 5;
    motion->velocity_y = (velocity_y * 4) / 5;
    advance_sprite_animation_and_textures(object, motion, (s32) (velocity_y * 4) >> 0x1F, (s32) (velocity_x * 4) >> 0x1F);
    if (object->flags & 0x6000) {
        (*(u16 *)((u8 *)entry + -2)) = (u16) (((S_80921A44_2_pre *)entry)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
