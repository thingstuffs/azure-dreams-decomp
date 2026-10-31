#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern EntityCallback floor_contact_callbacks[];

extern void advance_sprite_animation_and_textures(void *entity);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);

typedef struct S_800D1E34_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D1E34_1;   /* pos in update_actor_floor_contact */

typedef struct S_800D1E34_2 {
    u8 pad_00[0x90];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x3];
    union { u8 n; s8 n2; u8 v; } unk_9D;   /* accessed as both */
} S_800D1E34_2;   /* obj in update_actor_floor_contact */

/* Run entity callbacks, advance movement, and resolve floor contact. */
void update_actor_floor_contact(void *object_arg, void *motion_arg, SpriteFrameState *sprite)
{
    S_800D1E34_2 *object = object_arg;
    register S_800D1E34_1 *motion = motion_arg;
    SpriteFrameState *entity= sprite;
    void *object_base = object;
    EntityCallback callback;
    s16 floor_height;
    u16 entity_flags;
    u16 global_flags = g_dungeon_status.flags;

    if (global_flags & 0x2000) {
        (*(u8 *)((u8 *)object_base + (0x71))) &= 0x7F;
        return;
    }

    callback = (*(EntityCallback *)((u8 *)object_base + (0x8C)));
    if (callback != 0) {
        callback(object_base, motion, entity, object_base);
    }
    floor_contact_callbacks[(*(u8 *)((u8 *)object_base + (0x9A)))](object_base, motion, entity, object_base);

    entity_flags = entity->flags;
    if (!(entity_flags & 0x8000)) {
        if (!(entity_flags & 0x40)) {
            advance_sprite_animation_and_textures(entity);
        }
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if (object->unk_98 & 8) {
        object->unk_9D.n = 0;
    } else {
        motion->unk_14 += object->unk_9D.n2 * 0x14000;
        object->unk_9D.v++;
    }
    object->unk_90.at00.v += motion->unk_14;

    if (!(object->unk_98 & 4)) {
        floor_height = sample_terrain_surface_height(motion->unk_00.at02.v, motion->unk_04.at02.v,
                              (s16)((*(u16 *)((u8 *)object_base + (0x88))) - 0x20));
        if (floor_height < 0x200) {
            if (object->unk_90.at02.v + (*(s16 *)((u8 *)object_base + (0x88))) < floor_height) {
                object->unk_98 &= 0xFFFF;   /* BYTES: +0x98 no-op write-back: retail reads the field, the unchanged store compiles away (decision 39) */
            } else {
                if (floor_height >= (*(s16 *)((u8 *)object_base + (0x88)))) {
                    object->unk_90.at00.v = 0;
                } else {
                    object->unk_90.at02.v = floor_height - (*(u16 *)((u8 *)object_base + (0x88)));
                }
                motion->unk_14 = 0;
                (*(u32 *)((u8 *)object_base + (0x1C))) |= 0x08000000;
                object->unk_9D.n = 0;
            }

            if ((*(u32 *)((u8 *)object_base + (0x1C))) & 0x40000000) {
                (*(u32 *)((u8 *)object_base + (0x1C))) &= ~0x40000000;
                floor_height = sample_terrain_surface_height(
                    (entity->tile_x << 6) | 0x20,
                    (entity->tile_y << 6) | 0x20,
                    (s16)((*(u16 *)((u8 *)object_base + (0x88))) - 0x20));
                object->unk_90.at02u.v += (*(u16 *)((u8 *)object_base + (0x88))) - floor_height;
                (*(u16 *)((u8 *)object_base + (0x88))) = floor_height;
            }
        } else {
            (*(u32 *)((u8 *)object_base + (0x1C))) &= ~0x08000000;
        }
    } else {
        (*(u32 *)((u8 *)object_base + (0x1C))) &= ~0x08000000;
    }

    motion->unk_0A = (*(u16 *)((u8 *)object_base + (0x88)))
        + object->unk_90.at02u.v;
    entity->flags |= 0x40;
    (*(u32 *)((u8 *)object_base + (0x1C))) |= 0x200;
}
