#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_809A0A34_1 {
    u8 pad_00[0x98];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_809A0A34_1;   /* arg0 in start_kewne_attack_action */

void select_sprite_entry();         /* extern */
typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */
extern u8 kewne_frame_set_3;

/* Clears the actor flag and conditionally updates its state and directional animation. */
void start_kewne_attack_action(void *controller, void *action_context, SpriteFrameState *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((S_809A0A34_1 *)controller)->unk_9A = 0x17;
            (*(s32 *)((u8 *)controller + 0x8C)) = 0;
            ((S_809A0A34_1 *)controller)->unk_9B = 0;
            (sprite->frameTable) = &kewne_frame_set_3;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &kewne_frame_set_3), 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            ((S_809A0A34_1 *)controller)->unk_98 = (u16) (((S_809A0A34_1 *)controller)->unk_98 | 8);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}
