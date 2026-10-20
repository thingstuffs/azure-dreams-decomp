#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/position_views.h"


extern s32 has_pending_actor_or_turn_action(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern u8 D_80174AF4[];
extern u8 D_80174AFC[];


typedef struct S_801739F8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_801739F8_0;   /* arg0 in advance_bank_actor_animation */


   /* global in advance_bank_actor_animation */

/* Advances entity animation states and updates the shared activity count. */
void advance_bank_actor_animation(void *controller, void *context, void *sprite, void *entity)
{
    void *saved_context;
    register void *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define controller controller
#define context saved_context
#define sprite sprite

    state = ((S_801739F8_0 *)controller)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        DungeonGlobalStatus *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = &g_dungeon_status;
        (*(u16 *)&activity_counts->activity_counts.parts.pending_action_count)--;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AFC;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_80174AFC[direction & 7], 0);
        ((S_801739F8_0 *)controller)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register DungeonGlobalStatus *activity_counts;

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AF4;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            select_sprite_entry(sprite, D_80174AF4[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            activity_counts = &g_dungeon_status;
            (*(u16 *)&activity_counts->activity_counts.parts.pending_action_count)++;
            ((S_801739F8_0 *)controller)->unk_9B++;
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        if (((UnsignedPositionXZView *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            begin_ready_actor_directional_action(controller, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            ((S_801739F8_0 *)controller)->unk_A0 = 0;
            update_bank_actor_sprite_state(controller, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
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
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174AF4;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_80174AF4[direction & 7], 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((UnsignedPositionXZView *)dungeon_state)->unk_0A++;

        ((S_801739F8_0 *)controller)->unk_9B++;
        return;

    case 2:
    {
        DungeonGlobalStatus *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = &g_dungeon_status;
        (*(u16 *)&activity_counts->activity_counts.parts.pending_action_count)--;
        ((EntityRec *)entity)->flags1C &= ~0x208;
        ((S_801739F8_0 *)controller)->unk_8C = update_bank_actor_state;
        return;
    }

    default:
        return;
    }
}

