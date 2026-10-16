#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_A07008AC();                            /* extern */
extern M2C_UNK D_A0700184;
extern M2C_UNK D_A07001AC;
extern M2C_UNK D_A0700B28;
extern s32 D_A0700B30;
extern void *D_A0700B44;
extern s32 D_A0700B4C;
extern void *D_A0700B50;

void func_A07008D0(s32 arg0) {
    u8 *var_a0;
    void *temp_a0;

    if (D_A0700B30 != 0) {
        M2C_FIELD(D_A0700B50, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x64)(&D_A0700184, &D_A07001AC, 0x59);
        M2C_FIELD(D_A0700B50, M2C_UNK (**)(M2C_UNK), 0x70)(1);
    }
    D_A0700B30 = 1;
    func_A07008AC();
    M2C_FIELD(D_A0700B44, void **, 0x10) = (void *) *(&D_A0700B28 + (arg0 * 4));
    temp_a0 = M2C_FIELD(D_A0700B44, void **, 0x10);
    if (M2C_FIELD(temp_a0, u8 *, 1) != 0x80) {
        var_a0 = temp_a0 + 1;
        do {
            M2C_FIELD(var_a0, s32 *, 0xB) = (s32) *((M2C_FIELD(var_a0, s32 *, 0xB) * 4) + D_A0700B4C);
            var_a0 += 0x14;
        } while (*var_a0 != 0x80);
    }
}
