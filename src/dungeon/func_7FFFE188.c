#include "common.h"
#include "m2c_compat.h"

__asm__(".set D_80080000, 0x80080000");

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80080000[];
M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_8009C1B4(); /* extern */

typedef struct S_7FFFE188_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_7FFFE188_0;   /* arg2 in func_7FFFE188 */

typedef struct S_7FFFE188_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_7FFFE188_1;   /* arg0 in func_7FFFE188 */

void func_7FFFE188(S_7FFFE188_1 *arg0, M2C_UNK arg1, S_7FFFE188_0 *arg2, M2C_UNK arg3) {
    s32 *base;
    u16 temp_v0;

    base = D_80080000 + 0xDE0;
    arg2->unk_0C = (s32) ((s32) (base[0] - arg2->unk_00) / 2);
    arg2->unk_10 = (s32) ((s32) (base[1] - arg2->unk_04) / 2);
    func_8009539C(arg2);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_8009C1B4(arg0, arg1, arg2, arg3);
    }
}
