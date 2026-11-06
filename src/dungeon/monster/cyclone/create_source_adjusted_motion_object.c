#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "dungeon/monster/cyclone/bobbing_motion.h"

typedef struct {
    u32 words[6];
} Copy24;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

extern u8 cyclone_spawn_update_address;

typedef struct S_80175D04_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x86];
    s16 unk_B2;
} S_80175D04_0;   /* arg0 in create_source_adjusted_motion_object */

typedef struct S_80175D04_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80175D04_1;   /* &local in create_source_adjusted_motion_object */


/* Creates an object with a source-adjusted position and motion toward a directional target. */
void *create_source_adjusted_motion_object(S_80175D04_0 *actor, Copy24 *start_pos, SpriteFrameState *source)
{
    Copy24 target_pos;
    Vec3u16 source_offset;
    u16 direction_bits;
    s32 direction_offset;
    s16 axis_step;
    CycloneBobbingMotionBody *motion;
    ObjectNodeHeader * object;
    ObjectPosition *child_pos;
    SpriteFrameState *render;

    direction_bits = actor->unk_2A;
    target_pos = *start_pos;
    direction_offset = (direction_bits >> 8) & 0xE;

    axis_step = dir_step_x[direction_offset >> 1];
    ((S_80175D04_1 *)(&target_pos))->unk_02 +=
        (axis_step * actor->unk_B2 * 0x40) +
        (axis_step * 0x20);

    axis_step = dir_step_y[direction_offset >> 1];
    ((S_80175D04_1 *)(&target_pos))->unk_06 +=
        (axis_step * actor->unk_B2 * 0x40) +
        (axis_step * 0x20);

    object = allocate_flagged_object_node(0x312);
    if (object != 0) {
        (object->update_callback) = &cyclone_spawn_update_address;
        register_node(object, project_sprite_chain);

        render = object->sprite;
        render->animation_resource = source->animation_resource;
        render->scale_y = 0x800;
        render->scale_x = 0x800;
        render->color.word = 0x00808080;
        render->flags |= 0xC;
        render->tpage_abr |= 0x20;
        select_sprite_entry(render, 0x47, 0);

        child_pos = object->position;
        (*(Copy24 *)((u8 *)object + 0x24)) = *start_pos;
        motion = NODE_BODY(object);

        source_offset.z = 0;
        source_offset.y = 0;
        source_offset.x = 0;
        if (resolve_record_orientation_or_fallback(source->source, source, &source_offset, 1) != 0) {
            motion->path.x.unsigned_parts.integer += source_offset.x;
            child_pos->x.w.i = motion->path.x.unsigned_parts.integer;
            motion->path.y.unsigned_parts.integer += source_offset.y;
            child_pos->y.w.i = motion->path.y.unsigned_parts.integer;
            motion->path.z.unsigned_parts.integer += source_offset.z;
            child_pos->z.w.i = motion->path.z.unsigned_parts.integer;
        }

        motion->path.velocity_x =
            ((s32)target_pos.words[0] - motion->path.x.v) / 0x20;
        motion->path.velocity_y =
            ((s32)target_pos.words[1] - motion->path.y.v) / 0x20;

        return object;
    }

    return 0;
}
