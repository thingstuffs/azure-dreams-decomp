#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C6644_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C6644_0;   /* arg0 in func_800C6644 */


M2C_UNK func_800C4174(S_800C6644_0 *, M2C_UNK, M2C_UNK);
/* Decrement the countdown and call func_800C4174 when it reaches zero or becomes negative. */
void func_800C6644(S_800C6644_0 *object, M2C_UNK callback_arg_1, M2C_UNK callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800C4174(object, callback_arg_1, callback_arg_2);
    }
}
