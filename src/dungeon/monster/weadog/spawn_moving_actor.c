#include "dungeon/monster/weadog_frames.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/node.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/monster/weadog.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))

extern GridPoint weadog_slot_g_direction_steps[8];
extern u8 D_80077C50[];
extern u8 weadog_object_callback[];
extern s32 weadog_action_resume_address;

extern u8 D_80174F18[];





/* Spawns a moving actor and advances the action through animation and recovery. */
void spawn_moving_actor(ActorRecord *action_work, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    GridPoint direction_vectors[8];
    s32 state;
    u16 timer;
    u16 flags;
    u8 *animations;
    s32 direction_index;
    ObjectNodeHeader * spawned_actor;
    SpriteFrameState *spawned_sprite;
    WeadogFlightBody *spawned_work;
    ObjectPosition *spawned_pos;
    void *direction_ptr;
    s16 direction_y;
    s32 tile_coord;

    __builtin_memcpy(direction_vectors, weadog_slot_g_direction_steps, sizeof(direction_vectors));
    state = action_work->action_phase;
    switch (state) {
    case 0:
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        timer = action_work->action_timer + 1;
        action_work->action_timer = timer;
        if (((s16)timer < 0x14) && !(sprite->flags & 0x8000)) {
            return;
        }
        animations = D_80174F18;
        sprite->frameTable = animations;
        select_sprite_entry(sprite,
            animations[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        action_work->action_timer = 0x14;
        action_work->action_phase = action_work->action_phase + 1;
    case 1:
        if (((s16)(action_work->action_timer) == 0x13) || (sprite->flags & 0x8000)) {
            if (!(sprite->flags & 0x8000)) {
                play_sound_if_enabled(0x707);
            }
            spawned_actor = allocate_flagged_object_node(0x12);
            if (spawned_actor != 0) {
                spawned_actor->update_callback = weadog_object_callback;
                spawned_work = NODE_BODY(spawned_actor);
                register_node(spawned_actor, project_sprite_chain);
                spawned_sprite = spawned_actor->sprite;
                spawned_sprite->flags &= 0xFFF3;
                spawned_work->owner = action_work;
                spawned_pos = spawned_actor->position;
                spawned_pos->x.w.i = position->x.unsigned_parts.integer;
                spawned_pos->y.w.i = position->y.unsigned_parts.integer;
                spawned_pos->z.w.i = position->z.unsigned_parts.integer - 0x20;
                direction_ptr = &direction_vectors;
                direction_index = ((u16)actor->facing >> 7) & 0x1C;
                spawned_work->velocity_x = direction_vectors[direction_index >> 2].x << 0x13;
                direction_index = ((u16)actor->facing >> 7) & 0x1C;
                spawned_work->velocity_y =
                    (*(u16 *)(direction_index + (u8 *)direction_ptr + 2)) << 0x13;
                spawned_work->velocity_z = 0xFFF20000;
                spawned_work->gravity = 0x14900;
                spawned_work->direction = ((u16)actor->facing >> 9) & 7;
                spawned_sprite = spawned_actor->sprite;
                spawned_sprite->scale_y = 0x1000;
                spawned_sprite->scale_x = 0x1000;
                direction_index = ((u16)actor->facing >> 7) & 0x1C;
                direction_ptr = direction_index + (u8 *)direction_ptr;
                direction_y = *(volatile u16 *)((u8 *)direction_ptr + 2);
                spawned_sprite->depth_bias = direction_y * 6;
                action_work->unk_A4.halves.low.s = 0x4D;
                tile_coord = position->x.w.i;
                if (tile_coord < 0) {
                    tile_coord += 0x3F;
                }
                spawned_work->spawner_tile_x = tile_coord >> 6;
                tile_coord = position->y.w.i;
                spawned_work->spawner_tile_y = (tile_coord / 64);
                spawned_sprite->color.c.b = 0x80;
                spawned_sprite->color.c.g = 0x80;
                spawned_sprite->color.c.r = 0x80;
                spawned_sprite->source = D_80077C50;
            }
        }
        if (((s16)(action_work->action_timer) == 0x12) || (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
        }
        timer = action_work->action_timer - 1;
        action_work->action_timer = timer;
        if (((s32)(timer << 16) <= 0) || (sprite->flags & 0x8000)) {
            action_work->action_phase = action_work->action_phase + 1;
            sprite->flags &= 0xF7FF;
            return;
        }
        return;
    case 2:
        if (((sprite->unk_04 == state) && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
            action_work->action_timer = 0x23;
        }
        timer = action_work->action_timer - 1;
        action_work->action_timer = timer;
        if (((s32)(timer << 16) <= 0) || (sprite->flags & 0x8000)) {
            action_work->action_timer = 0;
            sprite->flags &= 0xF7FF;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        if (sprite->frameTable == weadog_frame_set_3) {
            return;
        }
        sprite->frameTable = weadog_frame_set_3;
        sprite->flags &= 0xF7FF;
        direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
        select_sprite_entry(sprite, U8_AT(sprite->frameTable, direction_index), 0);
        action_work->action_phase = action_work->action_phase + 1;
        return;
    case 3:
        if (action_work->unk_A4.halves.low.s != 0x4D) {
            spend_actor_mp(actor, 0x2000);
            action_work->unk_8C.address = &weadog_action_resume_address;
            g_dungeon_status.active_actor = 0;
            actor->action_flags &= 0x7FFF;
        }
    }
}
