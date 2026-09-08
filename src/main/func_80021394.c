#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80021394_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_80021394_0;   /* arg0 in func_80021394 */

/* Set the record's fields at offsets 0x14 and 0x00. */
void func_80021394(S_80021394_0 *record, s32 value_14, s32 value_00) {
    record->unk_14 = value_14;
    record->unk_00 = value_00;
}
