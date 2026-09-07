#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80099754();                      /* extern */
extern M2C_UNK D_80097F9C;

typedef struct S_80098B30_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80098B30_0;   /* arg0 in func_80098B30 */


void func_80098B30(S_80098B30_0 *arg0, Rec_D_800E3D7C *arg1) {
    arg0->unk_04 = &D_80097F9C;
    func_80099754(arg1);
    arg1->unk_14.as_s32 = 0xFFFC0000;
}
