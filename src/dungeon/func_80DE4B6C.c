#include "modules/dungeon_ovl_e0365c.h"

void start_actor_directional_animation(void *actor_state, s32 action_param, void *sprite, EntityRec *actor) {
    actor->unk_71 = actor->unk_71 & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_param, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_9A = 0x18;
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_8C = 0;
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_9B = 0;
            (*(s32 * *)((u8 *)sprite + 0x2C)) = &D_80174558;
            func_80047784(sprite,
                          *((((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                            + (u8 *)&D_80174558),
                          0);
            advance_status_timers(actor);
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
    }
}
