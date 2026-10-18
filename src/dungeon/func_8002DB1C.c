#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK initialize_object_entries();          /* extern */
extern M2C_UNK D_800CB21C;
extern M2C_UNK D_800D6910;


/* Initialize the object's state, clear its slot flag, and set its counter to seven. */
void initialize_object_with_seven_tick_counter(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    initialize_object_entries(object, context, &D_800D6910);
    D_80082660[object->unk_60].unk_00 = 0;
    object->unk_54 = &D_800CB21C;
    object->unk_6C.as_s16 = 7;
}
