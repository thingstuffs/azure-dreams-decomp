#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct Copy48 {
    u32 words[12];
} Copy48;

extern void select_sprite_entry(void *, u8, s32);
extern void play_sound_if_enabled(s32);
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);

extern u8 D_800D58D8[];
extern s8 view_direction_depth_biases[];
extern u8 uboat_default_frames[];
extern u8 D_800E2410[];
#include "dungeon/monster/u_boat.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

typedef struct S_80173A60_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x14];
    void * unk_AC;
} S_80173A60_4;   /* state in advance_actor_item_action */

   /* target in advance_actor_item_action */

typedef struct S_80173A60_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173A60_9;   /* global in advance_actor_item_action */

/* Advances an actor's item action, spawning its visual effect and restoring idle state. */
/* Starts a targeted spell, creates a directional sprite copy at frame 3, signals it at frame 19, then
 * updates status. */
void advance_actor_item_action(ActorRecord *actor_state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s16 use_player;
    u8 *item_id;
    s32 offset_x;

    use_player = 0;
    switch (actor_state->action_phase.u) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = (actor->action_flags & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                use_player = 1;
            case 2:
                item_id = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player = 1;
            case 1:
                item_id = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player = 1;
            case 0:
                item_id = (u8 *)actor + 8;
                break;
            default:
                item_id = 0;
                break;
            }
        } else {
            switch (actor->action_flags & 0x3FFF) {
            case 3:
                item_id = (u8 *)actor + 0xE;
                break;
            case 2:
                item_id = (u8 *)actor + 0xB;
                break;
            case 1:
                item_id = (u8 *)actor + 8;
                break;
            default:
                item_id = 0;
                break;
            }
        }

        if (*item_id != 0) {
            s32 use_player_test;
            void *linked_actor;

            actor_state->action_state_flags &= 0xFF7F;
            use_player_test = use_player;
            if (use_player_test != 0) {
                u8 *linked_sprite;

                linked_actor = primary_actor_record;
                actor->target = linked_actor;
                linked_sprite = *(u8 * *)&((ObjectNodeHeader *)((u8 *)linked_actor - 0x20))->sprite;
                actor->target_tile_x = linked_sprite[0x24];
                offset_x = linked_sprite[0x25];
                actor->target_tile_y = offset_x;
            } else if (item_action_definitions[*item_id].kind == 2) {
                linked_actor = actor->target;
                if (linked_actor != 0) {
                    u8 *linked_sprite;

                    linked_sprite = *(u8 * *)&((ObjectNodeHeader *)((u8 *)linked_actor - 0x20))->sprite;
                    actor->target_tile_x = linked_sprite[0x24];
                    offset_x = linked_sprite[0x25];
                    actor->target_tile_y = offset_x;
                }
            } else {
                s32 offset_y;

                s32 abs_x;
                offset_x = (s32)scan_actor_along_heading(actor,
                                       sprite->tile_x,
                                       sprite->tile_y,
                                       actor->facing, 0x10);
                actor->target = (void *)offset_x;
                abs_x = abs(actor->target_tile_x);
                offset_y = abs(actor->target_tile_y);
                actor->target_tile_x = abs_x;
                actor->target_tile_y = offset_y;
            }

            if (create_actor_spell_effect(actor, item_id, use_player,
                              (u16 *)((u8 *)actor_state + 0x98)) == 0) {
                return;
            }
            actor_state->action_timer.u = 0;
            actor_state->action_phase.u++;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(actor);
        (*((u8 *)actor + 0x6D))--;
        actor_state->unk_8C.address = uboat_behavior_entry;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x0800;
            return;
        }
        sprite->flags &= 0xF7FF;
        actor_state->action_phase.u++;
        play_sound_if_enabled(0x703);
                        /* fall through */

    case 2:
    {
        u16 timer;

        timer = actor_state->action_timer.u + 1;
        actor_state->action_timer.u = timer;
        if ((s16)timer == 3) {
            ObjectNodeHeader *effect;

            effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
            if (effect != 0) {
                S_80173A60_4 *effect_state;
                SpriteFrameState *effect_sprite;
                ObjectPosition *effect_pos;
                u8 *anim_table;
                u8 *anim_entry;
                s8 *height_offsets;
                s32 direction_index;

                effect_state = (S_80173A60_4 *)(((u8 *)effect) + 0x20);
                effect_state->unk_96 = 0x10;
                effect->update_callback = D_800D58D8;
                effect_state->unk_AC = motion;
                effect_state->unk_94 = (*(u16 *)((u8 *)actor + 0x2A));
                effect_sprite = effect->sprite;
                *(Copy48 *)effect_sprite = *(Copy48 *)sprite;
                effect_sprite->scale_y = 0x1000;
                effect_sprite->scale_x = 0x1000;
                effect_sprite->color.c.b = 0x80;
                effect_sprite->color.c.g = 0x80;
                effect_sprite->color.c.r = 0x80;
                register_node(effect, project_sprite_chain);

                anim_table = D_800E2410;
                effect_sprite->frameTable = anim_table;
                anim_entry = (u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle +
                          actor->facing + 0x100) >> 9) & 7) + (u32)anim_table);
                select_sprite_entry(effect_sprite, *anim_entry, 0);
                effect_sprite->flags &= 0xFFF3;

                direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle +
                          actor_state->facing + 0x100) >> 9) & 7;
                height_offsets = view_direction_depth_biases;
                effect_sprite->depth_bias = -(height_offsets[direction_index] * 4);
                effect_state->unk_94 =
                    (actor_state->facing >> 9) & 7;
                effect_state->unk_2A = actor_state->facing;

                effect_pos = effect->position;
                effect_pos->x.w.i = ((u16)motion->x.w.i);
                effect_pos->y.w.i = ((u16)motion->y.w.i);
                effect_pos->z.w.i = ((u16)motion->z.w.i);
            }
        }

        if (actor_state->action_timer.s == 0x10) {
            u8 *anim_table;
            s32 direction_index;

            anim_table = uboat_default_frames;
            sprite->frameTable = anim_table;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, anim_table[direction_index], 3);
            if (actor_state->unk_B0.bytes[0] == 0) {
                create_owner_linked_directional_object(actor_state, motion, sprite);
            }
        }

        if (actor_state->action_timer.s == 0x13 ||
            (sprite->flags & 0xE000)) {
            actor_state->action_state_flags |= 0x80;
            play_sound_if_enabled(0x81B);
        }

        if (actor_state->action_timer.s < 0x19 &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        actor_state->action_phase.u++;
        return;
    }

    case 3:
    {
        S_80173A60_9 *action_status;

        action_status = ((S_80173A60_9 *)(&g_dungeon_status));
        if (action_status->unk_0C != 0) {
            return;
        }
        actor_state->action_timer.u = 0;
        if (action_status->unk_0C != 0) {
            return;
        }
        action_status->unk_0A--;
        actor_state->unk_8C.address = uboat_behavior_entry;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        (*((u8 *)actor + 0x6D))--;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    }
    }
}
