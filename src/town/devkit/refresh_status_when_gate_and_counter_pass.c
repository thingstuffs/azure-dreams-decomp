#include "common.h"
#include "town/devkit/stage_dispatch.h"

typedef struct S_808B2F58_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_808B2F58_0;   /* *(void **)0xA0700F5C in func_808B2F58 */

typedef struct S_808B2F58_1 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2F58_1;   /* status in func_808B2F58 */


extern s32 func_8070021C();
extern s32 forward_indexed_table_value();
extern s32 func_807002D4();
extern s32 dispatch_first_failed_entry();

/* When the gate and the counter both pass, refresh the status byte and return the stage handler's result. */
s32 dispatch_scene_stage_if_counter_positive(s32 fallback_result)
{
    S_808B2F58_1 *status;

    if ((func_8070021C(1) != 0) &&
        (*((S_808B2F58_0 *)(*(void **)0xA0700F5C))->unk_08 > 0)) {
        forward_indexed_table_value(1);
        status = *(void **)0xA0700F40;
        status->unk_0E = status->unk_0E;
        return dispatch_first_failed_entry();
    }
    func_807002D4(1);
    return fallback_result;
}
