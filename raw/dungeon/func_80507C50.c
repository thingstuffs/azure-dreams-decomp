#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001F354(s16, s32, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_8004E634(s16, u8 *);                   /* extern */
extern M2C_UNK D_8001F5B4;
extern M2C_UNK D_80077DE8;
extern M2C_UNK D_80077E00;
extern s16 D_8008146C;

void func_8001F450(void) {
    u8 sp10;
    M2C_UNK *var_a3;
    M2C_UNK var_s2;
    s16 var_s1;
    u8 *var_s0;
    u8 var_v0;

    var_a3 = NULL;
    if (*(s32 *)0x80012090 != 2) {
        var_s2 = 0;
        if (D_8008146C == 0x28) {
            var_a3 = &D_80077E00;
        }
    } else {
        var_s2 = 1;
    }
    if (var_a3 != NULL) {
        func_8001F354(0xAA, 0x78, 0, var_a3);
        return;
    }
    func_8001F354(0xAA, 0x78, var_s2, &D_80077DE8);
    var_s0 = &sp10;
    func_8004E634(D_8008146C, var_s0);
    var_s1 = 0xC8;
    if (sp11 == 0) {
        var_s1 = 0xDA;
    }
    if (sp10 != 0) {
        var_v0 = *var_s0;
        do {
            if (var_v0 != 0x20) {
                func_8001F354(var_s1, 0x780000 >> 0x10, var_s2, *((var_v0 * 4) + &D_8001F5B4));
            }
            var_s0 += 1;
            var_v0 = *var_s0;
            var_s1 += 0x12;
        } while (var_v0 != 0);
    }
}
