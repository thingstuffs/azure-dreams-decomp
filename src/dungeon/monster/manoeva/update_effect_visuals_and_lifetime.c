#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/manoeva.h"
#include "dungeon/item.h"
#include "engine/texture.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void advance_sprite_animation_and_textures(void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);

extern u8 manoeva_action_resume_address[];
extern Callback manoeva_callbacks[];

typedef struct S_80170AD0_0 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170AD0_0;   /* actor in update_effect_visuals_and_lifetime */

   /* monster in update_effect_visuals_and_lifetime */

/* Updates actor callbacks, facing, movement, and floor contact. */
void update_effect_visuals_and_lifetime(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite)
{
    S_80170AD0_0 *actor = (S_80170AD0_0 *)body;
    s16 direction_index;
    register s32 direction;
    ActorActionHandler callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    u8 entity_kind;

    if (g_dungeon_status.flags & 0x2000) {
        ActorActionHandler early_callback;

        early_callback = body->unk_8C.handler;
        if (early_callback == (Callback)manoeva_action_resume_address) {
            early_callback(body, position, sprite, body);
        } else {
            body->movement_queue_state &= 0x7F;
        }
        return;
    }

    direction_index = body->pending_turn_updates;
    entity_kind = body->action_id.u;
    if (entity_kind != 0x17 && entity_kind != 0x19) {
        if (refresh_actor_facing_and_lifecycle(body, position, sprite, body) != 0) {
            return;
        }
    }

    callback = body->unk_8C.handler;
    if (callback != 0) {
        callback(body, position, sprite, actor);
    }

    manoeva_callbacks[body->action_id.u](body, position, sprite, actor);

    if ((s16)direction_index != actor->unk_6D) {
        try_move_actor_to_valid_position(body, position, sprite, actor);
    }

    monster_flags = sprite->flags;
    if (!(monster_flags & 0x8000)) {
        s32 direction_sector;

        direction_sector =
            (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9;
        direction = direction_sector & 7;
        direction_index = direction;

        if (body->unk_94 != direction_index) {
            u8 *direction_tiles = *(unsigned char **)&sprite->frameTable;
            select_indirect_table_entry(sprite, direction_tiles[direction_index],
                          sprite->unk_04);
            body->unk_94 = direction;
        }

        if (dir_sprite_flag[direction_index] != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }

        if (!(actor->unk_1C.u & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
        }

        apply_monster_koyaw_data(actor->unk_1C.s, (u8 *)sprite + 0xC);
    } else {
        sprite->flags =
            (monster_flags & 0x0800) ? (monster_flags & 0x8FFF) : (monster_flags | 0x7000);
    }

    position->x.v += position->velocity_x;
    position->y.v += position->velocity_y;

    if (body->action_state_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        position->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    }

    body->unk_90.value += position->velocity_z;

    if (!(body->action_state_flags & 4)) {
        floor_height = sample_terrain_surface_height(position->x.w.i,
                              position->y.w.i,
                              (s16)(actor->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = actor->unk_88.s;
            if (body->unk_90.parts.high.s + actor_height < floor_height) {
                actor->unk_1C.u &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    body->unk_90.value = 0;
                } else {
                    body->unk_90.parts.high.s = floor_height - actor->unk_88.u;
                }

                position->velocity_z = 0;
                body->unk_9D.u = 0;
                actor->unk_1C.u |= 0x08000000;
            }

            if (actor->unk_1C.u & 0x40000000) {
                actor->unk_1C.u &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height(
                    (sprite->tile_x << 6) | 0x20,
                    (sprite->tile_y << 6) | 0x20,
                    (s16)(actor->unk_88.u - 0x20));
                body->unk_90.parts.high.s +=
                    actor->unk_88.u - floor_height;
                actor->unk_88.u = floor_height;
            }
        } else {
            actor->unk_1C.u &= 0xF7FFFFFF;
        }
    } else {
        actor->unk_1C.u &= 0xF7FFFFFF;
    }

    position->z.w.i =
        actor->unk_88.u + body->unk_90.parts.high.u;
    sprite->flags |= 0x40;

}
