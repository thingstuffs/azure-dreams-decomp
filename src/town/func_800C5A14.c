#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
s32 func_8009CFE0();                                /* extern */
M2C_UNK func_800C30A4();                      /* extern */
M2C_UNK func_800C3200();                            /* extern */
M2C_UNK func_800C321C();    /* extern */
extern M2C_UNK D_800C3960;

typedef struct S_800C3174_0 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x44];
    s8 * unk_98;
} S_800C3174_0;   /* arg0 in func_800C3174 */

void func_800C3174(S_800C3174_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_v0;
    s8 *temp_v0_2;

    temp_v0 = func_8009CFE0();
    if (temp_v0 != 0) {
        if ((temp_v0 != 2) || (arg0->unk_50 != &D_800C3960)) {
            func_8008F134(arg0);
            temp_v0_2 = arg0->unk_98;
            if (temp_v0_2 != NULL) {
                *temp_v0_2 = 0;
            }
            func_80033D08(arg0);
            func_800C30A4(arg0);
            return;
        }
        /* Duplicate return node #8. Try simplifying control flow for better match */
        func_800C321C(arg0, arg1, arg2);
        return;
    }
    func_800C321C(arg0, arg1, arg2);
}
