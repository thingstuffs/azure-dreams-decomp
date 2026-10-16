#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern void townCallTheSelectedNonzeroTableCallee80094A38(s32 *, Rec_func_80094268_arg0 *);


/* Call the handler when the record selects a nonzero entry. */
void townCallTheHandlerSelectsNonzeroEntry(s32 *entries, Rec_func_80094268_arg0 *record, void *ptr2) {
    if (entries[record->unk_16] != 0) {
        townCallTheSelectedNonzeroTableCallee80094A38(entries, record);
    }
}
