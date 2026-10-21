#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void clear_slots_of_type(void *, s32);
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
extern void func_8015F510(void *, void *, void *, void *);
extern void func_8015F768(u8 *move_work, void *entry_context, u8 *position, u8 *actor);
extern s32 func_8015FF24(void *, void *, void *, void *);
extern void func_80160110(void *, void *, void *, void *);
extern s32 func_80160228(void *, void *, void *, s32);
extern void func_80161900(void *, void *, void *, void *);
extern void func_80161AD4(void *, void *, void *, void *);

extern s32 D_8015EF68;
extern u8 D_80161FB8[];
extern u8 D_80161FC0[];
extern u8 D_80161FF0[];
extern u8 D_80161FF8[];
extern u8 D_80162000[];

typedef struct CreatureState {
    u8 pad_00[0x1C];
    u32 flags;
    u8 pad_20[0x5];
    u8 tileY;
    u8 pad_26[0x4];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 action;
    u8 pad_48[0x1C];
    s16 reaction;
    u8 pad_66[0x7];
    s8 actionsLeft;
} CreatureState;

typedef struct ActorSprite {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    u8 room;
    u8 pad_27[0x5];
    void * directionFrames;
} ActorSprite;

/* Updates a dungeon actor's behavior, facing, and animation from its current state. */
void update_dungeon_actor_behavior_and_animation(void *actor, void *context, ActorSprite *sprite, CreatureState *entity)
{
    u8 *anim_table;
    s32 tile_id;
    s32 direction_aux;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_8015F510(actor, context, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        u8 *inactive_anims;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->directionFrames != D_80162000) {
            inactive_anims = D_80161FF8;
            sprite->directionFrames = inactive_anims;
            select_sprite_entry(sprite,
                inactive_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100)
                    >> 9) & 7],
                0);
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AE = 0;
        clear_slots_of_type(entity, 0x1A);
        return;
    }

    if (entity->flags & 0x200) {
        if (sprite->directionFrames == D_80162000) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            entity->flags &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80161FF8)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80161FB8;
            if (sprite->directionFrames != anim_table) {
                sprite->directionFrames = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100)
                        >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = next_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (entity->reaction != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80161FC0)) {
                    return;
            }
        }

        if (entity->flags & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_80161900(actor, context, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    tile_id = find_active_rect_containing_point(sprite->position.tile.x,
        sprite->position.tile.y);
    sprite->room = tile_id;

    if (entity->actionsLeft > 0) {
        if (entity->flags & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (sprite->position.packed == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_8015F768(actor, context, sprite, entity);
            return;
        }
        if (!(entity->action & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(entity,
                        (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80160228(actor, context, sprite, 0) == 0) {
                    return;
            }
            entity->action |= 0x4000;
            if (!(entity->action & 0x8000)) {
                func_8015F768(actor, context, sprite, entity);
                return;
            }
        }

        switch (entity->action & 0x3FFF) {
        case 8:
            if ((s16)func_8015FF24(actor, context, sprite, entity) == 0) {
                func_80160110(actor, context, sprite, entity);
                    return;
            }
            return;
        case 9:
            func_80161AD4(actor, context, sprite, entity);
            return;
        case 5:
        case 6:
        case 7:
            {
                ActorRecord *player;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    sprite->position.tile.x, sprite->position.tile.y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
                player = primary_actor_record;
                entity->facing = direction;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80161FF0, &D_8015EF68);
                    return;
                }
            }
        /* fall through */
        case 12:
            update_actor_status_and_food(entity);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor, context, sprite, D_80161FF0, &D_8015EF68);
            return;
        default:
            func_8015F768(actor, context, sprite, entity);
            return;
        }
    } else if (!(entity->flags & 0x2000)) {
        s32 record_index = (s8)tile_id;

        if ((record_index < 0) || !(dungeon_rooms[record_index].flags & 2)) {
            if (!(entity->flags & 0x430)) {

                if ((s16)compare_monster_neighbor_values(sprite->position.tile.x,
                        sprite->position.tile.y, reference_tile_object.tile_position.parts.tile_x,
                        reference_tile_object.tile_position.parts.tile_y) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->position.tile.x,
                            sprite->position.tile.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    anim_table = D_80161FB8;
    if (sprite->directionFrames == anim_table) {
        return;
    }
    sprite->directionFrames = anim_table;
    select_sprite_entry(sprite,
        ((((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + anim_table)[0],
        0);
}
