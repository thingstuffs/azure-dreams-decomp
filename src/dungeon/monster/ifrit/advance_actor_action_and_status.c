#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_8017388C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_8017388C_0;   /* arg0 in advance_actor_action_and_status */

typedef struct S_8017388C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_8017388C_1;   /* arg2 in advance_actor_action_and_status */

typedef struct S_8017388C_2 {
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
} S_8017388C_2;   /* arg3 in advance_actor_action_and_status */


extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80173F28(void *, void *, void *, void *);

extern u8 D_80170E84[];
extern u8 D_80174860[];

/* Advance the actor action through animation setup, status handling, and completion. */
void advance_actor_action_and_status(void *in_action, void *in_context, void *in_sprite, void *in_actor)
{
    void *context = in_context;
    void *actor = in_actor;
    s32 state;

    state = ((S_8017388C_0 *)in_action)->unk_9B;
    switch (state) {
    case 0:
        if (((S_8017388C_1 *)in_sprite)->unk_14 & 0xE000) {
            u8 *direction_frames;
            DungeonGlobalStatus *system_base;

            direction_frames = D_80174860;
            (*(void * *)((u8 *)in_sprite + 0x2C)) = direction_frames;
            select_sprite_entry(in_sprite,
                direction_frames[((g_game_work.view.viewAngle + ((S_8017388C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            system_base = &g_dungeon_status;
            (*(u16 *)&system_base->unk_0A)--;
            ((S_8017388C_0 *)in_action)->unk_9B++;
        }
        return;

    case 1:
        if ((get_entity_effect_value(actor, 1) << 16) != 0) {
            s32 actor_flags;
            DungeonGlobalStatus *system_base;

            system_base = &g_dungeon_status;
            if (system_base->flags & 0x1000) {
                return;
            }

            if ((((S_8017388C_2 *)actor)->unk_64 != 0) &&
                (begin_ready_actor_directional_action(in_action, context, in_sprite, 0) != 0)) {
                return;
            }

            if (((S_8017388C_2 *)actor)->unk_25 == 0) {
                if (system_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_action, context, in_sprite, actor);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((S_8017388C_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(in_action, context, in_sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(in_action, context, in_sprite, actor);
                func_80173F28(in_action, context, in_sprite, actor);
                return;
            }

            if (((S_8017388C_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &D_80082E80;
                coordinate = ((S_8017388C_1 *)in_sprite)->unk_26;
                if ((((coordinate == origin->unk_026) &&
                    (coordinate >= 0)) ||
                    (get_tile_chebyshev_distance(origin, in_sprite) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(actor, 1);
                }
            }

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                return;
            }
        }

        if (!(((S_8017388C_1 *)in_sprite)->unk_14 & 0x8000)) {
            DungeonGlobalStatus *system_base = &g_dungeon_status;

            (*(u16 *)&system_base->unk_0A)++;
            ((S_8017388C_0 *)in_action)->unk_9B++;
            return;
        }
        break;

    case 2:
        if (!(((S_8017388C_1 *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *system_base = &g_dungeon_status;
            (*(u16 *)&system_base->unk_0A)--;
        }

        break;
    default:
        return;
    }
    ((S_8017388C_2 *)actor)->unk_1C &= ~0x200;
    in_action = (u8 *)in_action + 0x8C;
    *(void **)in_action = D_80170E84;
}
