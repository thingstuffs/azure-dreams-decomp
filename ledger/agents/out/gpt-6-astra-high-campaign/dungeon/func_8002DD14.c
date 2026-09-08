#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C4174(void *);                            /* extern */


/* Decrement the object counter and call its handler when it reaches zero. */
void func_800CB474(Rec_func_80094268_arg0 *object) {
    u16 remaining_count;

    remaining_count = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        func_800C4174(object);
    }
}
