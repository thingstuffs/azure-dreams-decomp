#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C4174(void *);                            /* extern */


void func_800CB474(Rec_func_80094268_arg0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C.as_u16 - 1;
    arg0->unk_6C.as_u16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C4174(arg0);
    }
}
