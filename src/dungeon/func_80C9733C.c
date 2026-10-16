#include "modules/dungeon_ovl_cb3000.h"

void func_80174B3C(S_80174B3C_1 *state, void *unused_position, void *unused_render_state, CB_80174B3C_S_80174B3C_0 *entity) {
    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    state->CB_80174B3C_handler = func_80174B3C;
    state->action = 0x17;
    state->action_tick = 0;
    entity->unk_6D = 0;
    if (!(((CB_80174B3C_S_80174B3C_2 *)(&D_80083460))->unk_02 & 0x2000) && ((func_800A2BDC(entity) << 0x10) == 0)) {
        state->CB_80174B3C_handler = NULL;
        state->action = 0x17;
        state->action_tick = 0;
        D_800DCF5E = 0;
        ((CB_80174B3C_S_80174B3C_2 *)(&D_80083460))->unk_0A = (u16) (((CB_80174B3C_S_80174B3C_2 *)(&D_80083460))->unk_0A + 1);
    }
}
