#include "shared/audio_commands.h"
#include "dungeon/monster/baloon.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "sdk/libc.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void spawn_directional_random_velocity_effect(void *, s32);

extern u8 baloon_default_frames[];
extern u8 baloon_fall_frames[8];
extern u8 D_800E2398[8];

typedef struct S_80173B08_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173B08_2;   /* linked in update_actor_item_use */

/* Updates the actor's item-use state, animation, and effects. */
/* Starts a targeted spell, settles to ground height, emits forward and surrounding particles, then
 * restores its hover. */
void update_actor_item_use(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *item_slot;
    u32 stage;
    s32 flag;
    s16 effect_count;
    u32 state;
    void *target;

    flag = 0;
    state = body->action_phase.u;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = (actor->action_flags & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                flag = 1;
            case 2:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 5:
                flag = 1;
            case 1:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 4:
                flag = 1;
            case 0:
                item_slot = (u8 *)actor + 8;
                break;
            case 3:
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind;

            action_kind = actor->action_flags & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            body->action_state_flags &= 0xFF7F;
            {
                u8 is_special;
                S_80173B08_2 *item_id;

                is_special = flag;
                if (is_special != 0) {
                    target = primary_actor_record;
                    actor->target = target;
                    item_id = (S_80173B08_2 *)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    actor->target_tile_x = item_id->unk_24;
                    actor->target_tile_y = item_id->unk_25;
                } else {
                    item_id = (void *)(*item_slot);
                    if (item_action_definitions[((u8)item_id)].kind == 2) {
                        target = actor->target;
                        if (target != 0) {
                            item_id = (S_80173B08_2 *)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                            actor->target_tile_x = item_id->unk_24;
                            actor->target_tile_y = item_id->unk_25;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_actor_along_heading(
                            actor, sprite->tile_x, sprite->tile_y,
                            actor->facing, 0x10);
                        actor->target = (void *)dx;
                        dx = abs(actor->target_tile_x);
                        dy = abs(actor->target_tile_y);
                        actor->target_tile_x = dx;
                        actor->target_tile_y = dy;
                    }
                }
            }

            if (create_actor_spell_effect(actor, item_slot, flag,
                              (u8 *)body + 0x98) == 0) {
                return;
            }
            body->action_phase.u++;
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            g_dungeon_status.active_actor = 0;
            primary_actor_record->unk_A4.halves.high.u--;
            advance_status_timers(actor);
            (*((u8 *)actor + 0x6D))--;
            body->unk_8C.address = update_actor_turn_behavior;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags &= 0x7FFF;
            return;
        }

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        body->action_phase.u++;
        play_sound_if_enabled(0x703);

    case 2:
        body->action_phase.u++;
        body->action_state_flags &= 0xFFF7;
        (*(u32 *)((u8 *)actor + 0x1C)) &= 0xFFFBFFFF;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;

    case 3:
        if (sprite->flags & 0x8000) {
            body->action_phase.u = 7;
            sprite->flags |= 0x6000;
            body->action_state_flags |= 0x80;
            return;
        }
        {
            s16 floor_height;

            floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                  ((u16)motion->y.w.i),
                                  (s16)((*(u16 *)((u8 *)actor + 0x88)) - 0x20));
            if ((body->unk_90.parts.high.s -
                 (s16)(floor_height - (*(u16 *)((u8 *)actor + 0x88)))) != 0) {
                return;
            }
        }
        body->action_timer.u = 0;
        stage = body->action_phase.u;
        stage++;
        body->action_phase.u = stage;
        sprite->frameTable = D_800E2398;
        select_sprite_entry(sprite, D_800E2398[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        return;

    case 4:
    {
        s16 timer;

        timer = body->action_timer.u;
        body->action_timer.u = timer + 1;
        if (timer < 12 && !(sprite->flags & 0xE000)) {
            return;
        }
    }
        body->action_state_flags |= 0x80;
        sprite->flags |= 0x800;
        body->action_timer.u = 0x12;
        body->action_phase.u++;
        effect_count = 0;
        do {
            spawn_angled_random_velocity_effect((u8 *)body - 0x20,
                          actor->facing, 0xE0E0E0);
            effect_count++;
        } while ((s16)effect_count < 3);
        return;

    case 5:
        if ((g_dungeon_status.active_actor) == 0) {
            body->action_timer.u = 0;
        }
        if (body->action_timer.s >= 10) {
            effect_count = 0;
            do {
                spawn_angled_random_velocity_effect((u8 *)body - 0x20,
                              actor->facing, 0xE0E0E0);
                effect_count++;
            } while ((s16)effect_count < 3);
        }
        if ((u32)(body->action_timer.u - 10) < 7) {
            s16 angle;

            for (angle = 0; angle < 0x1000; angle += 0x200) {
                if (angle != actor->facing) {
                    effect_count = 0;
                    do {
                        spawn_directional_random_velocity_effect((u8 *)body - 0x20, angle);
                        effect_count++;
                    } while ((s16)effect_count <= 0);
                }
            }
        }
        {
            s16 timer;

            timer = body->action_timer.u - 1;
            body->action_timer.u = timer;
            if (timer > 0 && !(sprite->flags & 0xE000)) {
                return;
            }
        }
        body->action_timer.u = 0;
        sprite->flags &= 0xF7FF;
        state = body->action_state_flags;
        stage = body->action_phase.u;
        stage++;
        state |= 8;
        body->action_phase.u = stage;
        body->action_state_flags = state;
        sprite->frameTable = baloon_fall_frames;
        select_sprite_entry(sprite, baloon_fall_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        return;

    case 6:
        if (body->unk_90.parts.high.s >= -0x1F) {
            body->unk_90.parts.high.u -= 4;
            return;
        }
        body->action_phase.u++;

    case 7:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (*(u8 * *)&sprite->frameTable != baloon_default_frames) {
            sprite->frameTable = baloon_default_frames;
            select_sprite_entry(
                sprite,
                baloon_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->unk_9E.u = 0;
            body->action_state_flags |= 8;
            (*(u32 *)((u8 *)actor + 0x1C)) |= 0x40000;
            body->unk_90.parts.high.s = -0x20;
            sprite->flags &= 0xFFF3;
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            body->unk_8C.address = update_actor_turn_behavior;
            advance_status_timers(actor);
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        (*((u8 *)actor + 0x6D))--;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

        return;
    }
}
