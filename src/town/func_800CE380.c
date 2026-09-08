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

/* Initializes record state using its stored table index and setup routines. */
void func_800CBAE0(void *record_data, M2C_UNK context, Rec_D_80082E80 *state) {
    u8 table_index;

    table_index = ((S_800CBAE0_0 *)((u8 *)record_data - 0x10))->unk_A6;
    ((S_800CBAE0_0 *)((u8 *)record_data - 0x10))->unk_70 = (s32) table_index;
    state->unk_08 = (s32) *(table_index + &D_800D68B0);
    func_8008F104(record_data, context, &D_800D6A58);
    func_8009B218(record_data, context, state, 0);
    ((S_800CBAE0_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800CBAAC;
}
