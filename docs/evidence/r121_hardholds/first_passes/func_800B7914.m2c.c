s32 func_80033BC0(?, ?);                            /* extern */
? func_8003E4FC(?, s32, ?);                         /* extern */
? func_8003F320();                                  /* extern */
? func_80040AA0(?, ?);                              /* extern */

void func_800BD074(void) {
    if (*(u8 *)0x80082E6B == 0x11) {
        if (*(s32 *)0x80012090 == 0) {
            if (*(s16 *)0x8008146C == 0x28) {
                if (func_80033BC0(0xA2, 0x800E0000) == 0) {
                    if (*(s32 *)0x8001208C == 0) {
                        *(s32 *)0x8001208C = 1;
                        func_80040AA0(0x21, 0x800E0000);
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
    func_8003E4FC(6, 0x800DF3D4, 0);
    func_8003F320();
}
