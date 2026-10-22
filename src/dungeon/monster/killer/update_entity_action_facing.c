#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *, void *, void *, void *);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *, void *, void *, void *, void *);
extern void func_80171438(void *, void *, void *, void *);
extern void func_8017167C(void *, void *, void *, void *);
extern s32 validate_direction_and_initialize_action(void *, void *, void *, void *);
extern void update_eligible_actor_action_alt(void *, void *, void *, void *);
extern s32 func_80172230(void *, void *, void *, s32);
extern void func_80173A84(void *, void *, void *, void *);

extern u8 D_80170EA8;
extern u8 D_80174038[];
extern u8 D_80174040[];
extern u8 D_80174070[];
extern u8 D_80174080[];
extern u8 D_80174088[];


typedef struct S_80170EA8_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    union { u16 n; u16 v; } unk_98;   /* accessed as both */
    u8 unk_9A;
    u8 unk_9B;
} S_80170EA8_0;   /* arg0 in update_entity_action_facing */


typedef struct S_80170EA8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170EA8_2;   /* arg2 in update_entity_action_facing */


/* Updates the entity action, facing direction, and animation from dungeon state. */
/* Selects Killer's movement, two attack modes, spells, and turn processing, then restores its directional
 * idle frames. */
void update_entity_action_facing(void *actor, void *context, void *sprite, ActorRecord *entity)
{
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 dungeon_flags = g_dungeon_status.flags;

    if (dungeon_flags & 0x1000) {
        ((S_80170EA8_0 *)actor)->unk_9A = 0xE;
        func_80171438(actor, context, sprite, entity);
        return;
    }

    if (entity->mp == 0) {
        advance_actor_pending_action(actor, context, sprite, entity);
        if (((S_80170EA8_2 *)sprite)->unk_2C != D_80174088) {
            (*(void * *)((u8 *)sprite + (0x2C))) = D_80174080;
            select_sprite_entry(sprite,
                D_80174080[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_80170EA8_2 *)sprite)->unk_2C == D_80174088) {
            ((S_80170EA8_0 *)actor)->unk_9A = 0xD;
            ((S_80170EA8_0 *)actor)->unk_9B = 1;
            ((S_80170EA8_0 *)actor)->unk_8C = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80174080)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        if (((S_80170EA8_0 *)actor)->unk_9A != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80174038;
            if (((S_80170EA8_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170EA8_0 *)actor)->unk_9A = next_state;
        }

        ((S_80170EA8_0 *)actor)->unk_98.n &= 0xFFF3;
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174040)) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_80173A84(actor, context, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    tile_record = find_active_rect_containing_point(((S_80170EA8_2 *)sprite)->unk_24.at00.v, ((S_80170EA8_2 *)sprite)->unk_24.at01.v);
    ((S_80170EA8_2 *)sprite)->unk_26 = tile_record;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (((S_80170EA8_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_8017167C(actor, context, sprite, entity);
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(entity,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172230(actor, context, sprite, 0) == 0) {
                return;
            }
            entity->action_flags |= 0x4000;
            if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
                func_8017167C(actor, context, sprite, entity);
            return;
            }
        }

        switch (entity->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 9:
            ((S_80170EA8_0 *)actor)->unk_98.v |= 0x8000;
            /* fallthrough */
        case 8:
            if (((u32)entity->flags1C) & 0x2000) {
                if ((entity->action_flags & ACTOR_ACTION_CODE_MASK) == 8) {
                    ((S_80170EA8_0 *)actor)->unk_98.v &= 0x7FFF;
                }
            }
            if ((s16)validate_direction_and_initialize_action(actor, context, sprite, entity) == 0) {
                update_eligible_actor_action_alt(actor, context, sprite, entity);
                return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                ActorRecord *global_actor;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    ((S_80170EA8_2 *)sprite)->unk_24.at00.v, ((S_80170EA8_2 *)sprite)->unk_24.at01.v,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
                global_actor = primary_actor_record;
                entity->facing = direction;
                if (global_actor->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80174070, &D_80170EA8);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(entity);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor, context, sprite, D_80174070, &D_80170EA8);
            return;
        default:
            func_8017167C(actor, context, sprite, entity);
            return;
        }
    } else if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(dungeon_rooms[record_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((s16)test_neighbor_position_relation(((S_80170EA8_2 *)sprite)->unk_24.at00.v,
                        ((S_80170EA8_2 *)sprite)->unk_24.at01.v, reference_tile_object.tile_position.parts.tile_x,
                        reference_tile_object.tile_position.parts.tile_y) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        ((S_80170EA8_2 *)sprite)->unk_24.at00.v, ((S_80170EA8_2 *)sprite)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_80170EA8_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174038;
    if (((S_80170EA8_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
    select_sprite_entry(sprite,
        *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
