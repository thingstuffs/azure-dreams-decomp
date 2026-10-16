#include "modules/town_town_windows.h"

/* Reset the object handler and restore its saved byte unless the check returns two. */
void townResetObjectHandlerAndSavedByte(void *object, void *context) {
    if (townClassifyRecordByStateAndPosition(object, context) != 2) {
        func_80033CD8(object, func_80045340);
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_00 = &townDispatchObjectOrSwitchAlternateState;
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_25 = (u8) ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_BC;
    }
}
