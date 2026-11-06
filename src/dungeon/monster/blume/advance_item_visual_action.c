#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "dungeon/player/object.h"
#include "sdk/libc.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern void select_sprite_entry(void *, s32, s32);

extern u8 D_80170FD8[];

extern u8 blume_action_resume_address[];
#include "dungeon/monster/blume.h"
#include "dungeon/monster/blume/fading_motion.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"

extern u8 D_80175424[12];


   /* coords in advance_item_visual_action */

/* Process item use, spawn its visual effect, and finish the action when ready. */
/* Starts a targeted spell, emits randomly colored sprite particles during casting, then restores movement
 * and status. */
void advance_item_visual_action(ActorRecord *controller, ObjectPosition *motion, SpriteFrameState *action_sprite, ActorRecord *actor_body)
{
    u8 *item_slot;
    s16 use_player;
    u8 state;
    ActorRecord *target_actor;

    use_player = 0;
    state = controller->action_phase.u;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor_body + 0x1C)) & ACTOR_PLAYER_SIDE) {
            switch (actor_body->action_flags & 0x3FFF) {
            case 7:
                use_player = 1;
                /* fallthrough */
            case 3:
                item_slot = (u8 *)actor_body + 0xE;
                break;
            case 6:
                use_player = 1;
                /* fallthrough */
            case 2:
                item_slot = (u8 *)actor_body + 0xB;
                break;
            case 5:
                use_player = 1;
                /* fallthrough */
            case 1:
                item_slot = (u8 *)actor_body + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor_body->action_flags & 0x3FFF) {
            case 3:
                item_slot = (u8 *)actor_body + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor_body + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor_body + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            controller->action_state_flags &= 0xFF7F;
            {
                s32 target_player;

                target_player = use_player;
                if (target_player != 0) {
                    SpriteFrameState *item_data;

                    target_actor = primary_actor_record;
                    actor_body->target = target_actor;
                    item_data = NODE_HEADER(target_actor)->sprite;
                    actor_body->target_tile_x = item_data->tile_x;
                    actor_body->target_tile_y = item_data->tile_y;
                } else {
                    u8 *item_table;
                    u8 item_id;
                    u32 item_data;

                    item_table = item_action_definitions;
                    item_id = *item_slot;
                    item_data = (item_id * 20 + item_table)[0x12];
                    if (item_data == 2) {
                        target_actor = actor_body->target;
                        if (target_actor != 0) {
                            item_data = (u32)NODE_HEADER(target_actor)->sprite;
                            actor_body->target_tile_x = ((SpriteFrameState *)item_data)->tile_x;
                            actor_body->target_tile_y = ((SpriteFrameState *)item_data)->tile_y;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_actor_along_heading(
                            actor_body, action_sprite->tile_x, action_sprite->tile_y,
                            actor_body->facing, 0x10);
                        actor_body->target = (void *)dx;
                        dx = abs(actor_body->target_tile_x);
                        dy = abs(actor_body->target_tile_y);
                        actor_body->target_tile_x = dx;
                        actor_body->target_tile_y = dy;
                    }
                }
            }

            if (create_actor_spell_effect(actor_body, item_slot, use_player, &controller->action_state_flags) == 0) {
                return;
            }
            controller->action_phase.u = controller->action_phase.u + 1;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, action_sprite->tile_x, action_sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(actor_body);
        (*((u8 *)actor_body + 0x6D))--;
        controller->unk_8C.address = blume_action_resume_address;
        actor_body->target_tile_y = 0;
        actor_body->target_tile_x = 0;
        actor_body->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            action_sprite->flags |= 0x800;
            return;
        }
        action_sprite->flags &= 0xF7FF;
        controller->action_phase.u++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            s16 effect_count;
            s32 dim_channel;

            effect_count = 0;
            dim_channel = 0x20;
            for (; effect_count < 1; effect_count++) {
                ObjectNodeHeader *effect_node;

                effect_node = allocate_flagged_object_node(0x212);
                if (effect_node != 0) {
                    BlumeFadingMotionBody *effect_data;
                    SpriteFrameState *sprite;
                    ObjectPosition *effect_pos;
                    s32 dx;
                    s32 dy;
                    s32 color_bits;

                    effect_data = NODE_BODY(effect_node);
                    effect_data->ticks_left = 0x13;
                    effect_data->unk_00 = 0;
                    effect_node->update_callback = update_fading_motion_effect;
                    register_node(effect_node, D_80170FD8);

                    sprite = effect_node->sprite;
                    sprite->tpage_abr = dim_channel;
                    sprite->flags |= 0x0C;
                    effect_pos = effect_node->position;
                    effect_pos->x.unsigned_parts.integer = ((u16)motion->x.w.i);
                    effect_pos->y.unsigned_parts.integer = ((u16)motion->y.w.i);
                    effect_pos->z.unsigned_parts.integer = ((u16)motion->z.w.i);

                    dx = (rand() & 0x3F) - 0x20;
                    dy = (rand() & 0x3F) - 0x20;
                    effect_pos->x.unsigned_parts.integer += dx;
                    effect_pos->y.unsigned_parts.integer += dy;
                    sprite->scale_x = 0x1000;
                    sprite->scale_y = 0x1000;

                    color_bits = rand() & 7;
                    if (color_bits & 1) {
                        sprite->color.c.r = 0x80;
                    } else {
                        sprite->color.c.r = dim_channel;
                    }
                    if (color_bits & 2) {
                        sprite->color.c.g = 0x80;
                    } else {
                        sprite->color.c.g = dim_channel;
                    }
                    if (color_bits & 4) {
                        sprite->color.c.b = 0x80;
                    } else {
                        sprite->color.c.b = dim_channel;
                    }
                    effect_data->initial_red = sprite->color.c.r;
                    effect_data->initial_green = sprite->color.c.g;
                    effect_data->initial_blue = sprite->color.c.b;
                    sprite->clut = 0x7DCF;
                    sprite->flags |= 0x100;
                    (*(Copy12 *)effect_data->sprite_entries) = *(Copy12 *)D_80175424;
                    sprite->source = effect_data->sprite_entries;
                    effect_data->accumulated_step = 8;
                    effect_data->late_countdown = 4;
                }
            }
        }

        if ((action_sprite->unk_04 == 6 &&
             (action_sprite->flags & 0x1000)) ||
            (action_sprite->flags & 0xE000)) {
            controller->action_state_flags |= 0x80;
        }
        if ((action_sprite->unk_04 == 9 &&
             (action_sprite->flags & 0x1000)) ||
            (action_sprite->flags & 0xE000)) {
            action_sprite->flags |= 0x800;
            controller->action_timer.u = 0x14;
            controller->action_phase.u = controller->action_phase.u + 1;
            return;
        }
        return;

    case 3:
        {
            s16 timer;

            if ((g_dungeon_status.active_actor) == 0) {
                controller->action_timer.u = 0;
            }
            timer = controller->action_timer.u - 1;
            controller->action_timer.u = timer;
            if (timer <= 0) {
                controller->action_timer.u = 0;
                action_sprite->flags &= 0xF7FF;
            }
            if (!(action_sprite->flags & 0xE000)) {
                return;
            }
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, action_sprite->tile_x, action_sprite->tile_y);
            if (*(u8 * *)&action_sprite->frameTable != blume_direction_frames) {
                u8 *facing_frames;
                s32 facing_index;

                facing_frames = blume_direction_frames;
                action_sprite->frameTable = facing_frames;
                facing_index = ((g_game_work.view.camera_rotation.parts.viewAngle + actor_body->facing + 0x100) >> 9) & 7;
                select_sprite_entry(action_sprite, facing_frames[facing_index], 0);
                action_sprite->flags &= 0xF7FF;
            }
            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            controller->unk_8C.address = blume_action_resume_address;
            advance_status_timers(actor_body);
            actor_body->target_tile_y = 0;
            actor_body->target_tile_x = 0;
            (*((u8 *)actor_body + 0x6D))--;
            actor_body->action_flags &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }

        return;
    default:
        return;
    }
}
