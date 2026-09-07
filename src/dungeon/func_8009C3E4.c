#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A1B44_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800A1B44_0;   /* D_800E3D7C in func_800A1B44 */

typedef struct S_800A1B44_1 {
    s32 unk_00;
    u8 pad_04[0x6C];
    s32 unk_70;
} S_800A1B44_1;   /* var_s0 in func_800A1B44; pointer addresses record offset 0x14 */


M2C_UNK func_800A19E4(); /* extern */
extern S_800A1B44_0 *D_800E3D7C;

void func_800A1B44(s16 arg0, s16 arg1) {
    void *var_s0;

    var_s0 = (void *) (D_800E3D7C->unk_5C + 0x20);
    if (var_s0 != D_800E3D7C) {
        do {
            func_800A19E4(((S_800A1B44_1 *)((u8 *)var_s0 - 0x14))->unk_00, var_s0, arg0, arg1, (void *) ((s32) var_s0 + 0x9C));
            var_s0 = (void *) (((S_800A1B44_1 *)((u8 *)var_s0 - 0x14))->unk_70 + 0x20);
        } while (var_s0 != D_800E3D7C);
    }
}
