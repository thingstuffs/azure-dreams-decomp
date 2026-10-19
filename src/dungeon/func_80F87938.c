#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171138_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80171138_0;   /* arg0 in update_bank_actor_state */

   /* arg3 in update_bank_actor_state */

typedef struct S_80171138_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171138_2;   /* arg2 in update_bank_actor_state */


extern s8 find_active_rect_containing_point(u8, u8);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern u8 D_80174ADC[];
extern u8 D_80174AEC[];
extern u8 D_80174AF4[];
extern u8 D_80174AFC[];

/* Updates actor behavior, animation, and facing from its status and dungeon state. */
void update_bank_actor_state(void *actor_in, void *context_in, void *sprite_in, void *stats_in)
{
    void *actor;
    void *context;
    void *sprite;
    ActorUnsignedFlagsView *stats;
    s32 angle_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_state;
    u32 dungeon_flags = g_dungeon_status.flags;

    actor = actor_in;
    context = context_in;
    sprite = sprite_in;
    stats = stats_in;

    if (dungeon_flags & 0x1000) {
        ((S_80171138_0 *)actor)->unk_9A = 0xE;
        advance_bank_actor_path(actor_in, context_in);
        return;
    }

    if (stats->unk_25 == 0) {
        advance_actor_pending_action(actor, context, sprite, stats);
        if (((S_80171138_2 *)sprite)->unk_2C == D_80174AFC) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AF4;
        func_80047784(sprite,
            D_80174AF4[((g_game_work.view.viewAngle + stats->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (stats->unk_1C & 0x200) {
        if (((S_80171138_2 *)sprite)->unk_2C == D_80174AFC) {
            ((S_80171138_0 *)actor)->unk_9A = 0xD;
            ((S_80171138_0 *)actor)->unk_9B = 1;
            ((S_80171138_0 *)actor)->unk_8C = 0;
            stats->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80174AF4) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (stats->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, stats);
            return;
        }

        if (((S_80171138_0 *)actor)->unk_9A != 0xE) {
            ((S_80171138_0 *)actor)->unk_9A = 0xE;
        }

        if (((S_80171138_2 *)sprite)->unk_2C != D_80174AD4) {
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AD4;
            func_80047784(sprite,
                D_80174AD4[((g_game_work.view.viewAngle + stats->unk_2A + 0x100) >> 9) & 7],
                ((S_80171138_0 *)actor)->unk_A0);
        }

        stats->unk_1C |= 0x40000;
        ((S_80171138_0 *)actor)->unk_98 &= 0xFFF7;

        if (stats->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174ADC) != 0) {
                return;
            }
        }

        if (stats->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, stats);
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            update_bank_actor_sprite_state(actor, context, sprite, stats);
            return;
        }

        if ((can_entity_gain_level(stats) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, stats);
        }
    }

    tile_index = find_active_rect_containing_point(((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v);
    ((S_80171138_2 *)sprite)->unk_26 = tile_index;

    if (stats->unk_6D > 0) {
        if (stats->unk_1C & 0x20) {
            update_actor_status_and_food(stats);
            return;
        }
        if (!(((S_80171138_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX))) {
            action_state = stats->unk_46;
            if (!(action_state & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(stats,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((complete_actor_jump_to_destination(actor, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action_state = stats->unk_46 | 0x4000;
                stats->unk_46 = action_state;
            }

            if (action_state & 0x8000) {
                switch (stats->unk_46 & 0x3FFF) {
                case 9:
                    start_bank_actor_hit_reaction(actor, context, sprite, stats);
                    return;

                case 8:
                    if ((begin_bank_directional_effect(actor, context, sprite, stats) << 16) != 0) {
                        return;
                    }
                    initialize_bank_actor_action(actor, context, sprite, stats);
                    return;

                case 12:
                    update_actor_status_and_food(stats);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    EntityRec *player;
                    s16 facing_angle;

                    facing_angle = (s16)get_rounded_facing_and_rounding_flag(
                        ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &angle_aux);
                    player = D_800814A8;
                    stats->unk_2A = facing_angle;
                    if (player->unk_9A != 0x11) {
                        update_actor_status_and_food(stats);
                        return;
                    }
                }

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(actor, context, sprite, D_80174AEC, update_bank_actor_state);
                    return;

                case 4:
                case 10:
                case 11:
                default:
                    break;
                }
            }
        }
        select_bank_actor_movement(actor, context, sprite, stats);
        return;
    }

    status_flags = stats->unk_1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }

    {

        if ((compare_monster_neighbor_values(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
            stats->unk_2A = (s16)get_rounded_facing_and_rounding_flag(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &angle_aux);
        }
    }
    return;
}

