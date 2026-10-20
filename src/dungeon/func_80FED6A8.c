#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *, void *, void *, void *);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *, void *, void *, void *, void *);
extern void func_8015F438(void *, void *, void *, void *);
extern void func_8015F67C(void *, void *, void *, void *);
extern s32 func_8015FE28(void *, void *, void *, void *);
extern void func_8016008C(void *, void *, void *, void *);
extern s32 func_80160230(void *, void *, void *, s32);
extern void func_80161A84(void *, void *, void *, void *);

extern u8 D_8015EEA8;
extern u8 D_80162038[];
extern u8 D_80162040[];
extern u8 D_80162070[];
extern u8 D_80162080[];
extern u8 D_80162088[];

typedef struct ActionState {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[0x8];
    u16 flags;
    u8 action;
    u8 phase;
} ActionState;

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

/* Updates the entity action, facing direction, and animation from dungeon state. */
void update_entity_action(ActionState *actor, void *context, ActorSprite *sprite, EntityRec *entity)
{
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 dungeon_flags = g_dungeon_status.flags;

    if (dungeon_flags & 0x1000) {
        actor->action = 0xE;
        func_8015F438(actor, context, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->directionFrames != D_80162088) {
            sprite->directionFrames = D_80162080;
            select_sprite_entry(sprite,
                D_80162080[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (sprite->directionFrames == D_80162088) {
            actor->action = 0xD;
            actor->phase = 1;
            actor->handler = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80162080)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        if (actor->action != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80162038;
            if (sprite->directionFrames != anim_table) {
                sprite->directionFrames = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            actor->action = next_state;
        }

        actor->flags &= 0xFFF3;
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80162040)) {
                    return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_80161A84(actor, context, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    tile_record = find_active_rect_containing_point(sprite->position.tile.x, sprite->position.tile.y);
    sprite->room = tile_record;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (sprite->position.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_8015F67C(actor, context, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80160230(actor, context, sprite, 0) == 0) {
                    return;
            }
            entity->unk_46 |= 0x4000;
            if (!(entity->unk_46 & 0x8000)) {
                func_8015F67C(actor, context, sprite, entity);
                return;
            }
        }

        switch (entity->unk_46 & 0x3FFF) {
        case 9:
            actor->flags |= 0x8000;
        /* fall through */
        case 8:
            if (((u32)entity->flags1C) & 0x2000) {
                if ((entity->unk_46 & 0x3FFF) == 8) {
                    actor->flags &= 0x7FFF;
                }
            }
            if ((s16)func_8015FE28(actor, context, sprite, entity) == 0) {
                func_8016008C(actor, context, sprite, entity);
                    return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                EntityRec *global_actor;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    sprite->position.tile.x, sprite->position.tile.y,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_aux);
                global_actor = D_800814A8;
                entity->facing = direction;
                if (global_actor->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80162070, &D_8015EEA8);
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
            begin_actor_spell_action(actor, context, sprite, D_80162070, &D_8015EEA8);
            return;
        default:
            func_8015F67C(actor, context, sprite, entity);
            return;
        }
    } else if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((s16)compare_monster_neighbor_values(sprite->position.tile.x,
                        sprite->position.tile.y, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->position.tile.x, sprite->position.tile.y,
                        D_80082E80.tileX, D_80082E80.tileY,
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
    anim_table = D_80162038;
    if (sprite->directionFrames == anim_table) {
        return;
    }
    sprite->directionFrames = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
