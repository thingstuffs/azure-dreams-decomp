#include "common.h"
#include "shared/object_flags.h"
#include "slus.h"
#include "town/minigame.h"


/* Advances and darkens a moving effect, updates its visual, and propagates status flags. */
void advance_fading_particle_until_animation_boundary(u8 *effect, u8 *motion, u8 *visual)
{
    s32 velocity;
    u8 shade;

    velocity = *(s32 *)(motion + 0x14);
    if (velocity != 0) {
        *(s32 *)(motion + 8) += velocity;
        *(s32 *)(motion + 0x14) += 0x18000;

        shade = visual[0xE] - 0x20;
        visual[0xE] = shade;
        visual[0xD] = shade;
        visual[0xC] = shade;
    }

    advance_sprite_animation_and_textures(visual);
    if (*(u16 *)(visual + 0x14) & 0x6000) {
        *(u16 *)(effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
