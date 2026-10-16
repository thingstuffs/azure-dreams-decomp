#include "common.h"
#include "m2c_compat.h"

void func_800BD074(void) {
    if (*(u8 *)0x80082E6B == 0x11) {
        if (*(s32 *)0x80012090 == 0) {
            if (*(s16 *)0x8008146C == 0x28) {
                if ((s32 (*)(M2C_UNK, M2C_UNK))0x80033BC0(0xA2, 0x800E0000) == 0) {
                    if (*(s32 *)0x8001208C == 0) {
                        *(s32 *)0x8001208C = 1;
                        (M2C_UNK (*)(M2C_UNK, M2C_UNK))0x80040AA0(0x21, 0x800E0000);
                        *(s8 *)0x800DCF4E = 0;
                        return;
                    }
                    goto block_8;
                }
                goto block_7;
            }
            goto block_8;
        }
        goto block_7;
    }
block_7:
block_8:
    (M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK))0x8003E4FC(6, 0x800DF3D4, 0);
    (M2C_UNK (*)())0x8003F320();
}
