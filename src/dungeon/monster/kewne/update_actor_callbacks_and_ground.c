#include "common.h"
#include "dungeon/monster/kewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "engine/texture.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "sdk/libgte.h"
#include "slus.h"

typedef s32 (*ActorCallback)(void *, void *, void *, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern u8 kewne_action_resume_address[12];
extern ActorCallback kewne_callbacks[16];
/* Update actor callbacks, movement, facing, animation, and ground height. */
void update_actor_callbacks_and_ground(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *sprite)
{
    ActorRecord *entry_actor = actor;
    s16 direction_index;
    s32 view_direction;
    s16 old_state;
    s16 height_offset;
    s32 ground_height;
    u16 sprite_flags;
    u16 anim_flags;
    u32 clear_mask;
    s32 actor_flags;
    s32 bob_step;
    s32 ground_offset;
    s32 bob_offset;
    s32 height_adjust;
    s32 physics_flags;
    ActorRecord *actor_base = actor;
    ActorActionHandler callback;
    u32 initial_flags = g_dungeon_status.flags;
    if (initial_flags & 0x2000) {
        callback = actor->unk_8C.handler;
        if (callback == (ActorActionHandler) kewne_action_resume_address) {
            callback(entry_actor, position, sprite, entry_actor);
            return;
        }
        else {
            actor->movement_queue_state &= 0x7F;
            return;
        }
    }
    old_state = actor->pending_turn_updates;
    if (refresh_actor_facing_and_lifecycle(actor, position, sprite, actor) != 0) {
        return;
    }
    if (actor->unk_8C.handler != 0) {
        actor->unk_8C.handler(actor, position, sprite, actor);
    }
    kewne_callbacks[actor->action_id](actor, position, sprite, actor);
    if (((s16) old_state) != actor->pending_turn_updates) {
        try_move_actor_to_valid_position(actor, position, sprite, actor);
    }
    position->x.v += position->velocity_x;
    position->y.v += position->velocity_y;
    if ((!(actor->flags1C & 0x40000)) && (!(actor->action_state_flags & 8))) {
        position->velocity_z += actor->unk_9D * 0x14000;
        actor->unk_9D++;
    }
    else {
        actor->unk_9D = 0;
    }
    actor->unk_90.value += position->velocity_z;
    view_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor_base->facing) + 0x100) >> 9;
    bob_step = view_direction & 7;
    direction_index = bob_step;
    if (actor->unk_94 != direction_index) {
        select_indirect_table_entry(sprite, *((u8 *) ((sprite->frameTable) + direction_index)),
            sprite->unk_04);
        actor->unk_94 = bob_step;
    }
    if (dir_sprite_flag[direction_index] != 0) {
        sprite_flags = (sprite->flags) | 1;
        sprite->flags = sprite_flags;
    }
    else {
        sprite_flags = (sprite->flags) & 0xFFFE;
        sprite->flags = sprite_flags;
    }
    anim_flags = sprite->flags;
    /* Select the animation path; afterwards physics_flags carries the flight bit. */
    physics_flags = anim_flags & 0x8000;
    switch (physics_flags) {
    case 0:
        apply_monster_koyaw_data(actor_base->flags1C, ((u8 *) sprite) + 0xC);
        if (!(actor_base->flags1C & 0x20)) {
            if (!((sprite->flags) & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        }
        else {
            sprite->flags |= 0x7000;
            actor_base->flags1C &= 0xFFFBFFFF;
        }
        actor_base->flags1C &= 0xF7FFFFFF;
        physics_flags = actor_base->flags1C & 0x40000;
        if (physics_flags) {
            if ((!((sprite->flags) & 0x40))
                && ((sprite->frameTable) == kewne_direction_frames)) {
                if ((*(u16 *)&sprite->unk_04) == 0x100) {
                    actor->unk_9E = 0;
                    actor->unk_A0.value = 0;
                }
                if (((u32) ((((u8)(sprite->unk_04))) - 1)) < 4) {
                    s16 bob_tick = actor->unk_9E;
                    actor->unk_9E++;
                    actor->unk_A0.value += rsin(bob_tick * 0xAA) << 5;
                }
                else {
                    s16 bob_tick = actor->unk_9E;
                    actor->unk_9E++;
                    actor->unk_A0.value += rsin(bob_tick * 0xAA) << 6;
                }
            }
            if (!(actor->action_state_flags & 8)) {
                height_offset = actor->unk_90.parts.high;
                if (height_offset >= (-0x1F)) {
                    actor->unk_90.parts.high = ((u16) height_offset) - 8;
                }
                else if (height_offset < (-0x28)) {
                    actor->unk_90.parts.high = ((u16) height_offset) + 8;
                }
            }
            break;
        }
        /* Fall through with zero flags to share the ground-physics path. */
    default:
        if (physics_flags) {
            sprite->flags = (anim_flags & 0x800) ? (anim_flags & 0x8FFF) : (anim_flags | 0x7000);
            clear_mask = 0xF7FFFFFF;
            actor_flags = actor_base->flags1C;
            actor_flags &= clear_mask;
            actor_base->flags1C = actor_flags;
            actor_flags &= 0x40000;
            physics_flags = actor_flags;
        }
        if (!physics_flags) {
            bob_offset = actor->unk_A0.value;

            actor->unk_9E = 0;
            actor->unk_A0.value = 0;
            actor->unk_90.value -= bob_offset;
            if (!(actor->action_state_flags & 8)) {
                ground_height = sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
                    (s16) (actor_base->ground_height - 0x20));
                ground_offset = ground_height - (u16)actor_base->ground_height;
                if (((s16) ground_offset) < actor->unk_90.parts.high) {
                    actor->unk_90.parts.high = ground_offset;
                    actor->unk_9D = 0;
                    position->velocity_z = 0;
                    actor_base->flags1C |= 0x08000000;
                }
            }
        }
        else {
            if ((!((sprite->flags) & 0x40)) && ((sprite->frameTable) == kewne_direction_frames)) {
                if ((*(u16 *)&sprite->unk_04) == 0x100) {
                    actor->unk_9E = 0;
                    actor->unk_A0.value = 0;
                }
                if (((u32) ((((u8)(sprite->unk_04))) - 1)) < 4) {
                    s16 bob_tick = actor->unk_9E;
                    actor->unk_9E++;
                    actor->unk_A0.value += rsin(bob_tick * 0xAA) << 5;
                }
                else {
                    s16 bob_tick = actor->unk_9E;
                    actor->unk_9E++;
                    actor->unk_A0.value += rsin(bob_tick * 0xAA) << 6;
                }
            }
            if (!(actor->action_state_flags & 8)) {
                height_offset = actor->unk_90.parts.high;
                if (height_offset >= (-0x1F)) {
                    actor->unk_90.parts.high = ((u16) height_offset) - 8;
                }
                else if (height_offset < (-0x28)) {
                    actor->unk_90.parts.high = ((u16) height_offset) + 8;
                }
            }
        }
    }
    actor_flags = actor_base->flags1C;

    if (actor_flags & 0x40000000) {
        actor_base->flags1C = actor_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(((sprite->tile_x) << 6) | 0x20, ((sprite->tile_y) << 6) | 0x20, (s16) (actor_base->ground_height - 0x20));
        if (((s16) ground_height) < 0x200) {
            height_adjust = (u16)actor_base->ground_height - ground_height;
            actor->unk_90.parts.high += height_adjust;
            actor_base->ground_height = ground_height;
        }
    }
    position->z.w.i = (actor_base->ground_height + actor->unk_90.parts.high) - actor->unk_A0.parts.high;
    sprite->flags |= 0x40;
}
