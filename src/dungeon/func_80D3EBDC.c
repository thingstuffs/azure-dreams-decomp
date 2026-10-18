#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801743DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_801743DC_0;   /* arg0 in advance_actor_action */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void func_800A9A04(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void update_actor_action_transition(void *, void *, void *, void *);

extern u8 D_800E2428[];
extern u8 D_800E2430[];
extern u8 D_80171A80[];

/* Advances the entity action through animation, behavior, and callback transitions. */
void advance_actor_action(void *action, void *context, void *sprite, EntityRec *entity)
{
    s32 entity_flags;
    u16 action_value;
    u16 value_offset;
    DungeonGlobalStatus *global_base;
    s32 phase;

    phase = ((S_801743DC_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2428;
        func_80047784(sprite,
            D_800E2428[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base = &g_dungeon_status;

            (*(u16 *)&counter_base->unk_0A)--;
        }
        ((S_801743DC_0 *)action)->unk_9B++;
        return;
    case 1:
        global_base = &g_dungeon_status;
        if (global_base->flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(action, context, sprite, 0) != 0) {
                return;
            }
        }
        if (entity->tileY == 0) {
            if (global_base->flags & 0x2008) {
                return;
            }
            advance_actor_pending_action(action, context, sprite, entity);
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            action_value = ((S_801743DC_0 *)action)->unk_92;
            value_offset = ((S_801743DC_0 *)action)->unk_A2;
            ((S_801743DC_0 *)action)->unk_A2 = 0;
            ((S_801743DC_0 *)action)->unk_9E = 0;
            ((S_801743DC_0 *)action)->unk_92 = action_value - value_offset;
            update_actor_action_transition(action, context, sprite, entity);
            return;
        }
        if (entity->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            EntityRec *owner = D_800814A8;

            if ((check_entity_relation(entity,
                    (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_food(entity);
        func_800A9A04(entity);
        if ((func_80042900(entity, 1) << 16) != 0) {
            TileObject *origin = &D_80082E80;
            s8 tile = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;

            if (((tile == origin->unk_026) && (tile >= 0)) ||
                ((s16)get_tile_chebyshev_distance(origin, sprite) < 2)) {
                if (!(generate_random_value() & 7)) {
                    func_80042B68(entity, 1);
                }
            }
        }
        if ((func_80042900(entity, 1) << 16) != 0) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_800E2430;
        func_80047784(sprite,
            D_800E2430[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)&entity->flags1C) |= 0x40000;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_801743DC_0 *)action)->unk_8C = D_80171A80;
            return;
        }
        {
            DungeonGlobalStatus *counter_base = &g_dungeon_status;

            ((S_801743DC_0 *)action)->unk_9B++;
            (*(u16 *)&counter_base->unk_0A)++;
        }
        return;
    case 2:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;
        ((S_801743DC_0 *)action)->unk_8C = D_80171A80;
        return;
    default:
        return;
    }
}
