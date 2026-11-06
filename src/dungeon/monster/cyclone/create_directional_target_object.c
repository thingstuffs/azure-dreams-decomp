#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "engine/graphics.h"
#include "dungeon/monster/cyclone/bobbing_motion.h"

typedef struct
{
    u32 words[6];
}
Copy24;
typedef struct
{
    u16 x;
    u16 y;
    u16 z;
}
Vec3u16;
extern u8 cyclone_spawn_update_address;
/* Create a render object and initialize its position and motion toward a directional target. */
void *create_directional_target_object(ActorRecord *emitter, Copy24 *position, SpriteFrameState *sprite)
{
    ActorRecord *emitter_copy;
    Copy24 target_position;
    Vec3u16 position_offset;
    u16 direction_flags;
    s32 direction_offset;
    Copy24 *position_data;
    CycloneBobbingMotionBody *motion_data;
    ObjectNodeHeader * object;
    ObjectPosition *transform;
    SpriteFrameState *source_copy;
    SpriteFrameState *render;
    void *result;
    position_data = position;
    source_copy = sprite;
    direction_flags = (u16)emitter->facing;
    emitter_copy = emitter;
    target_position = *position_data;
    direction_offset = (direction_flags >> 8) & 0xE;
    *((u16 *) (((u8 *) (&target_position)) + 2)) += (dir_step_x[direction_offset >> 1]
        * emitter->unk_B0.halves.high.s) * 0x40;
    *((u16 *) (((u8 *) (&target_position)) + 6)) += ((*((s16 *) (((((u8 *)dir_step_y)))
        + direction_offset))) * emitter_copy->unk_B0.halves.high.s) * 0x40;
    object = allocate_flagged_object_node(0x312);
    if (object != 0) {
        object->update_callback = &cyclone_spawn_update_address;
        register_node(object, project_sprite_chain);
        render = object->sprite;
        render->animation_resource = source_copy->animation_resource;
        render->scale_y = 0x800;
        render->scale_x = 0x800;
        render->color.word = 0x00808080;
        render->flags |= 0xC;
        render->tpage_abr |= 0x20;
        select_sprite_entry(render, 0x47, 0);
        transform = object->position;
        *((Copy24 *) (((u8 *) object) + 0x24)) = *position_data;
        motion_data = NODE_BODY(object);
        position_offset.z = 0;
        position_offset.y = 0;
        position_offset.x = 0;
        if (resolve_record_orientation_or_fallback(source_copy->source, source_copy, &position_offset, 1) != 0) {
            motion_data->path.x.unsigned_parts.integer += position_offset.x;
            transform->x.unsigned_parts.integer = motion_data->path.x.unsigned_parts.integer;
            motion_data->path.y.unsigned_parts.integer += position_offset.y;
            transform->y.unsigned_parts.integer = motion_data->path.y.unsigned_parts.integer;
            motion_data->path.z.unsigned_parts.integer += position_offset.z;
            transform->z.unsigned_parts.integer = motion_data->path.z.unsigned_parts.integer;
        }
        motion_data->path.velocity_x = (((s32) target_position.words[0])
            - motion_data->path.x.v) / 0x20;
        motion_data->path.velocity_y = (((s32) target_position.words[1])
            - motion_data->path.y.v) / 0x20;
        result = object;
        return result;
    }
    if (position_data || sprite) {
        return 0;
    }
    else {
        return 0;
    }
}
