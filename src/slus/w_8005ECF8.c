#include "common.h"

/* D_800794F4: SPU-transfer channel-busy scalar (established elsewhere as an
 * array of 3 to force hi/lo addressing); only element 0 is read here. */
extern s32 D_800794F4[3];

/* D_800794EC: SPU-transfer-target channel value; established convention in
 * src/w_8005E7E0.c as extern s32 D_800794EC[3], element 0 is the value
 * passed to the event-wait BIOS calls. */
extern s32 D_800794EC[3];

/* D_8007998C: pending "queue swap"-style flag/value; established in
 * src/w_8005E7E0.c as extern volatile s32 D_8007998C[3] there (that TU
 * needs volatile to defeat address-CSE across a busy-flag save/restore);
 * this function only touches it directly so a plain (non-volatile)
 * declaration is used to get the natural %hi/%lo fused load/store. */
extern s32 D_8007998C[3];

extern s32 TestEvent(s32 event);

/* Polls or waits for SPU transfer completion and latches the completion status. */
s32 func_8005ECF8(s32 wait_for_completion)
{
    s32 event_status;

    if (D_800794F4[0] == 1 || D_8007998C[0] == 1) {
        return 1;
    }

    event_status = TestEvent(D_800794EC[0]);
    if (wait_for_completion == 1) {
        if (event_status == 0) {
            while (TestEvent(D_800794EC[0]) == 0) {
            }
        }
        event_status = 1;
    } else {
        if (event_status != 1) {
            return event_status;
        }
    }

    D_8007998C[0] = event_status;
    return event_status;
}
