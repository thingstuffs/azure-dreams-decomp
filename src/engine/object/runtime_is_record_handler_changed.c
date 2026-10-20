#include "common.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"


extern s32 func_80038A00;

/* Returns whether the record's unk_9C differs from the address of func_80038A00. */
s32 runtime_is_record_handler_changed(Rec_D_80082A38 *record) {
    return record->unk_9C != (s32) &func_80038A00;
}
