#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8015F0EC_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_8015F0EC_0;   /* arg0 in update_actor_animation_and_dispatch_current */


typedef struct S_8015F0EC_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
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
} S_8015F0EC_2;   /* arg2 in update_actor_animation_and_dispatch_current */


extern s32 get_entity_effect_value(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8015F69C(void *, void *, void *, void *);
extern void func_8015F854(void *, void *, void *, void *);
extern s32 func_8015FF9C(void *, void *, void *, void *);
extern void func_80160234(void *, void *, void *, void *);
extern void func_80160358(void *, void *, void *, void *);
extern s32 func_8016066C(void *, void *, void *, s32);
extern void func_80162574(void *, void *, void *, void *);

extern u8 D_80163E40[];
extern u8 D_80163E48[];
extern u8 D_80163E98[];
extern u8 D_80163EA0[];
extern u8 D_80163EB0[];
extern u8 D_80163EB8[];

/* Update a dungeon actor's animation and dispatch its current behavior. */
void update_actor_animation_and_dispatch_current(void *actor, void *context, void *sprite, EntityRec *entity)
{
    s32 distance;
    s8 room_id;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_8015F0EC_0 *)actor)->unk_9A = 0xE;
        func_8015F69C(actor, context, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        u8 *anim_table;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (((S_8015F0EC_2 *)sprite)->unk_2C == D_80163EA0) {
            return;
        }
        anim_table = D_80163EB0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        select_sprite_entry(sprite,
            anim_table[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_8015F0EC_2 *)sprite)->unk_2C == D_80163EA0) {
            ((S_8015F0EC_0 *)actor)->unk_9A = 0xD;
            ((S_8015F0EC_0 *)actor)->unk_9B = 1;
            ((S_8015F0EC_0 *)actor)->unk_8C = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80163EB0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        {
            void *current_anims;
            u8 *anim_table;

            if (((S_8015F0EC_0 *)actor)->unk_9A != 0xE) {
                ((S_8015F0EC_0 *)actor)->unk_9A = 0xE;
                ((S_8015F0EC_0 *)actor)->unk_B2 = 0;
            }

            current_anims = ((S_8015F0EC_2 *)sprite)->unk_2C;
            if (current_anims == D_80163EB8) {
                if (((S_8015F0EC_2 *)sprite)->unk_14 & 0xE000) {
                    u8 *idle_anims = D_80163E40;

                    (*(void * *)((u8 *)sprite + 0x2C)) = idle_anims;
                    select_sprite_entry(sprite,
                        idle_anims[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_8015F0EC_2 *)sprite)->unk_05 = 1;
                    ((S_8015F0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8015F0EC_0 *)actor)->unk_9E = 0;
                }
            } else {
                anim_table = D_80163E40;
                if (current_anims != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_8015F0EC_2 *)sprite)->unk_05 = 1;
                    ((S_8015F0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8015F0EC_0 *)actor)->unk_9E = 0;
                }
            }
        }

        entity->flags1C |= 0x40000;
        ((S_8015F0EC_0 *)actor)->unk_98 &= 0xFFF7;

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80163E48) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            s16 adjusted_offset;

            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            adjusted_offset = ((S_8015F0EC_0 *)actor)->unk_92.u - ((S_8015F0EC_0 *)actor)->unk_A2.u;
            ((S_8015F0EC_0 *)actor)->unk_A2.s = 0;
            ((S_8015F0EC_0 *)actor)->unk_9E = 0;
            ((S_8015F0EC_0 *)actor)->unk_92.s = adjusted_offset;
            func_80162574(actor, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(((S_8015F0EC_2 *)sprite)->unk_24.at00.v, ((S_8015F0EC_2 *)sprite)->unk_24.at01.v);
    ((S_8015F0EC_2 *)sprite)->unk_26 = room_id;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (((S_8015F0EC_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8015F854(actor, context, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8016066C(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = entity->unk_46 | 0x4000;
            entity->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8015F854(actor, context, sprite, entity);
                return;
            }
        }

        switch ((entity->unk_46 & 0x3FFF) - 1) {
        case 7:
        case 8:
sw_case89:
            if ((func_8015FF9C(actor, context, sprite, entity) << 16) != 0) {
                return;
            }
            func_80160234(actor, context, sprite, entity);
            return;

        case 4:
        case 5:
        case 6:
sw_case567:
            {
                EntityRec *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    ((S_8015F0EC_2 *)sprite)->unk_24.at00.v, ((S_8015F0EC_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &distance);
                player = D_800814A8;
                entity->facing = heading;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80163E98, update_actor_animation_and_dispatch_current);
                    return;
                }
            }
                                /* fallthrough */

        case 11:
            update_actor_status_and_food(entity);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, D_80163E98, update_actor_animation_and_dispatch_current);
            return;

        default:
            func_8015F854(actor, context, sprite, entity);
            return;
        }
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        ((S_8015F0EC_2 *)sprite)->unk_24.at00.v, ((S_8015F0EC_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        ((S_8015F0EC_2 *)sprite)->unk_24.at00.v, ((S_8015F0EC_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                    return;
                }
            }
        }
    } else if ((get_entity_effect_value(entity, 4) << 16) == 0) {
        if (D_800814A8->unk_9A == 0x17) {
            func_80160358(actor, context, sprite, entity);
        }
    }
}
