#include "common.h"
#include "m2c_compat.h"

void func_800894A0(void) {
    (M2C_UNK (*)())0x80040190();
    if (*(s32 *)0x800814A0 & 0x8000) {
        (M2C_UNK (*)())0x800401FC();
    }
    *(s32 *)0x800814A0 = 0;
    if (*(u8 *)0x80080A86 == 0) {
        (M2C_UNK (*)())0x8004027C();
        if (!(*(u16 *)0x80013714 & 2)) {
            if (M2C_FIELD((void *)0x80083160, s32 *, 0x1DC) != 0) {
                (M2C_UNK (*)())0x8004D70C();
                (M2C_UNK (*)())0x800D13B8();
                if (!(M2C_FIELD(*(void **)0x800814A8, s32 *, 0x1C) & 0x10)) {
                    (M2C_UNK (*)())0x800CF8E4();
                }
            }
            goto block_7;
        }
    } else {
block_7:
        (M2C_UNK (*)())0x800897E4();
        (M2C_UNK (*)())0x80044B48();
        (M2C_UNK (*)())0x80089588();
    }
}
