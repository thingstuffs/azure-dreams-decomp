#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AD7F8_arg0.h"


typedef struct S_800AD7F8_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AD7F8_1;   /* temp_a0 in func_800AD7F8 */

/* Toggle the selected entry flag 0x20 when flag 0x80 is clear. */
void func_800AD7F8(Rec_func_800AD7F8_arg0 *state) {
    u8 flags;
    S_800AD7F8_1 *entry;

    entry = (state->unk_04 * 4) + state->unk_20;
    flags = entry->unk_03;
    if (!(flags & 0x80)) {
        entry->unk_03 = (u8) (flags ^ 0x20);
    }
}
