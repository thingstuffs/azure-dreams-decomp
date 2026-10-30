#include "shared/object_node.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171E20_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80171E20_0;   /* arg0 in update_actor_dungeon_behavior_and_animation */

typedef struct S_80171E20_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171E20_1;   /* arg3 in update_actor_dungeon_behavior_and_animation */

extern void select_sprite_entry(void *, u8, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);

extern void func_80172384(void *, void *, void *, void *);
extern s32 advance_item_action_sequence(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor); /* Unprototyped: this consumer uses the return value, but the owner definition is void. */
extern void func_80172F38(ActorRecord *action_state, ObjectPosition *action_context, void *sprite, ActorRecord *actor);
extern s32 func_80173050(void *, void *, void *, s32);
extern void func_80174890(void *, void *, void *, void *);
void begin_actor_directional_target_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);

#include "dungeon/monster/blume.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/monster/glacier.h"

extern u8 D_801753C4[];
extern u8 D_801753F4[];
extern u8 D_801753FC[];


/* Updates an actor's dungeon behavior, facing, and animation. */
/* Selects Blume's movement, target actions, spells, and turn processing, restoring directional idle frames
 * when ready. */
void update_actor_dungeon_behavior_and_animation(ActorRecord *actor_in, ObjectPosition *actor_data_in, SpriteFrameState *sprite_in, ActorRecord *status_in) {
    u32 initial_flags = g_dungeon_status.flags;
    s16 distance;
    s32 status_flags;
    s8 tile_id;
    s16 facing;
    u16 action_flags;
    u8 *anim_table;
    ActorRecord *player;

    if (initial_flags & 0x1000) {
        actor_in->action_id.u = 14;
        func_80172384(actor_in, actor_data_in, sprite_in, status_in);
        return;
    }

    if (status_in->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor_in, actor_data_in, sprite_in, status_in);
        if (*(u8 **)&sprite_in->frameTable == blume_direction_frames_2) {
            return;
        }
        {
            u8 *early_anim_table = D_801753FC;
            (sprite_in->frameTable) = early_anim_table;
            select_sprite_entry(
                sprite_in,
                early_anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + status_in->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171E20_1 *)status_in)->unk_1C & 0x200) {
        if (*(u8 **)&sprite_in->frameTable == blume_direction_frames_2) {
            actor_in->action_id.u = 13;
            actor_in->action_phase.u = 1;
            ((S_80171E20_0 *)actor_in)->unk_8C = 0;
            ((S_80171E20_1 *)status_in)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_in, actor_data_in, sprite_in, D_801753FC) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((S_80171E20_1 *)status_in)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }

        {
            u8 current_state = actor_in->action_id.u;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = blume_direction_frames;
                if (*(u8 **)&sprite_in->frameTable != anim_table) {
                    (sprite_in->frameTable) = anim_table;
                    select_sprite_entry(
                        sprite_in,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + status_in->facing + 0x100) >> 9) & 7],
                        0);
                }
                actor_in->action_id.u = next_state;
            }
        }

        actor_in->action_state_flags &= 0xFFF3;

        if (status_in->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_in, actor_data_in, sprite_in, D_801753C4) != 0) {
                return;
            }
        }

        if (((S_80171E20_1 *)status_in)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, actor_data_in, sprite_in, status_in);
            func_80174890(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }

        if ((s16)can_entity_gain_level(status_in) != 0) {
            process_selected_actor_record(actor_in, actor_data_in, sprite_in, status_in);
        }
    }

    tile_id = find_active_rect_containing_point(sprite_in->tile_x, sprite_in->tile_y);
    sprite_in->room_index = tile_id;

    if (status_in->pending_turn_updates > 0) {
        if (((S_80171E20_1 *)status_in)->unk_1C & 0x20) {
            update_actor_status_and_mp(status_in);
            return;
        }
        if (*(u16 *)&sprite_in->tile_x == reference_tile_object.tile_position.word) {
            initialize_item_sprite_frame(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }
        action_flags = status_in->action_flags;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((s16)check_entity_relation(
                            status_in, previous_actor) != 0) {
                        return;
                    }
                }
            }
            if ((s16)func_80173050(actor_in, actor_data_in, sprite_in, 0) == 0) {
                return;
            }
            action_flags = status_in->action_flags | 0x4000;
            status_in->action_flags = action_flags;
            if ((action_flags & 0x8000) == 0) {
                initialize_item_sprite_frame(actor_in, actor_data_in, sprite_in, status_in);
            return;
            }
        }

        switch (status_in->action_flags & 0x3FFF) {
        case 8:
            if ((s16)advance_item_action_sequence(actor_in, actor_data_in, sprite_in, status_in) != 0) {
                return;
            }
            func_80172F38(actor_in, actor_data_in, sprite_in, status_in);
            return;
        case 9:
            begin_actor_directional_target_action(actor_in, actor_data_in, sprite_in, status_in);
            return;
        case 5:
        case 6:
        case 7:
            facing = get_rounded_facing_and_rounding_flag(
                sprite_in->tile_x, sprite_in->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            player = primary_actor_record;
            status_in->facing = facing;
            if (player->action_id.u == 0x11) {
                begin_actor_spell_action(actor_in, actor_data_in, sprite_in, D_801753F4, update_actor_dungeon_behavior_and_animation);
                return;
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(status_in);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_in, actor_data_in, sprite_in, D_801753F4, update_actor_dungeon_behavior_and_animation);
            return;
        default:
            initialize_item_sprite_frame(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }
    }

    status_flags = ((S_80171E20_1 *)status_in)->unk_1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_id < 0) ||
            !(dungeon_rooms[tile_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)test_neighbor_position_relation(
                        sprite_in->tile_x, sprite_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    status_in->facing = get_rounded_facing_and_rounding_flag(
                        sprite_in->tile_x, sprite_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite_in->flags & 0x40) {
        return;
    }
    anim_table = blume_direction_frames;
    if (*(u8 **)&sprite_in->frameTable == anim_table) {
        return;
    }

    (sprite_in->frameTable) = anim_table;
    select_sprite_entry(
        sprite_in,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + status_in->facing + 0x100) >> 9) & 7],
        0);
}
