#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor.h"

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern EntityCallback floor_contact_callbacks[];

extern void advance_sprite_animation_and_textures(void *entity);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);



/* Run entity callbacks, advance movement, and resolve floor contact. */
void update_actor_floor_contact(ActorRecord *object_arg, void *motion_arg, SpriteFrameState *sprite)
{
    ActorRecord *object = object_arg;
    register ObjectPosition *motion = motion_arg;
    SpriteFrameState *entity= sprite;
    ActorRecord *object_base = object;
    EntityCallback callback;
    s16 floor_height;
    u16 entity_flags;
    u16 global_flags = g_dungeon_status.flags;

    if (global_flags & 0x2000) {
        object_base->movement_queue_state &= 0x7F;
        return;
    }

    callback = object_base->unk_8C.run;
    if (callback != 0) {
        callback(object_base, motion, entity, object_base);
    }
    floor_contact_callbacks[object_base->action_id.u](object_base, motion, entity, object_base);

    entity_flags = entity->flags;
    if (!(entity_flags & 0x8000)) {
        if (!(entity_flags & 0x40)) {
            advance_sprite_animation_and_textures(entity);
        }
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (object->action_state_flags & 8) {
        object->unk_9D.u = 0;
    } else {
        motion->velocity_z += object->unk_9D.s * 0x14000;
        object->unk_9D.u++;
    }
    object->unk_90.value += motion->velocity_z;

    if (!(object->action_state_flags & 4)) {
        floor_height = sample_terrain_surface_height(motion->x.unsigned_parts.integer, motion->y.unsigned_parts.integer,
                              (s16)((*(u16 *)((u8 *)object_base + (0x88))) - 0x20));
        if (floor_height < 0x200) {
            if (object->unk_90.parts.high.s + object_base->ground_height < floor_height) {
                object->action_state_flags &= 0xFFFF;   /* BYTES: +0x98 no-op write-back: retail reads the field, the unchanged store compiles away (decision 39) */
            } else {
                if (floor_height >= object_base->ground_height) {
                    object->unk_90.value = 0;
                } else {
                    object->unk_90.parts.high.s = floor_height - (*(u16 *)((u8 *)object_base + (0x88)));
                }
                motion->velocity_z = 0;
                (*(u32 *)((u8 *)object_base + (0x1C))) |= 0x08000000;
                object->unk_9D.u = 0;
            }

            if ((*(u32 *)((u8 *)object_base + (0x1C))) & 0x40000000) {
                (*(u32 *)((u8 *)object_base + (0x1C))) &= ~0x40000000;
                floor_height = sample_terrain_surface_height(
                    (entity->tile_x << 6) | 0x20,
                    (entity->tile_y << 6) | 0x20,
                    (s16)((*(u16 *)((u8 *)object_base + (0x88))) - 0x20));
                object->unk_90.parts.high.u += (*(u16 *)((u8 *)object_base + (0x88))) - floor_height;
                object_base->ground_height = floor_height;
            }
        } else {
            (*(u32 *)((u8 *)object_base + (0x1C))) &= ~0x08000000;
        }
    } else {
        (*(u32 *)((u8 *)object_base + (0x1C))) &= ~0x08000000;
    }

    motion->z.unsigned_parts.integer = (*(u16 *)((u8 *)object_base + (0x88)))
        + object->unk_90.parts.high.u;
    entity->flags |= 0x40;
    (*(u32 *)((u8 *)object_base + (0x1C))) |= 0x200;
}
