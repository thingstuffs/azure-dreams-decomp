#include "common.h"
#include "dungeon/monster/glacier/projected_depth.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/monster/glacier.h"
#include "sdk/libgte.h"

   /* arg1 in apply_relative_projected_depth */




typedef struct {
    u16 x0;
    u16 x1;
    u16 x2;
} Stack3;

extern s8 view_direction_depth_biases[];
extern void advance_sprite_animation_and_textures(void *);

/* Apply a relative projected depth with a direction bias and propagate output status flags. */
void apply_relative_projected_depth(void *entity_arg, MovingPosition *position, void *output) {
    GlacierProjectedDepthBody *entity = entity_arg;
    Stack3 coords;
    s32 projection_flags;
    s32 depth_cue;
    s32 screen_xy[2];
    s16 depth_delta;
    s32 depth_bias;
    ObjectPosition *base_position;
    SpriteFrameState *result;

    result = output;
    coords.x0 = position->x;
    coords.x1 = position->y;
    coords.x2 = position->z;
    depth_delta = RotTransPers(&coords.x0, &screen_xy, &depth_cue, &projection_flags);
    base_position = entity->reference_position;
    coords.x0 = base_position->x.unsigned_parts.integer;
    coords.x1 = base_position->y.unsigned_parts.integer;
    coords.x2 = base_position->z.unsigned_parts.integer;
    depth_delta = depth_delta - RotTransPers(&coords.x0, &screen_xy, &depth_cue, &projection_flags);
    depth_bias = view_direction_depth_biases[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16)entity->facing + 0x100) >> 9) & 7] * 2;
    depth_delta = depth_delta + depth_bias;
    result->flags = (u16) (result->flags & 0xFF7F);
    result->depth_bias = depth_delta;
    advance_sprite_animation_and_textures(result);
    if (result->flags & 0x6000) {
        NODE_HEADER(entity)->flags = (u16) (NODE_HEADER(entity)->flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
