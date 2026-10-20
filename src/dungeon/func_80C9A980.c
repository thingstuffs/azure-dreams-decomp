#include "modules/dungeon_ovl_cb9000.h"

void func_8016C180(CL_CB9000_80172180_S_80172180_1 *state, s32 position, CL_CB9000_80172180_S_80172180_2 *render_state, void *entity) {
    ((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_71 = (u8) (((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(entity - 0x20, position, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            state->action = 0x11;
            state->handler = 0;
            state->action_tick = 0;
            render_state->unk_2C = D_8016F2B4;
            select_sprite_entry(render_state, *((((s32) (g_game_work.view.viewAngle + ((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_2A + 0x100) >> 9) & 7) + D_8016F2B4), 0);
            ((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_6D = (u8) (((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_6D - 1);
            prepare_directional_attack(entity, render_state, ((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_2A, 1, 0);
            ((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_84 = 0x7C;
            ((CL_CB9000_80172180_S_80172180_0 *)entity)->unk_85 = 0;
        }
    }
}
