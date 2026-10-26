#include "common.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"
#include "engine/object.h"
#include "engine/script/vm.h"

/* Returns whether the record handler differs from noop_runtime_record_idle. */
s32 runtime_is_record_handler_changed(Rec_D_80082A38 *record) {
    return record->unk_9C != (s32) &noop_runtime_record_idle;
}
