#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800921DC();                            /* extern */
M2C_UNK func_800921F8();                            /* extern */
M2C_UNK func_80094330();     /* extern */
M2C_UNK func_80094910();                            /* extern */
M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80094C74();                      /* extern */
M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_800ABD74();                      /* extern */
extern u8 D_800CFCEF;
extern M2C_UNK D_800D00B8;
extern M2C_UNK D_800FE488;

typedef struct S_800920F4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800920F4_0;   /* arg0 in func_800920F4 */

typedef struct S_800920F4_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800920F4_1;   /* arg1 in func_800920F4 */

void func_800920F4(S_800920F4_0 *arg0, S_800920F4_1 *arg1, M2C_UNK arg2) {
    s16 temp_v0_2;
    u16 temp_v0;

    temp_v0 = arg0->unk_0A + 1;
    arg0->unk_0A = temp_v0;
    if ((s16) temp_v0 == 6) {
        func_80094984(&D_800D00B8, arg0);
    }
    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80094C74(arg1);
    temp_v0_2 = func_80095978(arg1, &D_800FE488);
    if (arg1->unk_0A >= temp_v0_2) {
        func_80094910();
        func_80095A94(arg1, temp_v0_2, &D_800FE488);
        func_800ABD74(arg1);
        func_800921DC(arg0);
        return;
    }
    if (D_800CFCEF != 0) {
        func_80094910();
        arg1->unk_14 = 0;
        func_800954F4(arg1);
        func_80094330(arg0, arg1, arg2);
        return;
    }
    func_80095388(arg1);
}
