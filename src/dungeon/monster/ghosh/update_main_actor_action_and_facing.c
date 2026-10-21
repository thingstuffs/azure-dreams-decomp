#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;

typedef struct S_8016B778_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    union { u8 * p; void * p2; } unk_2C;   /* accessed as both */
} S_8016B778_2;   /* arg2 in update_main_actor_action_and_facing */

typedef struct S_8016B778_3 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_8016B778_3;   /* *D_800814A8 in update_main_actor_action_and_facing */

typedef struct S_8016B778_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8016B778_4;   /* global_814A8 in update_main_actor_action_and_facing */

typedef struct S_8016B778_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8016B778_5;   /* entry in update_main_actor_action_and_facing */

extern u8 D_801746A4[];
extern u8 D_80174684[];
extern u8 D_801746C4[];
extern u8 D_8017467C[];
extern u8 D_8016B778[];
s8 find_active_rect_containing_point();
s32 compare_monster_neighbor_values(s32, s32, s32, s32);
s32 can_entity_gain_level();
struct ActorRecord; void update_actor_status_and_food(struct ActorRecord *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
s32 begin_ready_actor_directional_action();
struct Rec_func_800A9E70_arg0; struct Rec_func_800AA258_arg2; void begin_actor_move_to_target_facing(struct Rec_func_800A9E70_arg0 *, void *, struct Rec_func_800AA258_arg2 *, struct ActorRecord *);
s32 reset_actor_action_state(void *, s32, void *, u8 *);
void begin_actor_spell_action(void *, s32, void *, u8 *, s32);
void advance_entity_along_path(void *, void *, void *, void *);
void advance_actor_path();
s32 func_8016C720();
struct Rec_func_800A9E70_arg0; void clear_actor_flag_and_advance_action(struct Rec_func_800A9E70_arg0 *, s32, void *, struct ActorRecord *);
struct Rec_func_800A9E70_arg0; s32 dispatch_actor_action_phase(struct Rec_func_800A9E70_arg0 *, s32, s32, s32);
extern void func_8016DAA4(CallbackOwner *owner, s32 unused, s32 first, s32 second);
s32 execute_actor_script_command(u8 *, s32, u8 *);
extern M2C_UNK D_8017469C;
extern M2C_UNK D_801746BC;

/* Update the actor's dungeon action, animation, and facing direction. */
void update_main_actor_action_and_facing(Rec_func_800A9E70_arg0 *actor, s32 context, S_8016B778_2 *map_actor, ActorRecord *entity) {
    u16 target_distance;
    s32 entity_flags;
    s32 state_flags;
    s32 override_flag;
    s16 target_angle;
    s32 action_id;
    s8 tile_index;
    u16 action_flags;
    u8 *action_data;
    register void *current_anim;
    u8 *idle_anim;
    void *action_actor;
    s32 flag_mask_hi;
    u8 *tile_table;
    u8 *tile_entry;
    u8 *active_actor;
    if (g_dungeon_status.flags & 0x1000) {
        actor->unk_9A.as_u8 = 0xEU;
        advance_entity_along_path(actor, (void *)(context), map_actor, entity);
        return;
    }
    if (entity->flags1C & 0x200) {
        if (map_actor->unk_2C.p == D_801746A4) {
            flag_mask_hi = (s32)0xFFFB0000;
            actor->unk_9A.as_u8 = 0xDU;
            actor->unk_9B.as_s8 = 1;
            actor->unk_8C = 0;
            entity->flags1C &= flag_mask_hi | 0xFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, map_actor, (u8 *)(&D_8017469C)) != 0) {
            return;
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        state_flags = entity->flags1C;
        override_flag = state_flags & 0x100;
        action_actor = actor;
        if (override_flag) {
            begin_pushed_actor_move(action_actor, context, map_actor, entity);
            return;
        }
        if (actor->unk_9A.as_u8 != 0xE) {
            if (actor->unk_B3 == 0) {
                current_anim = map_actor->unk_2C.p2;
                idle_anim = (u8 *)&D_8017467C;
            } else {
                current_anim = map_actor->unk_2C.p2;
                idle_anim = D_80174684;
            }
            if (current_anim != idle_anim) {
                map_actor->unk_2C.p = idle_anim;
                action_data = (u8 *)(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7);
                action_data += (u32)idle_anim;
                select_sprite_entry(map_actor, *action_data, 0);
            }
            actor->unk_9A.as_u8 = 0xEU;
        }
        actor->unk_98 = (u16) (actor->unk_98 & 0xFFF3);
        if (actor->unk_B4 == 0) {
            if (!((u16)*((s16 *)&system_update_flags) & 8)) {
                if (entity->unk_64 != 0) {
                    if (begin_ready_actor_directional_action(actor, context, map_actor, D_801746C4) != 0) {
                        return;
                    }
                }
            } else {
                if (entity->unk_64 != 0) {
                    if (((s32)g_dungeon_status.pending_display_owner) == ((u8 *)entity - 0x20)) {
                        *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
                    }
                }
            }
        } else {
            if (entity->unk_64 != 0) {
                if (((s32)g_dungeon_status.pending_display_owner) == ((u8 *)entity - 0x20)) {
                    *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
                }
            }
        }
        if (entity->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, (void *)(context), (struct Rec_func_800AA258_arg2 *)(map_actor), entity);
            func_8016DAA4(actor, context, map_actor, entity);
            map_actor->unk_2C.p = D_8017467C;
            select_sprite_entry(map_actor, D_8017467C[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
            actor->unk_90.at00_s32.v = 0;
            return;
        }
        if ((can_entity_gain_level(entity) << 0x10) != 0) {
            entity->experience = 0;
            g_dungeon_status.active_actor = 0;
        }
    }
    tile_index = find_active_rect_containing_point(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v);
    map_actor->unk_26 = tile_index;
    if (entity->pending_turn_updates > 0) {
        if (entity->flags1C & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (map_actor->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            advance_actor_path(actor, context, map_actor, entity);
            return;
        }
        if (!(entity->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity, ((S_8016B778_3 *)(((int)primary_actor_record)))->unk_58 + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((u16) *((s16 *)&system_update_flags) & 8) {
                execute_actor_script_command((u8 *)(actor), context, (u8 *)(map_actor));
                entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
                update_actor_status_and_food(entity);
                entity->action_flags &= 0x7FFF;
                return;
            }
            if ((dispatch_actor_action_phase(actor, context, (s32)(map_actor), 0) << 0x10) == 0) {
                return;
            }
            action_flags = entity->action_flags | 0x4000;
            entity->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                advance_actor_path(actor, context, map_actor, entity);
                return;
            }
        }
        action_id = entity->action_flags & 0x3FFF;
        switch (action_id) {
        case 8:
        case 9:
            if ((func_8016C720(actor, context, map_actor, entity) << 0x10) != 0) {
                return;
            }
            clear_actor_flag_and_advance_action(actor, context, map_actor, entity);
            return;
        case 12:
            update_actor_status_and_food(entity);
            return;
        case 5:
        case 6:
        case 7:
            target_angle = get_rounded_facing_and_rounding_flag(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y, &target_distance);
            active_actor = (u8 *)*((int *)(&primary_actor_record));
            entity->facing = target_angle;
            if (((S_8016B778_4 *)active_actor)->unk_9A != 0x11) {
                update_actor_status_and_food(entity);
                return;
            }
            /* Fall through to install the action handler. */
        case 1:
        case 2:
        case 3:
            action_data = D_8016B778;
            begin_actor_spell_action(actor, context, map_actor, (u8 *)(&D_801746BC), (s32)(action_data));
            return;
        case 11:
        default:
            advance_actor_path(actor, context, map_actor, entity);
            return;
        }
    }
    entity_flags = entity->flags1C;
    if (entity_flags & 0x2000) {
        return;
    }
    if (*(u16 *)0x80013714 & 8) {
        return;
    }
    if (tile_index >= 0) {
        tile_table = dungeon_rooms;
        tile_entry = (tile_index * 0x14) + tile_table;
        if (((S_8016B778_5 *)tile_entry)->unk_0C & 2) {
            return;
        }
    }
    if (entity_flags & 0x430) {
        return;
    }
    if ((compare_monster_neighbor_values(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10)
        == 0) {
        return;
    }
    entity->facing = get_rounded_facing_and_rounding_flag(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, reference_tile_object.tile_position.parts.tile_x,
        reference_tile_object.tile_position.parts.tile_y, &target_distance);
    return;
}
