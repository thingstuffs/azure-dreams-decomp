#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

void townHandleInsertInitializeTwoValuesStatusFlags();        /* extern */
void townConfigureTheSetModeN3();                         /* extern */
void townInitializeOptionalObjectState(); /* extern */
extern M2C_UNK D_800D0690;


typedef struct S_8009C7A8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009C7A8_1;   /* arg2 in townSelectObjectStateByMode */

/* Select a state value and update the record according to its mode flag. */
void townSelectObjectStateByMode(Rec_D_800CFCB4 *record, s32 context, S_8009C7A8_1 *state, s32 default_value,
    s32 alternate_value, s32 update_value) {
    if (record->unk_94 != 0) {
        state->unk_08 = alternate_value;
        townConfigureTheSetModeN3(record, context, update_value);
        townInitializeOptionalObjectState(record, context, state, 0);
        return;
    }
    state->unk_08 = default_value;
    townHandleInsertInitializeTwoValuesStatusFlags(record, context, update_value);
    {
        void *next_record;
        s32 next_context;
        void *next_state;
        s32 *shared_data;

        next_record = record;
        next_context = context;
        next_state = state;
        shared_data = &D_800D0690;
        townInitializeOptionalObjectState(next_record, next_context, next_state, shared_data);
    }
}
