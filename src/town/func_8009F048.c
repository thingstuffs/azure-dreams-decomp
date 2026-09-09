#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

M2C_UNK func_8008F01C();        /* extern */
M2C_UNK func_8008F104();                         /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0690;


typedef struct S_8009C7A8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009C7A8_1;   /* arg2 in func_8009C7A8 */

/* Select a state value and update the record according to its mode flag. */
void func_8009C7A8(Rec_D_800CFCB4 *record, M2C_UNK context, S_8009C7A8_1 *state, s32 default_value, s32 alternate_value, s32 update_value) {
    if (record->unk_94 != 0) {
        state->unk_08 = alternate_value;
        func_8008F104(record, context, update_value);
        func_8009B218(record, context, state, 0);
        return;
    }
    state->unk_08 = default_value;
    func_8008F01C(record, context, update_value);
    {
        void *next_record;
        M2C_UNK next_context;
        void *next_state;
        M2C_UNK *shared_data;

        next_record = record;
        next_context = context;
        next_state = state;
        shared_data = &D_800D0690;
        func_8009B218(next_record, next_context, next_state, shared_data);
    }
}
