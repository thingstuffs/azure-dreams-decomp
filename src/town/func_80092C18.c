#include "modules/town_player_init.h"

/* Initialize the global record using its preceding value and D_800D0178. */
void initialize_global_scene_record(void) {
    s32 *record = &D_800834B8;
    call_the_handler_selects_nonzero_entry(&D_800D0178, record, ((func_80092C18_S_80090378_0 *)((u8 *)record - 0x14))->unk_00);
}
