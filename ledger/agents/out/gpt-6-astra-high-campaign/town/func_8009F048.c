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
        ASM_KEEP(next_record);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        next_context = context;
        ASM_KEEP(next_context);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        next_state = state;
        ASM_KEEP(next_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        shared_data = &D_800D0690;
        func_8009B218(next_record, next_context, next_state, shared_data);
    }
}
