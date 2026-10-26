#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/player/script_flags.h"

s32 process_checked_entry(void *object, s32 entryIndex);             /* extern */


/* Process flag 0xD52, conditionally select the object value, and forward the request. */
void process_flag_and_forward_request(Rec_func_800165F4_arg0 *object, s32 request_data) {
    clear_script_flag_bit(Ftt_pad33);
    if (check_progress_against_callback() != 0) {
        set_script_flag_bit(object->unk_18);
    }
    process_checked_entry(object, request_data);
}
