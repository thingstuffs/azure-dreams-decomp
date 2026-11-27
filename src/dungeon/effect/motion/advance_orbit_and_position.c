#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libgte.h"
#include "dungeon/effect/motion.h"
#include "slus.h"

struct Dst;
struct Elem;

#include "dungeon/effect/sprite/high_particle_entries.h"


/* Advance the orbit angle and update the position when the object flags allow it. */
void advance_orbit_and_position(IndexedColorSpriteBody *orbit, ObjectPosition *position, SpriteFrameState *object) {
    s16 angle;
    s32 next_angle;
    s32 wrap_angle;

    angle = orbit->orbit_angle;
    next_angle = angle + 0x40;
    wrap_angle = next_angle;
    if (next_angle < 0) {
        wrap_angle = angle + 0x103F;
    }
    orbit->orbit_angle = (s16) (next_angle - ((wrap_angle >> 0xC) << 0xC));
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        select_record_entry_and_value(object, &high_particle_sprite_entries, 0);
        position->x.w.i = (s16) (orbit->center_x + ((s32) ((rsin(orbit->orbit_angle) >> 4) * 0x1C) >> 8));
        position->y.w.i = (s16) (orbit->center_y + ((s32) ((rcos(orbit->orbit_angle) >> 4) * 0x1C) >> 8));
    }
}
