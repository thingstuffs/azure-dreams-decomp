#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, s32, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, s32, void *, s32);
extern void begin_actor_move_to_target_facing(void *, s32, void *, void *);
extern void update_timed_effect_size_and_position(void *, s32, void *, void *);

extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];


typedef struct S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801740DC_0;   /* arg0 in update_actor_directional_animation */


/* Updates actor state, directional animation, and the shared transition counter. */
void update_actor_directional_animation(void *actor_in, s32 actor_index, void *target, void *entity_in)
{
    EntityRec *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = ((S_801740DC_0 *)actor_in)->unk_9B;
    switch (state) {
    case 0:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->unk_0A--;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_80174E4C;
    direction = (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9;
    select_sprite_entry(target, D_80174E4C[direction & 7], 0);
    ((S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 1:
    if (entity->tileY != 0) {
        DungeonGlobalStatus *shared_counter;

        (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
        direction = (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, D_80174E54[direction & 7], 0);
        shared_counter = &g_dungeon_status;
        shared_counter->unk_0A++;
        ((S_801740DC_0 *)actor_in)->unk_9B++;
        return;
    } else {
        shared_state = &g_dungeon_status;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, actor_index, target, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor_in, actor_index, target, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, actor_index, target, entity);
            update_timed_effect_size_and_position(actor_in, actor_index, target, entity);
            return;
        }
        if (entity->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
            update_actor_status_and_food(entity);
        } else {
            update_actor_status_and_food(entity);
        }
        on_actor_status_updated(entity);
        if (entity->tileY == 0) {
            return;
        }
        (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
        direction = (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, D_80174E54[direction & 7], 0);
        shared_state->unk_0A++;
    }
    ((S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 2:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->unk_0A--;
    }
    ((S_801740DC_0 *)actor_in)->unk_8C = &D_80171728;

    return;
    default:
        return;
    }
}
