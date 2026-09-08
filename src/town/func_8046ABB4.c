#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001BBB4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001BBB4_1;   /* ((arg1 * 0x10) + arg0->unk_10) in func_8001BBB4 */




s32 func_8001AB68();                                /* extern */
M2C_UNK func_8001E5F0();                     /* extern */

typedef struct S_8001BBB4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001BBB4_0;   /* arg0 in func_8001BBB4 */

/* Store the data block in the indexed entry and invoke func_8001E5F0 for 0x402. */
s32 func_8001BBB4(S_8001BBB4_0 *entry_owner, s32 entry_index) {
    ((S_8001BBB4_1 *)(((entry_index * 0x10) + entry_owner->unk_10)))->unk_08 = func_8001AB68();
    func_8001E5F0(0x402);
    return 0;
}
