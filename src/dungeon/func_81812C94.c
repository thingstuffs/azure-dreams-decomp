#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80027AD0();            /* extern */
M2C_UNK func_80027B44();               /* extern */
M2C_UNK func_80027B6C();               /* extern */
M2C_UNK func_80027BBC();                    /* extern */
M2C_UNK func_8004CB2C();                      /* extern */

typedef struct S_80027C94_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x38];
    s32 unk_40;
    u8 pad_44[0x44];
    s32 unk_88;
} S_80027C94_0;   /* arg0 in func_80027C94 */

void func_80027C94(void *arg0) {
    func_80027B44(((S_80027C94_0 *)arg0)->unk_88, ((S_80027C94_0 *)arg0)->unk_00, ((S_80027C94_0 *)arg0)->unk_04);
    func_80027AD0(arg0, ((S_80027C94_0 *)arg0)->unk_00, ((S_80027C94_0 *)arg0)->unk_04);
    func_80027B6C(((S_80027C94_0 *)arg0)->unk_88, ((S_80027C94_0 *)arg0)->unk_00, ((S_80027C94_0 *)arg0)->unk_04);
    func_80027BBC(((S_80027C94_0 *)arg0)->unk_88, ((S_80027C94_0 *)arg0)->unk_40);
    func_8004CB2C(arg0 + 0x2C);
}
