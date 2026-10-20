#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

void select_sprite_entry();         /* extern */
s32 check_entity_relation();                     /* extern */
s8 find_active_rect_containing_point();                           /* extern */
void update_actor_status_and_food();                      /* extern */
void begin_pushed_actor_move(); /* extern */
s32 begin_ready_actor_directional_action(); /* extern */
void begin_actor_move_to_target_facing(); /* extern */
void func_8016FA84(void *actor, void *action, void *entity, void *path_arg);                            /* extern */
void advance_boss_actor_movement_state(); /* extern */
s32 update_boss_action_result(); /* extern */
s32 func_8017092C(); /* extern */
s32 advance_boss_command_stream();     /* extern */
extern u8 D_80174A2C[];
extern u8 D_80174A64[];


typedef struct S_8016F78C_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
} S_8016F78C_0;   /* arg0 in update_boss_actor_action */

/* Updates actor state, directional animation, and action handling. */
void update_boss_actor_action(void *actor, void *context, void *sprite, EntityRec *entity) {
    u8 stack_pad[8];
    u8 current_state;
    s32 next_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_8016F78C_0 *)actor)->unk_9A = 0xEU;
        func_8016FA84(actor, context, sprite, entity);
        return;
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }
        current_state = ((S_8016F78C_0 *)actor)->unk_9A;
        next_state = 0xE;
        if (current_state != next_state) {
            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174A2C) {
                (*(u8 **)((u8 *)sprite + (0x2C))) = D_80174A2C;
                select_sprite_entry(sprite, D_80174A2C[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
            }
            ((S_8016F78C_0 *)actor)->unk_9A = next_state;
        }
        ((S_8016F78C_0 *)actor)->unk_98 = (u16) (((S_8016F78C_0 *)actor)->unk_98 & 0xFFF3);
        if (!((((EntityRec *)entity)->unk_64 == 0) || (begin_ready_actor_directional_action(actor, context, sprite, D_80174A64) == 0))) {
            return;
        }
        if (entity->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_8017092C(actor, context, sprite, entity);
            (*(u8 **)((u8 *)sprite + (0x2C))) = D_80174A2C;
            select_sprite_entry(sprite, D_80174A2C[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
            ((S_8016F78C_0 *)actor)->unk_90 = 0;
            return;
        }
    }
    ((Rec_D_80082E80 *)sprite)->unk_26.as_s8 = find_active_rect_containing_point(((Rec_D_80082E80 *)sprite)->unk_24,
        ((Rec_D_80082E80 *)sprite)->unk_25);
    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (!(g_dungeon_status.flags & 0x2000) || ((check_entity_relation(entity, ((s32)D_800814A8->unk_58) + 0x20) << 0x10)
                == 0)) {
                if (D_80013714 & 8) {
                    advance_boss_command_stream(actor, context, sprite);
                    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
                    update_actor_status_and_food(entity);
                    entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
                    return;
                }
                if ((update_boss_action_result(actor, context, sprite, 0) << 0x10) == 0) {
                    return;
                }
                entity->unk_46 = (u16) (entity->unk_46 | 0x4000);
            } else {
                return;
            }
        }
        entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
        entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
        update_actor_status_and_food(entity);
        advance_boss_actor_movement_state(actor, context, sprite, entity);
    }
}
