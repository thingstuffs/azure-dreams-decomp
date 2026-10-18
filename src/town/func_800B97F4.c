#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

void update_cd_queue_head_entry();                         /* extern */


/* Processes and clears both nonzero handles, returning whether either was set. */
s32 release_monster_status_request_handles(Rec_func_800B683C_arg0 *owner) {
    s32 firstHandle;
    s32 secondHandle;
    s32 hadHandle;

    firstHandle = owner->unk_D0;
    hadHandle = 0;
    if (firstHandle != 0) {
        update_cd_queue_head_entry(firstHandle);
        owner->unk_D0 = 0;
        hadHandle = 1;
    }
    secondHandle = owner->unk_D4;
    if (secondHandle != 0) {
        update_cd_queue_head_entry(secondHandle);
        owner->unk_D4 = 0;
        hadHandle = 1;
    }
    return hadHandle;
}
