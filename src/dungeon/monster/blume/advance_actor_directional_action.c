#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2C];
    void *field_2C;
} SpriteFieldView_80DBC9D8;


typedef struct S_801741D8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801741D8_0;   /* arg0 in advance_actor_directional_action */

typedef struct S_801741D8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801741D8_1;   /* arg2 in advance_actor_directional_action */

typedef struct S_801741D8_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801741D8_2;   /* arg3 in advance_actor_directional_action */


extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80174890(void *, void *, void *, void *);

extern u8 D_80171E20[];
extern u8 D_80175404[];
extern u8 D_8017540C[];

/* Advance the actor action state and update its directional animation. */
void advance_actor_directional_action(void *controller, void *context, void *sprite, void *actor_in)
{
    void *actor;
    u8 state;
    DungeonGlobalStatus *global_state;
    void *check_target;
    void *active_actor;
    s8 tile;

    state = ((S_801741D8_0 *)controller)->unk_9B;
    actor = actor_in;
    switch (state) {
    case 0:
        if (((S_801741D8_1 *)sprite)->unk_14 & 0xE000) {
            DungeonGlobalStatus *counter;

            (((SpriteFieldView_80DBC9D8 *)sprite)->field_2C) = D_80175404;
            select_sprite_entry(sprite,
                D_80175404[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            counter = &g_dungeon_status;
            (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
            ((S_801741D8_0 *)controller)->unk_9B++;
            break;
        }
        break;

    case 1:
        if ((s16)get_entity_effect_value(actor, 1) != 0) {
        global_state = &g_dungeon_status;
        if (global_state->flags & 0x1000) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                break;
            }
        }

        if (((S_801741D8_2 *)actor)->unk_25 == 0) {
            if (global_state->flags & 0x2008) {
                break;
            }
            advance_actor_pending_action(controller, context, sprite, actor);
            break;
        }

        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, actor);
            break;
        }

        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, actor);
            func_80174890(controller, context, sprite, actor);
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_6D == 0) {
            break;
        }

        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            if ((s16)check_entity_relation(
                    actor, (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                break;
            }
        }

        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        do {
            if ((s16)get_entity_effect_value(actor, 1) != 0) {
                check_target = ((u8 *)(&reference_tile_object));
                tile = ((S_801741D8_1 *)sprite)->unk_26;
                if (tile != ((Rec_D_80082E80 *)((u8 *)(&reference_tile_object)))->unk_26.as_s8 || tile < 0) {
                    s16 distance;

                    distance = get_tile_chebyshev_distance(((u8 *)(&reference_tile_object)), sprite);
                    active_actor = actor;
                    if (distance >= 2) {
                        break;
                    }
                    check_target = active_actor;
                }
                if ((generate_random_value(check_target) & 7) == 0) {
                    clear_slots_of_type(actor, 1);
                }
            }
            active_actor = actor;

        } while (0);

        if ((s16)get_entity_effect_value(active_actor, 1) != 0) {
            break;
        }
        }

        (((SpriteFieldView_80DBC9D8 *)sprite)->field_2C) = D_8017540C;
        select_sprite_entry(sprite,
            D_8017540C[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((S_801741D8_1 *)sprite)->unk_14 & 0x8000) {
            ((S_801741D8_0 *)controller)->unk_8C = D_80171E20;
            break;
        } else {
            DungeonGlobalStatus *counter_m = &g_dungeon_status;
            counter_m->activity_counts.parts.pending_action_count++;
        }


        ((S_801741D8_0 *)controller)->unk_9B++;
        break;

    case 2:
        if (((S_801741D8_1 *)sprite)->unk_14 & 0xE000) {
            DungeonGlobalStatus *counter_m = &g_dungeon_status;
            counter_m->activity_counts.parts.pending_action_count--;

            ((S_801741D8_0 *)controller)->unk_8C = D_80171E20;
        }
        break;

    default:
        break;
    }
    return;
}
