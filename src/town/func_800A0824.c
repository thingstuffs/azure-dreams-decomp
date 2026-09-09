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
s32 func_8009D20C(void *, void *);                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009DEBC;

/* Reset the object handler and restore its saved byte unless the check returns two. */
void func_8009DF84(void *object, void *context) {
    if (func_8009D20C(object, context) != 2) {
        func_80033CD8(object, &D_80045340);
        ((S_8009DF84_0 *)((u8 *)object - 0x10))->unk_00 = &D_8009DEBC;
        ((S_8009DF84_0 *)((u8 *)object - 0x10))->unk_25 = (u8) ((S_8009DF84_0 *)((u8 *)object - 0x10))->unk_BC;
    }
}
