#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
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
extern void register_node(void *object, void *callback);
extern void select_sprite_entry(void *object, s32 kind, s32 value);
extern void *resolve_record_orientation_or_fallback(void *ptr, void *ptr1, Vec3u16 *out, s32 value3);
extern u8 cyclone_spawn_update_address;
/* Create a render object and initialize its position and motion toward a directional target. */
void *create_directional_target_object(void *emitter, Copy24 *position, void *source)
{
    void *emitter_copy;
    Copy24 target_position;
    Vec3u16 position_offset;
    u16 direction_flags;
    s32 direction_offset;
    Copy24 *position_data;
    ObjectNodeHeader * object;
    void *transform;
    void *source_copy;
    SpriteFrameState *render;
    void *result;
    position_data = position;
    source_copy = source;
    direction_flags = *((u16 *) (((u8 *) emitter) + 0x2A));
    emitter_copy = emitter;
    target_position = *position_data;
    direction_offset = (direction_flags >> 8) & 0xE;
    *((u16 *) (((u8 *) (&target_position)) + 2)) += ((*((s16 *) (((u8 *) (((u8 *)dir_step_x)))
        + direction_offset))) * (*((s16 *) (((u8 *) emitter) + 0xB2)))) * 0x40;
    *((u16 *) (((u8 *) (&target_position)) + 6)) += ((*((s16 *) (((u8 *) (((u8 *)dir_step_y)))
        + direction_offset))) * (*((s16 *) (((u8 *) emitter_copy) + 0xB2)))) * 0x40;
    object = allocate_flagged_object_node(0x312);
    if (object != 0) {
        object->update_callback = &cyclone_spawn_update_address;
        register_node(object, project_sprite_chain);
        render = object->sprite;
        render->animation_resource = *((s32 *) (((u8 *) source_copy) + 0x28));
        render->scale_y = 0x800;
        render->scale_x = 0x800;
        render->color.word = 0x00808080;
        render->flags |= 0xC;
        render->tpage_abr |= 0x20;
        select_sprite_entry(render, 0x47, 0);
        transform = object->position;
        *((Copy24 *) (((u8 *) object) + 0x24)) = *position_data;
        position_data = (Copy24 *) (((u8 *) object) + 0x20);
        position_offset.z = 0;
        position_offset.y = 0;
        position_offset.x = 0;
        if (resolve_record_orientation_or_fallback(*((void **) (((u8 *) source_copy) + 8)), source_copy, &position_offset, 1) != 0) {
            *((u16 *) (((u8 *) position_data) + 6)) += position_offset.x;
            *((u16 *) (((u8 *) transform) + 2)) = *((u16 *) (((u8 *) position_data) + 6));
            *((u16 *) (((u8 *) position_data) + 0xA)) += position_offset.y;
            *((u16 *) (((u8 *) transform) + 6)) = *((u16 *) (((u8 *) position_data) + 0xA));
            *((u16 *) (((u8 *) position_data) + 0xE)) += position_offset.z;
            *((u16 *) (((u8 *) transform) + 0xA)) = *((u16 *) (((u8 *) position_data) + 0xE));
        }
        *((s32 *) (((u8 *) position_data) + 0x10)) = (((s32) target_position.words[0])
            - (*((s32 *) (((u8 *) position_data) + 4)))) / 0x20;
        *((s32 *) (((u8 *) position_data) + 0x14)) = (((s32) target_position.words[1])
            - (*((s32 *) (((u8 *) position_data) + 8)))) / 0x20;
        result = object;
        return result;
    }
    if (position_data || source) {
        return 0;
    }
    else {
        return 0;
    }
}
