#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039760_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x7];
    u8 unk_27;
} S_80039760_0;   /* arg0 in func_80039760 */

typedef struct S_80039760_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_80039760_1;   /* temp_v1 in func_80039760 */


/* Set the event-script VM pointer from the selected little-endian table entry. */
void func_80039760(S_80039760_0 *vm) {
    S_80039760_1 *jump_entry;

    jump_entry = (vm->unk_27 * 4) + vm->unk_1C;
    vm->unk_1C = (s32) (jump_entry->unk_00 + (jump_entry->unk_01 << 8) + (jump_entry->unk_02 << 0x10) + (jump_entry->unk_03 << 0x18));
}
