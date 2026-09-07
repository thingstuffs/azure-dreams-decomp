/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_808B94E0_1 {
    u8 pad_00[0x64];
    M2C_UNK (*unk_64)(M2C_UNK, M2C_UNK, M2C_UNK);
} S_808B94E0_1;   /* *(void **)(D_A0700000 + 0xB50) in func_808B94E0 */


typedef struct S_808B94E0_0 {
    u8 pad_00[0x6C];
    M2C_UNK (*unk_6C)(M2C_UNK);
} S_808B94E0_0;   /* *(s32 *)(D_A0700000 + 0xB50) in func_808B94E0 */


M2C_UNK func_807001B4();
M2C_UNK func_80700244();
s32 func_8070042C();
M2C_UNK func_80700488();
M2C_UNK func_807008D0();
extern u8 D_A0700000[];
extern u8 D_A0700120[];
extern u8 D_A0700134[];

s32 func_808B94E0(void) {
    s32 *held = (s32 *)(D_A0700000 + 0xB40);

    func_807001B4(*held);
    func_80700244(0);
    func_80700488();
    *(s32 *)(D_A0700000 + 0x9D4) = func_8070042C();
    ((S_808B94E0_1 *)(*(void **)(D_A0700000 + 0xB50)))->unk_64(
        (s32)D_A0700120, (s32)D_A0700134, 0xC9);
    ((S_808B94E0_0 *)(*(s32 *)(D_A0700000 + 0xB50)))->unk_6C(0);
    func_807001B4(*held);
    func_807008D0(*(s32 *)(D_A0700000 + 0x9D4), *(s32 *)(D_A0700000 + 0x9D8));
    return *(s32 *)(D_A0700000 + 0x9D4);
}
