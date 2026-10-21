/* Relink of matched dungeon/func_80F8A1F8; every changed retail word is a paired relocation. */
#define D_80174AF4 D_80156AF4
#define D_80174AFC D_80156AFC
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
extern void func_80153138(void *, void *, void *, void *);
extern void func_80155D38(void *, s32, void *, void *);


extern s32 has_pending_actor_or_turn_action(void *);
extern void func_800A9A04(void *);
extern void update_actor_status_and_food(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern u8 D_80156AF4[];
extern u8 D_80156AFC[];


typedef struct S_801739F8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_801739F8_0;   /* arg0 in func_801559F8 */


typedef struct S_801739F8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801739F8_4;   /* global in func_801559F8 */

/* Advances entity animation states and updates the shared activity count. */
void func_801559F8(void *controller, void *context, void *sprite, void *entity)
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
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80156AFC;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        func_80047784(sprite, D_80156AFC[direction & 7], 0);
        ((S_801739F8_0 *)controller)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register DungeonGlobalStatus *activity_counts;

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80156AF4;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            func_80047784(sprite, D_80156AF4[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            activity_counts = &g_dungeon_status;
            (*(u16 *)&activity_counts->activity_counts.parts.pending_action_count)++;
            ((S_801739F8_0 *)controller)->unk_9B++;
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        if (((S_801739F8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            func_800AA6B4(controller, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            func_800AA258(controller, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            ((S_801739F8_0 *)controller)->unk_A0 = 0;
            func_80155D38(controller, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            EntityRec *owner = primary_actor_record;

            if ((func_8009A180(entity,
                    (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        func_800A9A04(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80156AF4;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        func_80047784(sprite, D_80156AF4[direction & 7], 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((S_801739F8_4 *)dungeon_state)->unk_0A++;

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
        ((S_801739F8_0 *)controller)->unk_8C = func_80153138;
        return;
    }

    default:
        return;
    }
}

