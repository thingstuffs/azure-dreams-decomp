/* Relink of matched dungeon/func_80977E0C; every changed retail word is a paired relocation. */
#define advance_actor_state_sequence func_8016D60C
#define D_801714D4 D_8016B4D4
#define D_801740F0 D_8016E0F0
#define D_801740F8 D_8016E0F8
#define D_80174150 D_8016E150
#define D_80174158 D_8016E158
#define D_80174160 D_8016E160
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017360C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_8017360C_0;   /* arg0 in func_8016D60C */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value();
extern void func_800A9A04(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_8016DE00(s32, s32, void *, void *);

extern u8 D_8016B4D4[];
extern u8 D_8016E0F0[];
extern u8 D_8016E0F8[];
extern u8 D_8016E150[];
extern u8 D_8016E158[];
extern u8 D_8016E160[];


/* Advances the actor state sequence and selects effects for its facing direction. */
void func_8016D60C(void *action, void *context, void *entity, EntityRec *actor)
{
    s32 effect_entry;
    s32 next_state;
    u8 state;

    state = ((S_8017360C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *local_table_0;
        {
            DungeonGlobalStatus *dungeon_state;
            if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000) == 0) {
                return;
            }

            local_table_0 = D_8016E0F8;

            (*(void * *)((u8 *)entity + 0x2C)) = local_table_0;
            effect_entry = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
            effect_entry &= 7;
            effect_entry += (s32)local_table_0;
            func_80047784(entity, *(u8 *)effect_entry, 0);
            dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->unk_0A)--;
            next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
            ((S_8017360C_0 *)action)->unk_9B = next_state;
            return;
        }

    }

    case 1:
    {
        u8 *local_table_1;
        if (((S_8017360C_0 *)action)->unk_92.s != 0) {
            return;
        }
        local_table_1 = D_8016E150;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_1;
        effect_entry = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_1;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        ((S_8017360C_0 *)action)->unk_9B = next_state;
        return;

    }

    case 2:
    {
        u8 *local_table_2;
        if ((s16)((S_8017360C_0 *)action)->unk_96++ < 2) {
            return;
        }
        local_table_2 = D_8016E158;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_2;
        effect_entry = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_2;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        ((S_8017360C_0 *)action)->unk_9B = next_state;
        return;

    }

    case 3:
    {
        u8 *local_table_3;
        if ((func_80042900(actor, 1) << 16) != 0) {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            s32 actor_flags;

            if ((dungeon_state->flags & 0x1000) != 0) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                begin_ready_actor_directional_action(action, context, entity, 0)) {
                return;
            }

            if (actor->tileY == 0) {
                if ((dungeon_state->flags & 0x2008) != 0) {
                    return;
                }
                advance_actor_pending_action(action, context, entity, actor);
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                return;
            }

            actor_flags = actor->flags1C;
            if ((actor_flags & 0x100) != 0) {
                begin_pushed_actor_move(action, context, entity, actor);
                return;
            }

            {
                u32 adjustment_flag = 0x80000;
                if ((actor_flags & adjustment_flag) != 0) {
                    u16 remaining_amount;

                    begin_actor_move_to_target_facing(action, context, entity, actor);
                    remaining_amount = ((S_8017360C_0 *)action)->unk_92.u;
                    remaining_amount -= ((S_8017360C_0 *)action)->unk_A2;
                    ((S_8017360C_0 *)action)->unk_A2 = 0;
                    ((S_8017360C_0 *)action)->unk_9E = 0;
                    ((S_8017360C_0 *)action)->unk_92.u = remaining_amount;
                    func_8016DE00(action, context, entity, actor);
                    return;
                }
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                EntityRec *owner = D_800814A8;

                if ((s16)check_entity_relation(actor,
                        (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *room_base = &D_80082E80;
                s8 room_id = ((Rec_D_80082E80 *)entity)->unk_26.as_s8;

                if ((room_id == room_base->unk_026 && room_id >= 0) || (s16)get_tile_chebyshev_distance(room_base, entity) < 2) {
                    if ((generate_random_value() & 7) == 0) {
                        func_80042B68(actor, 1);
                    }
                }
            }
            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
        }

        local_table_3 = D_8016E160;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_3;
        effect_entry = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_3;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000) != 0) {
            break;
        }
        ((S_8017360C_0 *)action)->unk_9B++;
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->unk_0A)++;
        }
        return;

    }

    case 4:
    {
        u8 *local_table_4;
        u32 phase_flag = 0x40000;
        u32 phase_flags;

        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        local_table_4 = D_8016E0F8;
        phase_flags = ((u32)actor->flags1C);

        phase_flags |= phase_flag;
        actor->flags1C = phase_flags;
        (*(void * *)((u8 *)entity + 0x2C)) = local_table_4;
        effect_entry = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_4;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        ((S_8017360C_0 *)action)->unk_9B = next_state;
        return;
    }

    case 5:
    {
        u8 *local_table_5;
        if ((s16)((S_8017360C_0 *)action)->unk_96++ < 4) {
            return;
        }

        local_table_5 = D_8016E0F0;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_5;
        effect_entry = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_5;
        func_80047784(entity, *(u8 *)effect_entry, 0);
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->unk_0A)--;
        }
        break;

    }
    default:
        return;
    }

    ((S_8017360C_0 *)action)->unk_8C = D_8016B4D4;
    return;
}
