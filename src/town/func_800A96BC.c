#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009CD18_arg1.h"

typedef struct S_800A6E1C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    M2C_UNK * unk_60;
} S_800A6E1C_0;   /* arg0 in func_800A6E1C; pointer addresses record offset 0x10 */



M2C_UNK func_8008F104();  /* extern */
M2C_UNK func_8009CD18();             /* extern */
extern M2C_UNK D_800A6CF0;
extern M2C_UNK D_800A6EA4;
extern M2C_UNK D_800D0DC0;

/* Initializes object callbacks and state, then sets unit scale. */
void func_800A6E1C(void *object, M2C_UNK init_param, Rec_func_8009CD18_arg1 *transform) {
    ((S_800A6E1C_0 *)((u8 *)object - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A6E1C_0 *)((u8 *)object - 0x10))->unk_60 = &D_800A6EA4;
    func_8009CD18(object, transform, 0xA);
    func_8008F104(object, init_param, &D_800D0DC0);
    transform->unk_20 = 0x1000;
    transform->unk_1E = 0x1000;
    transform->unk_1C = 0x1000;
    transform->unk_16 = 0;
}
