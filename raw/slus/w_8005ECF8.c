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

/* summary: Waits for/checks the SPU transfer-complete event on channel
 * D_800794EC[0] and reports/latches completion status into D_8007998C[0].
 * If either the channel is already marked busy (D_800794F4[0] == 1) or a
 * completion was already latched (D_8007998C[0] == 1), returns 1
 * immediately without touching D_8007998C. Otherwise polls TestEvent()
 * once; if called with a1==1 it blocks (busy-waits) until the event fires
 * and always reports 1, latching that into D_8007998C. If called with
 * a1!=1 it is non-blocking: unless the single poll already returned
 * exactly 1 it returns that raw poll result without latching D_8007998C. */
s32 func_8005ECF8(s32 a1)
{
    s32 result;

    if (D_800794F4[0] == 1 || D_8007998C[0] == 1) {
        return 1;
    }

    result = TestEvent(D_800794EC[0]);
    if (a1 == 1) {
        if (result == 0) {
            while (TestEvent(D_800794EC[0]) == 0) {
            }
        }
        result = 1;
    } else {
        if (result != 1) {
            return result;
        }
    }

    D_8007998C[0] = result;
    return result;
}
