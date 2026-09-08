#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009CD18_arg1.h"

typedef struct S_800A6DA0_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    s32 unk_60;
} S_800A6DA0_0;   /* arg0 in func_800A6DA0; pointer addresses record offset 0x10 */



M2C_UNK func_8008F104();  /* extern */
M2C_UNK func_8009CD18();             /* extern */
extern M2C_UNK D_800A6CF0;
extern M2C_UNK D_800D0DA8;

/* Initializes the object and sets its transform scale to 0xC00 on all axes. */
void func_800A6DA0(void *object, M2C_UNK context, Rec_func_8009CD18_arg1 *transform) {
    ((S_800A6DA0_0 *)((u8 *)object - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A6DA0_0 *)((u8 *)object - 0x10))->unk_60 = 0;
    func_8009CD18(object, transform, 0x48);
    func_8008F104(object, context, &D_800D0DA8);
    transform->unk_20 = 0xC00;
    transform->unk_1E = 0xC00;
    transform->unk_1C = 0xC00;
}
