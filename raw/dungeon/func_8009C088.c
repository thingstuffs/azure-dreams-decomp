#include "common.h"

extern u8 D_800E3DB0[];
extern u8 D_800E3DD0[];
extern u8 D_800E3DE0[];

u8 *func_800A17E8(s16 arg0, s16 arg1) {
    register s16 var_a2 ASM_REG("$6");
    u8 *var_v1;
    s16 next;

    if (arg1 == 3) {
        var_v1 = D_800E3DD0;
        var_a2 = 4;
    } else if (arg1 == 2) {
        return D_800E3DE0;
    } else if (D_800E3DB0[0x11] == 0x38) {
        var_v1 = D_800E3DB0 + 0x18;
        var_a2 = 3;
    } else if (D_800E3DB0[9] == 0x31) {
        var_v1 = D_800E3DB0 + 0x10;
        var_a2 = 2;
    } else {
        var_v1 = D_800E3DB0;
        var_a2 = 0;
    }

    if (var_a2 < 6) {
        do {
            if ((arg1 == 1 || arg1 == 3) && var_v1[0] != arg1) {
                return 0;
            }
            if (var_v1[1] == arg0) {
                return var_v1;
            }
            next = var_a2 + 1;
            var_a2 = next;
            var_v1 += 8;
        } while (next < 6);
    }
    return 0;
}
