#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
typedef struct Ent Ent;


typedef struct S_801721C0_1 {
    u8 pad_00[0x98];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_801721C0_1;   /* arg0 in finish_actor_tile_move_and_check_trap */


void select_sprite_entry();         /* extern */
Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */
extern u8 D_80176480;

/* Update the actor action state and directional animation when both checks pass. */
/* Starts Cyclone's directional attack when an action slot is free, consumes a pending turn, and prepares
 * damage. */
void finish_actor_tile_move_and_check_trap(void *action_state, s32 action_ctx, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_ctx, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((S_801721C0_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((S_801721C0_1 *)action_state)->unk_9B = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_80176480;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &D_80176480), 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            ((S_801721C0_1 *)action_state)->unk_98 = (u16) (((S_801721C0_1 *)action_state)->unk_98 | 8);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        }
    }
}
