#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C3BB8_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C3BB8_0;   /* arg0 in func_800C3BB8 */


M2C_UNK func_800C41D4(S_800C3BB8_0 *);
/* Decrements the timer and calls the handler when its signed value is nonpositive. */
void func_800C3BB8(S_800C3BB8_0 *object) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C - 1;
    object->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_800C41D4(object);
    }
}
