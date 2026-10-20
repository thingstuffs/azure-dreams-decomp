#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8014D3CC(void *, void *, void *, void *);
extern void func_8014D624(void *, void *, void *, void *);
extern s32 func_8014DDD0(void *, void *, void *, void *);
extern void func_8014DF94(void *, void *, void *, void *);
extern s32 func_8014E0AC(void *, void *, void *, s32);
extern void func_8014FF28(void *, void *, void *, void *);

extern u8 D_8014CE84;
extern u8 D_80150820[];
extern u8 D_80150830[];
extern u8 D_80150848[];
extern u8 D_80150858[];
extern u8 D_80150860[];

typedef struct ActorSpriteView {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x; u8 y; } bytes;
        u16 packed;
    } tile;
    u8 room;
    u8 pad_27[0x5];
    void * animationTable;
} ActorSpriteView;

void update_dungeon_actor_behavior_and_targets(void *controller, void *context, void *entity, EntityRec *actor_state)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8014D3CC(controller, context, entity, actor_state);
        return;
    }

    if (actor_state->tileY == 0) {
        advance_actor_pending_action(controller, context, entity, actor_state);
        if (((ActorSpriteView *)entity)->animationTable != D_80150860) {
            u8 *early_table = D_80150858;
            ((ActorSpriteView *)entity)->animationTable = early_table;
            select_sprite_entry(entity,
                early_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor_state->flags1C) & 0x200) {
        if (((ActorSpriteView *)entity)->animationTable == D_80150860) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor_state->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(controller, context, entity, D_80150858)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor_state->flags1C) & 0x100) {
            begin_pushed_actor_move(controller, context, entity, actor_state);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 != 0xE) {
            u8 control_state = 0xE;

            anim_table = D_80150820;
            if (((ActorSpriteView *)entity)->animationTable != anim_table) {
                ((ActorSpriteView *)entity)->animationTable = anim_table;
                select_sprite_entry(entity,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = control_state;
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (actor_state->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, entity, D_80150830)) {
                return;
            }
        }

        if (((u32)actor_state->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, entity, actor_state);
            func_8014FF28(controller, context, entity, actor_state);
            return;
        }

        if ((s16)can_entity_gain_level(actor_state) != 0) {
            process_selected_actor_record(controller, context, entity, actor_state);
        }
    }

    room_id = find_active_rect_containing_point(((ActorSpriteView *)entity)->tile.bytes.x, ((ActorSpriteView *)entity)->tile.bytes.y);
    ((ActorSpriteView *)entity)->room = room_id;

    if (actor_state->unk_6D > 0) {
        if (((u32)actor_state->flags1C) & 0x20) {
            update_actor_status_and_food(actor_state);
            return;
        }
        if (((ActorSpriteView *)entity)->tile.packed == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            func_8014D624(controller, context, entity, actor_state);
            return;
        }
        if (!(actor_state->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(actor_state,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8014E0AC(controller, context, entity, 0) == 0) {
                return;
            }
            actor_state->unk_46 |= 0x4000;
            if (!(actor_state->unk_46 & 0x8000)) {
                func_8014D624(controller, context, entity, actor_state);
                return;
            }
        }

        switch (actor_state->unk_46 & 0x3FFF) {
        case 8:
        case 9:
            if ((s16)func_8014DDD0(controller, context, entity, actor_state) == 0) {
                func_8014DF94(controller, context, entity, actor_state);
                return;
            }
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player_controller;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    ((ActorSpriteView *)entity)->tile.bytes.x, ((ActorSpriteView *)entity)->tile.bytes.y,
                    D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                    &direction_flags);
                player_controller = D_800814A8;
                actor_state->facing = direction;
                if (player_controller->unk_9A != 0x11) {
                    update_actor_status_and_food(actor_state);
                    return;
                }
                begin_actor_spell_action(controller, context, entity, D_80150848, &D_8014CE84);
                return;
            }
        case 12:
            update_actor_status_and_food(actor_state);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(controller, context, entity, D_80150848, &D_8014CE84);
            return;
        default:
            break;
        }

        func_8014D624(controller, context, entity, actor_state);
        return;
    } else if (!(((u32)actor_state->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor_state->flags1C) & 0x430)) {

                if ((s16)compare_monster_neighbor_values(((ActorSpriteView *)entity)->tile.bytes.x,
                    ((ActorSpriteView *)entity)->tile.bytes.y, D_80082E80.tile_position.parts.tile_x,
                    D_80082E80.tile_position.parts.tile_y) != 0) {
                    actor_state->facing = get_rounded_facing_and_rounding_flag(
                        ((ActorSpriteView *)entity)->tile.bytes.x, ((ActorSpriteView *)entity)->tile.bytes.y,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &direction_flags);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((ActorSpriteView *)entity)->flags & 0x40) {
        return;
    }
    anim_table = D_80150820;
    if (((ActorSpriteView *)entity)->animationTable == anim_table) {
        return;
    }
    ((ActorSpriteView *)entity)->animationTable = anim_table;
    select_sprite_entry(entity,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
        0);
}
