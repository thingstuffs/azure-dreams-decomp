#include "common.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"


typedef void (*DungeonCallback)(void *, void *, void *, void *);

extern DungeonCallback actor_gravity_callbacks[];

extern s16 sample_terrain_surface_height(u16, u16, s16);



typedef struct S_800D2664_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D2664_2;   /* ent in update_actor_gravity */

/* Runs object callbacks, applies movement and gravity, and updates ground height. */
void update_actor_gravity(ActorRecord *object, ObjectPosition *motion, void *entity) {
    S_800D2664_2 *ent = entity;
    void *update_obj = object;
    DungeonCallback callback;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 fall_offset;
    s32 fall_speed;
    u16 fall_flags;
    s16 ground_height;
    s16 base_height;
    s32 base_height_u;

    if (g_dungeon_status.flags & 0x2000) {
        (*((u8 *)update_obj + (0x71))) &= 0x7F;
        return;
    }


    callback = (*(DungeonCallback *)((u8 *)update_obj + (0x8C)));
    if (callback != 0) {
        callback(update_obj, motion, ent, update_obj);
    }
    actor_gravity_callbacks[(*((u8 *)update_obj + (0x9A)))](update_obj, motion, ent, update_obj);

    x = motion->x.v;
    dx = motion->velocity_x;
    y = motion->y.v;
    dy = motion->velocity_y;
    motion->x.v = x + dx;
    motion->y.v = y + dy;

    if ((*(u16 *)((u8 *)update_obj + (0x98))) & 8) {
        (*((u8 *)update_obj + (0x9D))) = 0;
    } else {
        motion->velocity_z += (*(s8 *)((u8 *)update_obj + (0x9D))) * 0x14000;
        (*((u8 *)update_obj + (0x9D)))++;
    }
    fall_offset = object->unk_90.value;
    fall_speed = motion->velocity_z;
    fall_flags = object->action_state_flags;
    object->unk_90.value = fall_offset + fall_speed;

    if (!(fall_flags & 4) && (ground_height = sample_terrain_surface_height(
            ((u16) motion->x.w.i),
            ((u16) motion->y.w.i),
            (s16)((*(u16 *)((u8 *)update_obj + (0x88))) - 0x20))) < 0x200) {
            base_height_u = (*(u16 *)((u8 *)update_obj + (0x88)));
            base_height = (*(s16 *)((u8 *)update_obj + (0x88)));
            if (object->unk_90.parts.high.s + base_height < ground_height) {
                u16 object_flags = object->action_state_flags;
                object->action_state_flags = object_flags;
            } else {
                if (ground_height >= base_height) {
                    object->unk_90.value = 0;
                } else {
                    object->unk_90.parts.high.s = ground_height - base_height_u;
                }
                motion->velocity_z = 0;
                (*(u32 *)((u8 *)update_obj + (0x1C))) |= 0x08000000;
                object->unk_9D.u = 0;
            }

            if ((*(u32 *)((u8 *)update_obj + (0x1C))) & 0x40000000) {
                s32 tile_x;
                s32 tile_y;
                (*(u32 *)((u8 *)update_obj + (0x1C))) &= ~0x40000000;
                tile_x = (ent->unk_24 << 6) | 0x20;
                tile_y = (ent->unk_25 << 6) | 0x20;
                ground_height = sample_terrain_surface_height(
                    tile_x, tile_y, (s16)((*(u16 *)((u8 *)update_obj + (0x88))) - 0x20));
                object->unk_90.parts.high.s += (*(u16 *)((u8 *)update_obj + (0x88))) - ground_height;
                (*(s16 *)((u8 *)update_obj + (0x88))) = ground_height;
            }
    } else {
        (*(u32 *)((u8 *)update_obj + (0x1C))) &= ~0x08000000;
    }


    motion->z.w.i = (*(u16 *)((u8 *)update_obj + (0x88))) + object->unk_90.parts.high.u;
    ent->unk_14 |= 0x40;
    (*(u32 *)((u8 *)update_obj + (0x1C))) |= 0x200;
}
