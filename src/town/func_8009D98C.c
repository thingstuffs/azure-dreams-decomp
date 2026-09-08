#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8009AF74;

typedef struct S_8009B0EC_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8009B0EC_0;   /* arg0 in func_8009B0EC */

/* Decrement the countdown, then reset it and switch handlers when it expires. */
void func_8009B0EC(S_8009B0EC_0 *object) {
    u16 countdown;

    countdown = object->unk_0A - 1;
    object->unk_0A = countdown;
    if ((countdown << 0x10) <= 0) {
        object->unk_0A = 3U;
        object->unk_04 = &D_8009AF74;
    }
}
