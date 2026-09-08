#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_80047C00();                            /* extern */
s32 func_80047CD8();                             /* extern */
M2C_UNK func_80047EEC();                    /* extern */
M2C_UNK func_800481E0();                            /* extern */

/* Runs cleanup, allocates an entity slot, and starts loading it if available. */
void func_80047F90(s16 entity_id) {
    s32 entity_slot;

    func_800481E0();
    func_80047C00();
    entity_slot = func_80047CD8(entity_id);
    if (entity_slot != 0) {
        func_8003F320();
        func_80047EEC(entity_id, entity_slot);
    }
}
