#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"
#include "town/shop/state.h"

void update_cd_queue_head_entry();                         /* extern */


/* Processes and clears both nonzero handles, returning whether either was set. */
s32 release_monster_status_request_handles(ShopFirstCallbackObject *owner) {
    s32 firstHandle;
    s32 secondHandle;
    s32 hadHandle;

    firstHandle = owner->read_handle;
    hadHandle = 0;
    if (firstHandle != 0) {
        update_cd_queue_head_entry(firstHandle);
        owner->read_handle = 0;
        hadHandle = 1;
    }
    secondHandle = owner->completion_handle;
    if (secondHandle != 0) {
        update_cd_queue_head_entry(secondHandle);
        owner->completion_handle = 0;
        hadHandle = 1;
    }
    return hadHandle;
}
