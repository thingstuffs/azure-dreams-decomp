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

/* Initializes the record and its associated resources. */
void func_800BC840(void *record, M2C_UNK init_context, M2C_UNK resource_target) {
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_00 = &D_800BC764;
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_60 = 0;
    func_8004491C(record - 0x20, &D_80045340);
    ((S_800BC840_0 *)((u8 *)record - 0x10))->unk_58 = (s32) D_800D20E4;
    func_8003DB94(resource_target, &D_800F15E4, 0);
    func_8008F074(record, init_context, &D_800D20CC);
}
