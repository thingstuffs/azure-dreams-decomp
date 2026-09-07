#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800CBAE0_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6C];
    s32 unk_70;
    u8 pad_74[0x32];
    u8 unk_A6;
} S_800CBAE0_0;   /* arg0 in func_800CBAE0; pointer addresses record offset 0x10 */



M2C_UNK func_8008F104();                   /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800CBAAC;
extern M2C_UNK D_800D68B0;
extern M2C_UNK D_800D6A58;

void func_800CBAE0(void *arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2) {
    u8 temp_v1;

    temp_v1 = ((S_800CBAE0_0 *)((u8 *)arg0 - 0x10))->unk_A6;
    ((S_800CBAE0_0 *)((u8 *)arg0 - 0x10))->unk_70 = (s32) temp_v1;
    arg2->unk_08 = (s32) *(temp_v1 + &D_800D68B0);
    func_8008F104(arg0, arg1, &D_800D6A58);
    func_8009B218(arg0, arg1, arg2, 0);
    ((S_800CBAE0_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800CBAAC;
}
