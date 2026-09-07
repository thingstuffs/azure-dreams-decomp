#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800DBD5C(); /* extern */
extern M2C_UNK D_800814A8;

typedef struct S_800DC000_0 {
    u8 pad_00[0xFC];
    s32 unk_FC;
} S_800DC000_0;   /* *state in func_800DC000 */

typedef struct S_800DC000_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800DC000_1;   /* arg0 in func_800DC000 */

void func_800DC000(S_800DC000_1 *arg0) {
    void **state = (void **)&D_800814A8;

    if (((S_800DC000_0 *)(*state))->unk_FC != arg0->unk_04) {
        func_800DBD5C(((S_800DC000_0 *)(*state))->unk_FC, arg0->unk_04, 8, 0x1A8, 0x1E0, 0);
        arg0->unk_04 = ((S_800DC000_0 *)(*state))->unk_FC;
    }
}
