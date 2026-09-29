#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern void func_80017BA0(s32, s32);

/* Call func_80017BA0 when the current entry byte is at least two, then clear it and return success. */
s32 func_804B7AC0(s32 first_input, s32 second_input)
{
    Rec_D_80016000 *state_before;
    Rec_D_80016000 *state_after;

    state_before = D_80016000;
    if (((u8 *)state_before->unk_40)[state_before->unk_08 * 8] < 2U) {
        return 0;
    }
    func_80017BA0(first_input, second_input);
    state_after = D_80016000;
    ((u8 *)state_after->unk_40)[state_after->unk_08 * 8] = 0;
    return 1;
}
