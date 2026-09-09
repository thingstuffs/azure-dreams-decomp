#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800CB474_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800CB474_0;   /* arg0 in func_800CB474 */


M2C_UNK func_800C4174(S_800CB474_0 *, M2C_UNK, M2C_UNK);
/* Decrement the countdown and call func_800C4174 when it reaches zero. */
void func_800CB474(S_800CB474_0 *object, M2C_UNK context, M2C_UNK update_data) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C - 1;
    object->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_800C4174(object, context, update_data);
    }
}
