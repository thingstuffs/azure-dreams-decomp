#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/item.h"
#include "engine/texture.h"
#include "shared/entity.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void advance_sprite_animation_and_textures(void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void start_direction_based_action(ActorRecord *action_state, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *object);

extern u8 barong_action_resume_address[];
extern Callback barong_callbacks[];

typedef struct S_801712A8_0 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_801712A8_0;   /* actor in update_actor_facing_and_floor_contact */

   /* monster in update_actor_facing_and_floor_contact */

/* Updates actor behavior, facing, movement, and floor contact. */
void update_actor_facing_and_floor_contact(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    S_801712A8_0 *actor = (S_801712A8_0 *)body;
    u16 direction;
    u32 direction_copy;
    ActorActionHandler callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        ActorActionHandler first_callback;

        first_callback = body->unk_8C.handler;
        if (first_callback == (ActorActionHandler)barong_action_resume_address) {
            first_callback(body, motion, sprite, body);
        } else {
            body->movement_queue_state &= 0x7F;
        }
        return;
    }

    direction = body->pending_turn_updates;
    if (refresh_actor_facing_and_lifecycle(body, motion, sprite, body) != 0) {
        return;
    }

    if ((*(u32 *)((u8 *)body + 0x14)) & 0x00800000) {
        if (body->action_id.u != 0x17) {
            (*(u32 *)((u8 *)body + 0x14)) &= 0xFF7FFFFF;
            start_direction_based_action(body, motion, sprite, body);
        }
    }

    callback = body->unk_8C.handler;
    if (callback != 0) {
        callback(body, motion, sprite, actor);
    }

    barong_callbacks[body->action_id.u](body, motion, sprite, actor);

    if ((s16)direction != actor->unk_6D) {
        try_move_actor_to_valid_position(body, motion, sprite, actor);
    }

    monster_flags = sprite->flags;
    if (!(monster_flags & 0x8000)) {
        s32 angle_sector;

        angle_sector =
            (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9;
        direction = angle_sector & 7;
        direction_index = direction;
        direction_copy = direction;

        if (body->unk_94 != direction_index) {
            u8 *tile_map = *(unsigned char **)&sprite->frameTable;
            if (tile_map != 0) {
                select_indirect_table_entry(sprite, tile_map[direction_index],
                              sprite->unk_04);
            }
            body->unk_94 = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
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

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (body->action_state_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        motion->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    }

    body->unk_90.value += motion->velocity_z;

    if (!(body->action_state_flags & 4) && (floor_height = sample_terrain_surface_height(motion->x.w.i,
                              motion->y.w.i,
                              (s16)(actor->unk_88.u - 0x20))) < 0x200) {
        actor_height = actor->unk_88.s;
        if (body->unk_90.parts.high.s + actor_height < floor_height) {
            actor->unk_1C.u &= 0xF7FFFFFF;
        } else if (floor_height >= actor_height) {
            body->unk_90.value = 0;
            motion->velocity_z = 0;
            actor->unk_1C.u |= 0x08000000;
            body->unk_9D.u = 0;
        } else {
            body->unk_90.parts.high.s = floor_height - actor->unk_88.u;
            motion->velocity_z = 0;
            actor->unk_1C.u |= 0x08000000;
            body->unk_9D.u = 0;
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
    motion->z.w.i =
        actor->unk_88.u + body->unk_90.parts.high.u;
    sprite->flags |= 0x40;

}
