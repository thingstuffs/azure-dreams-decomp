#define update_directional_sprite_state_and_signals func_801666B8
#define has_pending_actor_or_turn_action func_800A1904
#define func_80042B68 func_8004272C
#define D_801740F0 D_80166E94
#define D_801714D4 D_80164514
#define advance_actor_pending_action func_800A9454
#define begin_actor_move_to_target_facing func_800A9540
#define func_800A9A04 update_fading_effect_motion
#define D_80174150 D_80166EBC
#define D_80174160 D_80166ECC
#define check_entity_relation func_80098F70
#define D_801740F8 D_80166E94
#define D_80174158 D_80166EC4
#define begin_ready_actor_directional_action func_800A936C
#define update_actor_status_and_food func_800A86C4
#define func_80047784 func_80047320
#define generate_random_value func_800A59E8
#define primary_actor_record D_800803DC
#define begin_pushed_actor_move func_800A8F10
#define func_80042900 func_800424C4
#define reference_tile_object free_node_list_head
#define get_tile_chebyshev_distance func_8009EB30
/* Relink of matched dungeon/func_80977E0C at file 0x997E0C; imports and data use paired retail relocations. */
#define g_dungeon_status D_80085990
#define g_game_work D_80084818
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
} S_8017360C_0;   /* arg0 in func_80165EC4 */


extern s32 func_800424C4(void *, s32);
extern void func_8004272C(void *, s32);
extern void func_80047320(void *, u8, s32);
extern s32 func_80098F70(void *, void *);
extern s32 func_8009EB30(void *, void *);
extern s32 func_800A1904(void *);
extern s32 func_800A59E8();
extern void update_fading_effect_motion(void *);
extern void func_800A86C4(void *);
extern void func_800A8F10(void *, void *, void *, void *);
extern s32 func_800A936C(void *, void *, void *, s32);
extern void func_800A9454(void *, void *, void *, void *);
extern void func_800A9540(void *, void *, void *, void *);
extern void func_801666B8(void *, void *, void *, void *);

extern u8 D_80164514[];
extern u8 D_80166E94[];
extern u8 D_80166E94[];
extern u8 D_80166EBC[];
extern u8 D_80166EC4[];
extern u8 D_80166ECC[];


/* Advances the actor state sequence and selects effects for its facing direction. */
void func_80165EC4(void *action, void *context, void *entity, EntityRec *actor)
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

            local_table_0 = D_80166E94;

            (*(void * *)((u8 *)entity + 0x2C)) = local_table_0;
            effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
            effect_entry &= 7;
            effect_entry += (s32)local_table_0;
            func_80047320(entity, *(u8 *)effect_entry, 0);
            dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->activity_counts.parts.pending_action_count)--;
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
        local_table_1 = D_80166EBC;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_1;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_1;
        func_80047320(entity, *(u8 *)effect_entry, 0);
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
        local_table_2 = D_80166EC4;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_2;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_2;
        func_80047320(entity, *(u8 *)effect_entry, 0);
        ((S_8017360C_0 *)action)->unk_96 = 0;
        next_state = ((S_8017360C_0 *)action)->unk_9B + 1;
        ((S_8017360C_0 *)action)->unk_9B = next_state;
        return;

    }

    case 3:
    {
        u8 *local_table_3;
        if ((func_800424C4(actor, 1) << 16) != 0) {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            s32 actor_flags;

            if ((dungeon_state->flags & 0x1000) != 0) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                func_800A936C(action, context, entity, 0)) {
                return;
            }

            if (actor->tileY == 0) {
                if ((dungeon_state->flags & 0x2008) != 0) {
                    return;
                }
                func_800A9454(action, context, entity, actor);
                return;
            }

            if ((s16)func_800A1904(actor) != 0) {
                return;
            }

            actor_flags = actor->flags1C;
            if ((actor_flags & 0x100) != 0) {
                func_800A8F10(action, context, entity, actor);
                return;
            }

            {
                u32 adjustment_flag = 0x80000;
                if ((actor_flags & adjustment_flag) != 0) {
                    u16 remaining_amount;

                    func_800A9540(action, context, entity, actor);
                    remaining_amount = ((S_8017360C_0 *)action)->unk_92.u;
                    remaining_amount -= ((S_8017360C_0 *)action)->unk_A2;
                    ((S_8017360C_0 *)action)->unk_A2 = 0;
                    ((S_8017360C_0 *)action)->unk_9E = 0;
                    ((S_8017360C_0 *)action)->unk_92.u = remaining_amount;
                    func_801666B8(action, context, entity, actor);
                    return;
                }
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)func_800A1904(actor) != 0) {
                EntityRec *owner = D_800803DC;

                if ((s16)func_80098F70(actor,
                        (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            func_800A86C4(actor);
            update_fading_effect_motion(actor);
            if ((func_800424C4(actor, 1) << 16) != 0) {
                TileObject *room_base = &free_node_list_head;
                s8 room_id = ((Rec_D_80082E80 *)entity)->unk_26.as_s8;

                if ((room_id == room_base->room_index && room_id >= 0) || (s16)func_8009EB30(room_base, entity) < 2) {
                    if ((func_800A59E8() & 7) == 0) {
                        func_8004272C(actor, 1);
                    }
                }
            }
            if ((func_800424C4(actor, 1) << 16) != 0) {
                return;
            }
        }

        local_table_3 = D_80166ECC;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_3;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_3;
        func_80047320(entity, *(u8 *)effect_entry, 0);
        if ((((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000) != 0) {
            break;
        }
        ((S_8017360C_0 *)action)->unk_9B++;
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->activity_counts.parts.pending_action_count)++;
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

        local_table_4 = D_80166E94;
        phase_flags = ((u32)actor->flags1C);

        phase_flags |= phase_flag;
        actor->flags1C = phase_flags;
        (*(void * *)((u8 *)entity + 0x2C)) = local_table_4;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_4;
        func_80047320(entity, *(u8 *)effect_entry, 0);
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

        local_table_5 = D_80166E94;

        (*(void * *)((u8 *)entity + 0x2C)) = local_table_5;
        effect_entry = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        effect_entry &= 7;
        effect_entry += (s32)local_table_5;
        func_80047320(entity, *(u8 *)effect_entry, 0);
        {
            DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
            (*(u16 *)&dungeon_state->activity_counts.parts.pending_action_count)--;
        }
        break;

    }
    default:
        return;
    }

    ((S_8017360C_0 *)action)->unk_8C = D_80164514;
    return;
}
