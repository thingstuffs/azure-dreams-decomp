#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


typedef struct S_80171FC4_1 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80171FC4_1;   /* arg0 in start_directional_animation_if_allowed */


void select_sprite_entry();         /* extern */
typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */
extern u8 D_80174F28;

/* Update action state and start a directional animation if the actor passes the checks. */
void start_directional_animation_if_allowed(void *action_state, void *action_context, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((S_80171FC4_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((S_80171FC4_1 *)action_state)->unk_9B = 0;
            (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80174F28;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &D_80174F28), 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        }
    }
}
