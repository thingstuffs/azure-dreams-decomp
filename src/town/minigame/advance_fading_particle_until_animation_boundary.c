#include "common.h"
#include "shared/object_flags.h"
#include "slus.h"
#include "town/minigame.h"


/* Advances and darkens a moving effect, updates its visual, and propagates status flags. */
void advance_fading_particle_until_animation_boundary(u8 *effect, ObjectPosition *motion, SpriteFrameState *visual)
{
    s32 velocity;
    u8 shade;

    velocity = motion->velocity_z;
    if (velocity != 0) {
        motion->z.v += velocity;
        motion->velocity_z += 0x18000;

        shade = visual->color.c.b - 0x20;
        visual->color.c.b = shade;
        visual->color.c.g = shade;
        visual->color.c.r = shade;
    }

    advance_sprite_animation_and_textures(visual);
    if (visual->flags & 0x6000) {
        *(u16 *)(effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
