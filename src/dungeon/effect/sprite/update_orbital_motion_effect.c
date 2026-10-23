#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818BD3B0_0_pre {
    u16 flags; /* 0x00 */
} S_818BD3B0_0_pre;   /* the 0x2 bytes before arg0 in update_orbital_motion_effect, addressed as arg0[-1] */

typedef struct S_818BD3B0_0 {
    struct S_818BD3B0_1 * owner; /* 0x00 */
    u16 elapsed_ticks; /* 0x04 */
    s16 lifetime; /* 0x06 */
    s16 wave_offset; /* 0x08 */
    s16 orbit_scale; /* 0x0A */
    u16 angle; /* 0x0C */
} S_818BD3B0_0;   /* arg0 in update_orbital_motion_effect */

typedef struct S_818BD3B0_1 {
    u8 pad_00[0x14];
    u16 ticks; /* 0x14 */
} S_818BD3B0_1;

typedef struct S_818BD3B0_2 {
    s32 x; /* 0x00 */
    s32 y; /* 0x04 */
    s32 z; /* 0x08 */
    s32 center_x; /* 0x0C */
    s32 center_y; /* 0x10 */
    s32 center_z; /* 0x14 */
} S_818BD3B0_2;   /* arg1 in update_orbital_motion_effect */

s32 select_record_entry_and_value();
s32 advance_sprite_animation_and_textures();
s32 rsin();
s32 rcos();
extern M2C_UNK shared_sprite_entries[3];

/* Advance orbital motion, expire it at its duration, and update the object. */
void update_orbital_motion_effect(S_818BD3B0_0 *motion, S_818BD3B0_2 *position, SpriteFrameState *object) {
    s16 angle;
    s32 radius_product;
    s32 height_offset;
    u16 tick;
    S_818BD3B0_1 *owner;

    owner = motion->owner;
    owner->ticks = (u16) (owner->ticks + 1);
    tick = motion->elapsed_ticks + 1;
    motion->elapsed_ticks = tick;
    if (motion->lifetime < (s16) tick) {
        ((S_818BD3B0_0_pre *)motion)[-1].flags = (u16) (((S_818BD3B0_0_pre *)motion)[-1].flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }
    height_offset = (s32) ((rcos((s16) tick << 7) >> 4) * motion->orbit_scale) >> 8;
    motion->wave_offset = (s16) height_offset;
    position->z = (s32) (position->center_z - (height_offset << 0x10));
    radius_product = (rsin((s16) motion->elapsed_ticks << 7) >> 4) * motion->orbit_scale;
    angle = motion->angle + 0x80;
    motion->angle = (u16) angle;
    motion->wave_offset = (s16) (radius_product >> 8);
    position->x = (s32) (position->center_x + (((rcos(angle) >> 4) * motion->wave_offset) << 8));
    position->y = (s32) (position->center_y + (((rsin((s16) motion->angle) >> 4) * motion->wave_offset) << 8));
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        select_record_entry_and_value(object, &shared_sprite_entries, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame and s0/s2/s1 lifetime shape. */
