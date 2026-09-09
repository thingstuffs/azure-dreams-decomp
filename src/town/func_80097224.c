#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern M2C_UNK func_80094A60(s32 *, Rec_func_80094268_arg0 *, s32);


/* Call the handler when the record selects a nonzero entry. */
void func_80094984(s32 *entries, Rec_func_80094268_arg0 *record, s32 handler_param) {
    if (entries[record->unk_16] != 0) {
        func_80094A60(entries, record, handler_param);
    }
}
