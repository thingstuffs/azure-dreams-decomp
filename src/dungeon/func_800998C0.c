#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009EEAC();                            /* extern */
M2C_UNK func_8009F3D4(); /* extern */
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

typedef struct S_8009F020_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009F020_0;   /* var_s0 in func_8009F020 */

typedef struct S_8009F020_1 {
    u8 unk_00;
    u8 unk_01;
} S_8009F020_1;   /* var_s1 in func_8009F020 */

void func_8009F020(void) {
    u8 *var_s0;
    u8 *var_s1;
    s32 var_s2;

    func_8009EEAC();
    var_s2 = 0;
    var_s1 = D_800E36C8;
    var_s0 = D_800E3548;
    do {
        if ((((S_8009F020_0 *)var_s0)->unk_01 != 0) && (((S_8009F020_0 *)var_s0)->unk_00 != 0)) {
            func_8009F3D4(((S_8009F020_1 *)var_s1)->unk_00, ((S_8009F020_1 *)var_s1)->unk_01, 0x802020, 2, var_s2);
        }
        var_s1 += 0xC;
        var_s2 += 1;
        var_s0 += 4;
    } while (var_s2 < 0x40);
}
