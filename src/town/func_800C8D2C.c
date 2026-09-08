#include "common.h"

typedef s32 unk32;

typedef struct S_800C648C_0 {
    u8 pad_00[0x7C];
    s32 ** unk_7C;
    void ** unk_80;
} S_800C648C_0;   /* arg0 in func_800C648C */

typedef struct S_800C648C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C648C_1;   /* ((S_800C648C_0 *)arg0)->unk_80 in func_800C648C */



extern unk32 D_800D58B8;

/* Check whether both actor data references match D_800D58B8. */
s32 func_800C648C(S_800C648C_0 *actor) {
    s32 data_addr;

    data_addr = *actor->unk_7C;
    if ((data_addr == (s32)&D_800D58B8) &&
        (((S_800C648C_1 *)(actor->unk_80))->unk_04 == data_addr)) {
        return 1;
    }
    return 0;
}
