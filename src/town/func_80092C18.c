#include "modules/town_player_init.h"

/* Initialize the global record using its preceding value and D_800D0178. */
void func_80090378(void) {
    s32 *record = &D_800834B8;
    func_80094984(&D_800D0178, record, ((func_80092C18_S_80090378_0 *)((u8 *)record - 0x14))->unk_00);
}
