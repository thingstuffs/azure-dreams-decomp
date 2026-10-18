#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
void apply_object_setup_and_update(void *, M2C_UNK, M2C_UNK);
/* Clear the object's slot in the D_80082660 table, then run the shared handler. */
void clear_object_slot_table_run(void *obj, M2C_UNK param_a, M2C_UNK param_b)
{
    *(((u8 *) (D_80082660)) + ((*((s32 *) (((s8 *) obj) + 0x60))) * 8)) = 0;
    apply_object_setup_and_update(obj, param_a, param_b);
}
