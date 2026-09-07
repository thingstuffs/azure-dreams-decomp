#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009DF84_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x21];
    u8 unk_25;
    u8 pad_26[0x96];
    u8 unk_BC;
} S_8009DF84_0;   /* arg0 in func_8009DF84; pointer addresses record offset 0x10 */


M2C_UNK func_80033CD8();           /* extern */
s32 func_8009D20C();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009DEBC;

void func_8009DF84(void *arg0) {
    if (func_8009D20C() != 2) {
        func_80033CD8(arg0, &D_80045340);
        ((S_8009DF84_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_8009DEBC;
        ((S_8009DF84_0 *)((u8 *)arg0 - 0x10))->unk_25 = (u8) ((S_8009DF84_0 *)((u8 *)arg0 - 0x10))->unk_BC;
    }
}
