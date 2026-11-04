#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/monster/glacier.h"
#include "shared/object_node.h"


   /* the 0x2 bytes before arg0 in func_8102F348, addressed as arg0[-1] */

   /* arg0 in func_8102F348 */

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void advance_sprite_animation_and_textures(void *);
/* Updates effect motion and collision, grows its sprite, and flags expired effects. */
void grow_terrain_colliding_sprite(CollidingSpriteParticleBody *effect, ObjectPosition *position, SpriteFrameState *sprite) {
    s32 height;

    position->x.v += effect->velocity_x;
    effect->velocity_x += effect->acceleration_x;
    if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
                       position->z.w.i) << 16) != 0) {
        position->x.v -= effect->velocity_x;
        effect->velocity_x = 0;
        effect->acceleration_x = 0;
    }

    position->y.v += effect->velocity_y;
    effect->velocity_y += effect->acceleration_y;
    if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
                       position->z.w.i) << 16) != 0) {
        position->y.v -= effect->velocity_y;
        effect->velocity_y = 0;
        effect->acceleration_y = 0;
    }

    position->z.v += effect->velocity_z;
    effect->velocity_z += effect->acceleration_z;
    height = position->z.w.i;
    if ((sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
                       (s16)((u16)position->z.w.i - 4)) - 0x10) < height) {
        effect->velocity_z = 0;
        position->z.w.i = sample_terrain_surface_height(
            position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            (s16)((u16)position->z.w.i - 4)) - 0x11;
        position->z.w.frac = 0;
        if (effect->contacted_ground == 0) {
            effect->contacted_ground = 1;
            effect->remaining.s = 0;
        }
    }

    effect->animation_tick++;
    if ((effect->animation_tick & 3) == 0) {
        advance_sprite_animation_and_textures(sprite);
    }

    sprite->scale_x += 100;
    if (sprite->scale_x > 0x1000) {
        sprite->scale_x = 0x1000;
    }

    sprite->scale_y += 100;
    if (sprite->scale_y > 0x1000) {
        sprite->scale_y = 0x1000;
    }

    effect->remaining.u = effect->remaining.u - 1;
    if ((s16)effect->remaining.u <= 0) {
        s32 *status_page = (s32 *)0x80080000;
        NODE_HEADER(effect)->flags |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }

    if (sprite->flags & 0x8000) {
        s32 *status_page = (s32 *)0x80080000;
        NODE_HEADER(effect)->flags |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }
}
