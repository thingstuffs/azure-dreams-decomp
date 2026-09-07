#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BC840_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x54];
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
} S_800BC840_0;   /* arg0 in func_800BC840; pointer addresses record offset 0x10 */


M2C_UNK func_8003DB94(); /* extern */
M2C_UNK func_8004491C();              /* extern */
M2C_UNK func_8008F074();  /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800BC764;
extern M2C_UNK D_800D20CC;
extern s32 D_800D20E4;
extern M2C_UNK D_800F15E4;

void func_800BC840(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    ((S_800BC840_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800BC764;
    ((S_800BC840_0 *)((u8 *)arg0 - 0x10))->unk_60 = 0;
    func_8004491C(arg0 - 0x20, &D_80045340);
    ((S_800BC840_0 *)((u8 *)arg0 - 0x10))->unk_58 = (s32) D_800D20E4;
    func_8003DB94(arg2, &D_800F15E4, 0);
    func_8008F074(arg0, arg1, &D_800D20CC);
}
