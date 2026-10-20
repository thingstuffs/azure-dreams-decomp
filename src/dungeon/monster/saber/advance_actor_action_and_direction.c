#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80173D4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173D4C_0;   /* arg0 in advance_actor_action_and_direction */

typedef struct S_80173D4C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173D4C_1;   /* arg2 in advance_actor_action_and_direction */

typedef struct S_80173D4C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173D4C_2;   /* arg3 in advance_actor_action_and_direction */


extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void update_timed_effect_size_and_position(void *, void *, void *, void *);

extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];

/* Advances the actor_in action state and updates its directional animation. */
void advance_actor_action_and_direction(void *action, void *context, void *sprite_in, void *actor_in)
{
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = ((S_80173D4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174E4C;
        select_sprite_entry(sprite_in,
            D_80174E4C[((g_game_work.view.viewAngle + ((S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &g_dungeon_status;
            counter_base->unk_0A =
                ((u16)counter_base->unk_0A) - 1;
        }
        ((S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
            status = &g_dungeon_status;
            if (status->flags & 0x1000) {
                return;
            }
            if (((S_80173D4C_2 *)actor_in)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((S_80173D4C_2 *)actor_in)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite_in, actor_in);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = ((S_80173D4C_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite_in, actor_in);
                update_timed_effect_size_and_position(action, context, sprite_in, actor_in);
                return;
            }
            if (((S_80173D4C_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                if ((check_entity_relation(actor_in,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor_in);
            on_actor_status_updated(actor_in);
            if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
                s8 coordinate = ((S_80173D4C_1 *)sprite_in)->unk_26;
                TileObject *origin = &D_80082E80;
                s32 probe_result;

                if ((coordinate != origin->unk_026) || (coordinate < 0)) {
                    probe_result = get_tile_chebyshev_distance(origin, sprite_in);
                    actor_to_check = actor_in;
                    if (probe_result < 2) {
                        if (!(generate_random_value(actor_in) & 7)) {
                            clear_slots_of_type(actor_in, 1);
                        }
                        actor_to_check = actor_in;
                    }
                } else {
                    if (!(generate_random_value(origin) & 7)) {
                        clear_slots_of_type(actor_in, 1);
                    }
                    actor_to_check = actor_in;
                }
            } else {
                actor_to_check = actor_in;
            }
            if ((get_entity_effect_value(actor_to_check, 1) << 16) != 0) {
                return;
            }

            (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174E54;
            select_sprite_entry(sprite_in,
                D_80174E54[((g_game_work.view.viewAngle + ((S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
                ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;
                return;
            }
            g_dungeon_status.unk_0A++;

            ((S_80173D4C_0 *)action)->unk_9B++;
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174E54;
        select_sprite_entry(sprite_in,
            D_80174E54[((g_game_work.view.viewAngle + ((S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
            ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;
            return;
        }
        g_dungeon_status.unk_0A++;

        ((S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;

        ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;

        return;
    }
}
