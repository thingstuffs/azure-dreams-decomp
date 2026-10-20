#include "common.h"
#include "m2c_compat.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"



typedef struct S_8016A36C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    union { s32 * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_8016A36C_3;   /* arg2 in update_multi_form_actor_control */



#include "engine/graphics/select_sprite_entry_api.h"
void func_800478B8();
s32 func_80069EF8();
struct EntityRec; s32 check_entity_relation(struct EntityRec *, struct EntityRec *);
s8 find_active_rect_containing_point();
s32 compare_monster_neighbor_values(s32, s32, s32, s32);
s32 get_rounded_facing_and_rounding_flag();
s32 can_entity_gain_level();
struct EntityRec; void update_actor_status_and_food(struct EntityRec *);
void begin_pushed_actor_move();
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action(void *, s32, void *, void *);
struct EntityRec; struct Rec_func_800A9E70_arg0; struct Rec_func_800AA258_arg2; void begin_actor_move_to_target_facing(struct Rec_func_800A9E70_arg0 *, void *, struct Rec_func_800AA258_arg2 *, struct EntityRec *);
s32 reset_actor_action_state(void *, s32, void *, u8 *);
void begin_actor_spell_action(void *, s32, void *, u8 *, s32);
void advance_multi_form_turn_path(void *, void *, void *, void *);
void advance_actor_movement_step(u8 *, void *, u8 *, u8 *);
struct EntityRec; struct Rec_D_80082E80; struct Rec_func_800A9E70_arg0; s32 try_actor_attack(struct Rec_func_800A9E70_arg0 *, s32, struct Rec_D_80082E80 *, struct EntityRec *);
void start_actor_attack(void *, s32, s32, void *);
struct Rec_func_800A9E70_arg0; s32 resolve_actor_movement_action(struct Rec_func_800A9E70_arg0 *, s32, s32, s32);
void update_multi_form_actor_movement();
struct EntityRec; struct Rec_func_800A9E70_arg0; void complete_actor_facing_action(struct Rec_func_800A9E70_arg0 *, s32, s32, struct EntityRec *);
struct EntityRec; struct Rec_func_800A9E70_arg0; void start_actor_directional_action(struct Rec_func_800A9E70_arg0 *, void *, void *, struct EntityRec *);
s32 advance_actor_effect_sequence_2();
extern u8 D_801739A0;
extern u8 D_801739A8;
extern u8 D_801739B0;
extern u8 D_801739B8;
extern M2C_UNK D_801739E0;
extern M2C_UNK D_801739E8;
extern M2C_UNK D_801739F0;
extern M2C_UNK D_801739F8;
extern M2C_UNK D_80173A00;
extern M2C_UNK D_80173A08;
extern M2C_UNK D_80173A10;
extern M2C_UNK D_80173A18;
extern u8 D_80173A50;
extern u8 D_80173A58;
extern M2C_UNK D_80173AC0;
extern M2C_UNK D_80173AC8;

/* Updates dungeon actor actions, facing, and idle animations. */
void update_multi_form_actor_control(void *actor, void *context, void *sprite, EntityRec *entity) {
    void *pose_actor;
    s32 distance;
    u8 *idle_table;
    u8 *pose2_table;
    u8 *pose3_table;
    unsigned long table_index;
    u8 *next_table;
    u8 *current_table;
    s32 entity_flags;
    s32 action_id;
    s8 room_id;
    u16 action_flags;
    u16 pose2_idle_ticks;
    u16 pose2_anim_ticks;
    u16 pose3_idle_ticks;
    u16 pose3_anim_ticks;
    s32 inactive_pose;
    s32 flagged_pose;
    s32 anim_state;
    s32 active_pose;
    s32 action_pose;
    s32 idle_pose;
    u32 clear_mask;
    s32 state_changed;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        advance_multi_form_turn_path(actor, context, sprite, entity);
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 != 1) {
            return;
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = (u8) (((Rec_func_800A9E70_arg0 *)actor)->unk_AD + 1);
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) + 1);
        return;
    }
    if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 == 1) {
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_AD != 0) {
            g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - ((Rec_func_800A9E70_arg0 *)actor)->unk_AD);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = 0U;
        }
    }
    if (entity->tileY == 0) {
        advance_actor_pending_action(actor, (s32)(context), sprite, entity);
        inactive_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
        switch (inactive_pose) {
        case 0xD:
            if (((S_8016A36C_3 *)sprite)->unk_2C.p == (s32 *)((u8 *)&D_80173AC0 + 8)) {
                return;
            }
            (((S_8016A36C_3 *)sprite)->unk_2C.p) = (s32 *)((u8 *)&D_80173A58 + 0x68);
            table_index = ((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)(s32 *)((u8 *)&D_80173A58 + 0x68);
            select_sprite_entry(sprite, *(u8 *)table_index, 0);
            return;
        case 0xE:
            if (((S_8016A36C_3 *)sprite)->unk_2C.p == (s32 *)((u8 *)&D_80173A58 + 0x70)) {
                return;
            }
            (((S_8016A36C_3 *)sprite)->unk_2C.p) = &D_80173AC0;
            table_index = ((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)&D_80173AC0;
            select_sprite_entry(sprite, *(u8 *)table_index, 0);
            return;
        case 0xF:
            if (((S_8016A36C_3 *)sprite)->unk_2C.p == &D_80173AC8) {
                return;
            }
            (((S_8016A36C_3 *)sprite)->unk_2C.p) = (s32 *)((u8 *)&D_80173A00 + 0xC0);
            table_index = ((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)(s32 *)((u8 *)&D_80173A00 + 0xC0);
            select_sprite_entry(sprite, *(u8 *)table_index, 0);
            return;
        }
        return;
    }
    if (entity->flags1C & 0x200) {
        flagged_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
        switch (flagged_pose) {
        case 0xD:
            if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173AC8) {
                break;
            }
            clear_mask = 0xFFFB0000U;
            state_changed = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = flagged_pose;
            goto block_32;
        case 0xE:
            if (((S_8016A36C_3 *)sprite)->unk_2C.p == &D_80173AC8) {
                goto block_31;
            }
            break;
        case 0xF:
            if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173AC8) {
                break;
            }
block_31:
            clear_mask = 0xFFFB0000U;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
            state_changed = 1;
block_32:
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = (s8)state_changed;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            entity->flags1C = (s32) (entity->flags1C & (clear_mask | 0xFFFFU));
            return;
        default:
            goto block_37;
        }
        if (reset_actor_action_state(actor, (s32)(context), sprite, (u8 *)(&D_80173AC0)) != 0) {
            return;
        }
    }
block_37:
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }
        {
            s16 idle_state = 0xE;
            anim_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8;
            if (anim_state != idle_state) {
                anim_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
                switch (anim_state) {
                case 0:
                    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739A0) {
                        (((S_8016A36C_3 *)sprite)->unk_2C.p2) = &D_801739A0;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &D_801739A0), 0);
                    }
                    break;
                case 1:
                    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739A8) {
                        (((S_8016A36C_3 *)sprite)->unk_2C.p2) = &D_801739A8;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &D_801739A8), 0);
                    }
                    break;
                case 2:
                    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739B0) {
                        (((S_8016A36C_3 *)sprite)->unk_2C.p2) = &D_801739B0;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &D_801739B0), 0);
                    }
                    break;
                case 3:
                    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739B8) {
                        (((S_8016A36C_3 *)sprite)->unk_2C.p2) = &D_801739B8;
                        select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                            + &D_801739B8), 0);
                    }
                    break;
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x1F) + 0xF);
            }
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
        if (entity->unk_64 != 0) {
            active_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
            switch (active_pose) {
            case 0:
                if (begin_ready_actor_directional_action(actor, context, sprite, &D_80173A00) != 0) {
                    return;
                }
                break;
            case 1:
                if (begin_ready_actor_directional_action(actor, context, sprite, &D_80173A08) != 0) {
                    return;
                }
                break;
            case 2:
                if (begin_ready_actor_directional_action(actor, context, sprite, &D_80173A10) != 0) {
                    return;
                }
                break;
            case 3:
                if (begin_ready_actor_directional_action(actor, context, sprite, &D_80173A18) != 0) {
                    return;
                }
                break;
            }
        }
        if (entity->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            update_multi_form_actor_movement(actor, context, sprite, entity);
            return;
        }
        if ((can_entity_gain_level(entity) << 0x10) != 0) {
            if (((s32)g_dungeon_status.unk_0C) != entity) {
                return;
            }
            if (((s32)g_dungeon_status.unk_10) != 0) {
                return;
            }
            if ((s16) ((u16)g_dungeon_status.unk_0A) >= 2) {
                return;
            }
            if (g_dungeon_status.flags & 8) {
                return;
            }
            entity->unk_18 = 0;
            g_dungeon_status.unk_0C = 0;
        }
    }
    room_id = find_active_rect_containing_point(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v);
    ((S_8016A36C_3 *)sprite)->unk_26 = room_id;
    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (((S_8016A36C_3 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            advance_actor_movement_step(actor, context, sprite, (u8 *)(entity));
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity, (struct EntityRec *)(((s32)D_800814A8->unk_58) + 0x20)) << 0x10) != 0) {
                    return;
                }
            }
            if (D_80013714 & 8) {
                advance_actor_effect_sequence_2(actor, context, sprite);
                entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
                update_actor_status_and_food(entity);
                entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
                return;
            }
            if ((resolve_actor_movement_action(actor, (s32)(context), (s32)(sprite), 0) << 0x10) == 0) {
                return;
            }
            action_flags = entity->unk_46 | 0x4000;
            entity->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                advance_actor_movement_step(actor, context, sprite, (u8 *)(entity));
                return;
            }
        }
        action_id = entity->unk_46 & 0x3FFF;
        switch (action_id) {
        case 8:
            if ((try_actor_attack(actor, (s32)(context), sprite, entity) << 0x10) != 0) {
                return;
            }
            start_actor_attack(actor, (s32)(context), (s32)(sprite), entity);
            return;
        case 9:
            complete_actor_facing_action(actor, (s32)(context), (s32)(sprite), entity);
            return;
        case 10:
            start_actor_directional_action(actor, context, sprite, entity);
            return;
        case 12:
            update_actor_status_and_food(entity);
            return;
        case 5:
        case 6:
        case 7:
        {
            s32 angle = get_rounded_facing_and_rounding_flag(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &distance);
            EntityRec *owner = D_800814A8;
            entity->facing = (s16)angle;
            if (owner->unk_9A != 0x11) {
                update_actor_status_and_food(entity);
                return;
            }
        }
        case 1:
        case 2:
        case 3:
            action_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
            switch (action_pose) {
            case 0:
                begin_actor_spell_action(actor, (s32)(context), sprite, (u8 *)(&D_801739E0), (s32)(&update_multi_form_actor_control));
                return;
            case 1:
                begin_actor_spell_action(actor, (s32)(context), sprite, (u8 *)(&D_801739E8), (s32)(&update_multi_form_actor_control));
                return;
            case 2:
                begin_actor_spell_action(actor, (s32)(context), sprite, (u8 *)(&D_801739F0), (s32)(&update_multi_form_actor_control));
                return;
            case 3:
                begin_actor_spell_action(actor, (s32)(context), sprite, (u8 *)(&D_801739F8), (s32)(&update_multi_form_actor_control));
                return;
            }
            return;
        default:
            advance_actor_movement_step(actor, context, sprite, (u8 *)(entity));
            return;
        }
    }
    pose_actor = actor;
    entity_flags = entity->flags1C;
    if (!(entity_flags & 0x2000)) {
        if (!(D_80013714 & 8)) {
            if (room_id < 0 || !(D_800E2970[room_id].flags & 2)) {
                if (!(entity_flags & 0x430)) {
                    if ((compare_monster_neighbor_values(((S_8016A36C_3 *)sprite)->unk_24.at00.v,
                        ((S_8016A36C_3 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY) << 0x10) != 0) {
                        entity->facing = get_rounded_facing_and_rounding_flag(((S_8016A36C_3 *)sprite)->unk_24.at00.v,
                            ((S_8016A36C_3 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &distance);
                    }
                }
            }
        }
    }
    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_8016A36C_3 *)sprite)->unk_14 & 0x40) {
        return;
    }
    if (entity->flags1C & 0x20) {
        return;
    }
    if ((*(u16 *)0x80013714) & 8) {
        return;
    }
    idle_pose = ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_AC;
    switch (idle_pose) {
    case 0:
        next_table = &D_801739A0;
        current_table = ((S_8016A36C_3 *)sprite)->unk_2C.p2;
        if (current_table == next_table) {
            return;
        }
        (((S_8016A36C_3 *)sprite)->unk_2C.p) = next_table;
        table_index = ((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)next_table;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        return;
    case 1:
        current_table = ((S_8016A36C_3 *)sprite)->unk_2C.p2;
        next_table = &D_801739A8;
        if (current_table == next_table) {
            return;
        }
        (((S_8016A36C_3 *)sprite)->unk_2C.p) = next_table;
        table_index = ((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)next_table;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        return;
    case 2:
        pose2_table = ((S_8016A36C_3 *)sprite)->unk_2C.p;
        if (pose2_table != &D_801739B0 && pose2_table != &D_80173A50) {
            (((S_8016A36C_3 *)sprite)->unk_2C.p) = &D_801739B0;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                + &D_801739B0), 0);
            ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = 0U;
            ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
        }
        if (pose2_table == &D_801739B0 || ((S_8016A36C_3 *)sprite)->unk_2C.p == &D_801739B0) {
            pose2_idle_ticks = ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16;
            ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = (u16) (pose2_idle_ticks + 1);
            if ((s16) pose2_idle_ticks >= ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_A0.at00_s16.v) {
                (((S_8016A36C_3 *)sprite)->unk_2C.p) = &D_80173A50;
                select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                    + &D_80173A50), 0);
                func_800478B8(sprite);
                ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = 0U;
            }
        }
        if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173A50) {
            return;
        }
        pose2_anim_ticks = ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16;
        ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = (u16) (pose2_anim_ticks + 1);
        if ((s16) pose2_anim_ticks < 0x12) {
            return;
        }
        (((S_8016A36C_3 *)sprite)->unk_2C.p) = &D_801739B0;
        table_index = ((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)&D_801739B0;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = 0U;
        ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
        return;
    case 3:
        pose3_table = ((S_8016A36C_3 *)sprite)->unk_2C.p;
        idle_table = &D_801739B8;
        if (pose3_table != idle_table && pose3_table != &D_80173A58) {
            (((S_8016A36C_3 *)sprite)->unk_2C.p) = idle_table;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                + idle_table), 0);
            ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = 0U;
            ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
        }
        if (pose3_table == idle_table || ((S_8016A36C_3 *)sprite)->unk_2C.p == idle_table) {
            pose3_idle_ticks = ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16;
            ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = (u16) (pose3_idle_ticks + 1);
            if ((s16) pose3_idle_ticks >= ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_A0.at00_s16.v) {
                (((S_8016A36C_3 *)sprite)->unk_2C.p) = &D_80173A58;
                select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7)
                    + &D_80173A58), 0);
                func_800478B8(sprite);
                ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = 0U;
            }
        }
        if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173A58) {
            return;
        }
        pose3_anim_ticks = ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16;
        ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = (u16) (pose3_anim_ticks + 1);
        if ((s16) pose3_anim_ticks < 0x12) {
            return;
        }
        (((S_8016A36C_3 *)sprite)->unk_2C.p) = &D_801739B8;
        table_index = ((s32) (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
        table_index += (unsigned long)&D_801739B8;
        select_sprite_entry(sprite, *(u8 *)table_index, 0);
        ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_9E.as_u16 = 0U;
        ((Rec_func_800A9E70_arg0 *)pose_actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
        return;
    }
}
