#include "common.h"
#include "shared/object_index_slots.h"
void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Clear the object's slot in the D_80082660 table, then run the shared handler. */
void clear_object_slot_table_run(void *obj, s32 param_a, s32 param_b)
{
    *(((u8 *) (object_index_slots)) + ((*((s32 *) (((s8 *) obj) + 0x60))) * 8)) = 0;
    apply_object_setup_and_update(obj, param_a, param_b);
}
