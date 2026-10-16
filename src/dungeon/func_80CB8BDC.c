#include "modules/dungeon_ovl_cd7000.h"

void func_8014E3DC(void *state_arg,void *position,void *render_state,void *entity) {
    S_801723DC_0 *state=state_arg;
    if (func_800AB1C0(state,position,render_state,entity) != 0) {
        func_800AD594(entity, 4);
        func_800A4ACC(entity);
        if ((func_800AD9B4(render_state, entity) << 0x10) > 0) {
            state->CL_CD7000_801723DC_unk_8C = func_8014D02C;
            state->unk_90 = 0;
        }
    }
}
