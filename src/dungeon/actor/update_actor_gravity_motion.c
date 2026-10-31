#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"

typedef void (*DungeonCallback)(void *, void *, void *, void *);

extern DungeonCallback gravity_motion_callbacks[];

extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void advance_sprite_animation_and_textures(void *);


/* Runs object callbacks, applies movement and gravity, and updates ground height. */
void dispatch_actor_actions_and_integrate_gravity(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite) {
    SpriteFrameState *ent= sprite;
    void *update_obj = body;
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
    gravity_motion_callbacks[(*((u8 *)update_obj + (0x9A)))](update_obj, motion, ent, update_obj);

    {
        u16 render_flags = ent->flags;
        if (!(render_flags & 0x8000)) {
            if (!(render_flags & 0x40)) {
                advance_sprite_animation_and_textures(ent);
            }
        }
    }

    x = motion->x.v;
    dx = motion->velocity_x;
    y = motion->y.v;
    dy = motion->velocity_y;
    motion->x.v = x + dx;
    motion->y.v = y + dy;

    if (body->action_state_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        motion->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    }
    fall_offset = body->unk_90.value;
    fall_speed = motion->velocity_z;
    fall_flags = body->action_state_flags;
    body->unk_90.value = fall_offset + fall_speed;

    if (!(fall_flags & 4) && (ground_height = sample_terrain_surface_height(
            ((u16) motion->x.w.i),
            ((u16) motion->y.w.i),
            (s16)((*(u16 *)((u8 *)update_obj + (0x88))) - 0x20))) < 0x200) {
            base_height_u = (*(u16 *)((u8 *)update_obj + (0x88)));
            base_height = (*(s16 *)((u8 *)update_obj + (0x88)));
            if (body->unk_90.parts.high.s + base_height < ground_height) {
                u16 object_flags = body->action_state_flags;
                body->action_state_flags = object_flags;
            } else {
                if (ground_height >= base_height) {
                    body->unk_90.value = 0;
                } else {
                    body->unk_90.parts.high.s = ground_height - base_height_u;
                }
                motion->velocity_z = 0;
                (*(u32 *)((u8 *)update_obj + (0x1C))) |= 0x08000000;
                body->unk_9D.u = 0;
            }

            if ((*(u32 *)((u8 *)update_obj + (0x1C))) & 0x40000000) {
                s32 tile_x;
                s32 tile_y;
                (*(u32 *)((u8 *)update_obj + (0x1C))) &= ~0x40000000;
                tile_x = (ent->tile_x << 6) | 0x20;
                tile_y = (ent->tile_y << 6) | 0x20;
                ground_height = sample_terrain_surface_height(
                    tile_x, tile_y, (s16)((*(u16 *)((u8 *)update_obj + (0x88))) - 0x20));
                body->unk_90.parts.high.s += (*(u16 *)((u8 *)update_obj + (0x88))) - ground_height;
                (*(s16 *)((u8 *)update_obj + (0x88))) = ground_height;
            }
    } else {
        (*(u32 *)((u8 *)update_obj + (0x1C))) &= ~0x08000000;
    }

    motion->z.w.i = (*(u16 *)((u8 *)update_obj + (0x88))) + body->unk_90.parts.high.u;
    ent->flags |= 0x40;
    (*(u32 *)((u8 *)update_obj + (0x1C))) |= 0x200;
}
