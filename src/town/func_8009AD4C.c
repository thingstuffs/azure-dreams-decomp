#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80098524();                            /* extern */
M2C_UNK func_80098928();        /* extern */
extern M2C_UNK D_800FE488;

typedef struct S_800984AC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800984AC_0;   /* arg1 in func_800984AC */

void func_800984AC(s32 arg0, S_800984AC_0 *arg1, M2C_UNK arg2) {
    s16 temp_v0;

    temp_v0 = func_80095978(arg1, &D_800FE488);
    if (arg1->unk_0A >= temp_v0) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
        func_80098928(arg0, arg1, arg2);
        return;
    }
    func_80095388(arg1, temp_v0);
}
