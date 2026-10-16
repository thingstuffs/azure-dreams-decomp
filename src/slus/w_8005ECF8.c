#include "slus/sound_transfer_helpers.h"

/* Polls or waits for SPU transfer completion and latches the completion status. */
s32 pollDriverCompletionEvent(s32 wait_for_completion)
{
    s32 event_status;

    if (D_800794F4 == 1 || D_8007998C == 1) {
        return 1;
    }

    event_status = TestEvent(D_800794EC);
    if (wait_for_completion == 1) {
        if (event_status == 0) {
            while (TestEvent(D_800794EC) == 0) {
            }
        }
        event_status = 1;
    } else {
        if (event_status != 1) {
            return event_status;
        }
    }

    D_8007998C = event_status;
    return event_status;
}
