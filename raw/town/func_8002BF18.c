#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4(M2C_UNK);                         /* extern */
M2C_UNK func_800C2E84(void *, M2C_UNK, s32);        /* extern */
extern M2C_UNK D_800C9384;

void func_800C9678(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_v1;
    s32 var_s2;

    var_s2 = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
loop_1:
    temp_v1 = func_800374F4(4) & 0xFFFF;
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg1, s16 *, 2) < (M2C_FIELD(arg0, s16 *, 0x84) + M2C_FIELD(arg0, s16 *, 0x8C))) {
            M2C_FIELD(arg0, s16 *, 0x72) = 0x400;
        } else {
block_12:
            var_s2 += 1;
            if (var_s2 < 0x10) {
                goto loop_1;
            }
        }
        break;
    case 1:
        if (M2C_FIELD(arg1, s16 *, 6) < (M2C_FIELD(arg0, s16 *, 0x86) + M2C_FIELD(arg0, s16 *, 0x8E))) {
            M2C_FIELD(arg0, s16 *, 0x72) = 0;
        } else {
            goto block_12;
        }
        break;
    case 2:
        if ((M2C_FIELD(arg0, s16 *, 0x84) - M2C_FIELD(arg0, s16 *, 0x8C)) < M2C_FIELD(arg1, s16 *, 2)) {
            M2C_FIELD(arg0, s16 *, 0x72) = 0xC00;
        } else {
            goto block_12;
        }
        break;
    default:
        if ((M2C_FIELD(arg0, s16 *, 0x86) - M2C_FIELD(arg0, s16 *, 0x8E)) < M2C_FIELD(arg1, s16 *, 6)) {
            M2C_FIELD(arg0, s16 *, 0x72) = 0x800;
        } else {
            goto block_12;
        }
        break;
    }
    func_800C2E84(arg0, arg2, M2C_FIELD(M2C_FIELD(arg0, void **, 0x7C), s32 *, 4));
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800C9384;
}
