#include "common.h"
#include "shared/town_handler.h"




typedef struct S_80094A60_0 {
    u8 pad_00[0x16];
    s16 unk_16;
} S_80094A60_0;   /* arg1 in func_80094A60 */

/* Passes the selected nonzero table value to func_80094A38. */
void func_80094A60(s32 *values, S_80094A60_0 *selector, void *ptr2) {
    s32 value = values[selector->unk_16];
    if (value != 0) {
        func_80094A38(value, (Rec_D_80082D58 *) selector, ptr2);
    }
}
