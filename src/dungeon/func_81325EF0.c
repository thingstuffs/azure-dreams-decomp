#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

s32 func_80042900(void *, s32);
void func_80042B68(void *, s32);
void func_80047784(void *, s32, s32);
s32 check_entity_relation(void *, void *);
s16 get_tile_chebyshev_distance(void *, void *);
s32 has_pending_actor_or_turn_action(void *);
s32 generate_random_value(void);
void func_800A9A04(void *);
void update_actor_status_and_food(void *);
void begin_pushed_actor_move(void *, s32, void *, void *);
s32 begin_ready_actor_directional_action(void *, s32, void *, void *);
void begin_actor_move_to_target_facing(void *, s32, void *, void *);
void func_8016DAA4(void *, s32, void *, void *);

extern u8 D_8016B778[];
extern u8 D_801746A4[];
extern u8 D_801746AC[];
extern u8 D_801746C4[];
extern u8 D_80080000[];

typedef struct S_8016D6F0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x18];
    u8 unk_B4;
} S_8016D6F0_0;   /* arg0 in advance_actor_action_and_animation */

typedef struct S_8016D6F0_2 {
    u8 pad_00[0x14A8];
    u8 * unk_14A8;
    u8 pad_14AC[0x1D7C];
    s16 unk_3228;
    u8 pad_322A[0x238];
    u16 unk_3462;
} S_8016D6F0_2;   /* base8008 in advance_actor_action_and_animation */

typedef struct S_8016D6F0_5 {
    u8 pad_00[0x3714];
    u16 unk_3714;
} S_8016D6F0_5;   /* base8001 in advance_actor_action_and_animation */

typedef struct S_8016D6F0_9 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8016D6F0_9;   /* ((S_8016D6F0_2 *)base8008)->unk_14A8 in advance_actor_action_and_animation */

/* Advance the actor's action state, directional animation, and completion callback. */
void advance_actor_action_and_animation(S_8016D6F0_0 *actor, s32 actor_id, Rec_D_80082E80 *sprite, EntityRec *entity)
{
    TileObject *reference_pos;
    DungeonGlobalStatus *counter_base;
    u8 *flags_page;
    DungeonGlobalStatus *reference_base;
    void *action_actor;
    s32 state;
    s32 entity_flags;
    s32 action_flag;
    s8 room_id;

    state = actor->unk_9B;
    switch (state) {
    case 0:
        if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        {
            u8 *dir_table = D_801746A4;
            sprite->unk_2C.as_pu8 = dir_table;
            func_80047784(
                sprite,
                dir_table[((g_game_work.view.viewAngle +
                            entity->facing + 0x100) >> 9) & 7],
                0);
        }
        counter_base = &g_dungeon_status;
        counter_base->unk_0A--;
        actor->unk_9B++;
        return;
    case 1:
        if ((func_80042900(entity, 1) << 0x10) != 0) {
            if (((S_8016D6F0_2 *)D_80080000)->unk_3462 & 0x1000) {
                return;
            }
            flags_page = (u8 *)0x80010000;
            if (actor->unk_B4 == 0 && !(((S_8016D6F0_5 *)flags_page)->unk_3714 & 8)) {
                if (entity->unk_64 != 0) {
                    if (begin_ready_actor_directional_action(actor, actor_id, sprite, D_801746C4) != 0) {
                        return;
                    }
                }
            } else if (entity->unk_64 != 0) {
                reference_base = &g_dungeon_status;
                if (((s32)reference_base->unk_10) ==
                    (u32)((u8 *)entity - 0x20)) {
                    (*(s32 *)&reference_base->unk_10) &= 0x7FFFFFFF;
                }
            }
            if ((has_pending_actor_or_turn_action(entity) << 0x10) != 0) {
                return;
            }
            entity_flags = entity->flags1C;
            action_flag = entity_flags & 0x100;
            action_actor = actor;
            if (action_flag) {
                begin_pushed_actor_move(action_actor, actor_id, sprite, entity);
                return;
            }
            if (entity_flags & 0x80000) {
                begin_actor_move_to_target_facing(action_actor, actor_id, sprite, entity);
                func_8016DAA4(actor, actor_id, sprite, entity);
                return;
            }
            if (entity->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(entity) << 0x10) != 0) {
                if ((check_entity_relation(
                         entity,
                         ((S_8016D6F0_9 *)(((S_8016D6F0_2 *)D_80080000)->unk_14A8))->unk_58 + 0x20)
                     << 0x10) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(entity);
            func_800A9A04(entity);
            if ((func_80042900(entity, 1) << 0x10) != 0) {
                reference_pos = &D_80082E80;
                room_id = sprite->unk_26.as_s8;
                if (((room_id == reference_pos->unk_026 && room_id >= 0) ||
                     get_tile_chebyshev_distance(reference_pos, sprite) < 2) &&
                    (generate_random_value() & 7) == 0) {
                    func_80042B68(entity, 1);
                }
            }
            if ((func_80042900(entity, 1) << 0x10) != 0) {
                return;
            }
        }
        {
            u8 *dir_table = D_801746AC;
            sprite->unk_2C.as_pu8 = dir_table;
            func_80047784(
                sprite,
                dir_table[((g_game_work.view.viewAngle +
                            entity->facing + 0x100) >> 9) & 7],
                0);
        }
        if (sprite->unk_14.at00_u16.v & 0x8000) {
            actor->unk_8C = D_8016B778;
            return;
        }
        {
            DungeonGlobalStatus *counter_update = &g_dungeon_status;
            counter_update->unk_0A++;
        }
        actor->unk_9B++;
        return;
    case 2:
        if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *counter_update = &g_dungeon_status;
            counter_update->unk_0A--;
        }
        actor->unk_8C = D_8016B778;
        break;
    default:
        return;
    }
}
