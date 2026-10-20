/* Relink of matched dungeon/func_809CBEF4; every changed retail word is a paired relocation. */
#define D_80170E54 D_8014CE68
#define D_80173CD4 D_8014F86C
#define D_80173CDC D_8014F86C
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_801736F4_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern void func_800A9A04(void *);
extern void update_actor_status_and_food(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_8014F478(void *, s32, void *, void *);

extern u8 D_8014CE68;
extern u8 D_8014F86C[];
extern u8 D_8014F86C[];

/* Advances the entity's animation state and processes pending actions. */
void func_8014F13C(void *controller, void *context, void *sprite, EntityRec *entity)
{
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = D_8014F86C;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        func_80047784(sprite,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->tileY != 0) {

            (*(void * *)((u8 *)sprite + 0x2C)) = D_8014F86C;
            func_80047784(sprite,
                D_8014F86C[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            (((u32)entity->flags1C)) |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (func_800AA6B4(controller, context, sprite, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            func_800AA258(controller, context, sprite, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            func_8014F478(controller, context, sprite, entity);
            return;
        }

        if (entity->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        func_800A9A04(entity);
        if (entity->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_8014F86C;
        func_80047784(sprite,
            D_8014F86C[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~0x208;
            ((Rec_func_801736F4_arg0 *)controller)->unk_8C = &D_8014CE68;
        }

        return;
    }
}
