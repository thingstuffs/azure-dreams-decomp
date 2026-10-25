#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 initialize_object_entries(void *, s32, s32 *);          /* extern */
extern M2C_UNK D_800CB21C;
extern s32 D_800D6910[];


/* Initialize the object's state, clear its slot flag, and set its counter to seven. */
void initialize_object_with_seven_tick_counter(Rec_func_80094268_arg0 *object, s32 unused, s32 context) {
    initialize_object_entries(object, context, D_800D6910);
    object_index_slots[object->unk_60].unk_00 = 0;
    object->unk_54 = &D_800CB21C;
    object->unk_6C.as_s16 = 7;
}
