#include "modules/town_town_windows.h"

/* Dispatches an object callback or switches the object to its alternate state. */
void townDispatchObjectOrSwitchAlternateState(func_800A075C_S_func_8009DEBC_0 *object, s32 source, s32 context) {
    u8 saved_state;

    if (townClassifyRecordByStateAndPosition(object, source) == 2) {
        func_80033D08(object);
        saved_state = object->unk_15;
        object->unk_15 = 0;
        ((func_800A075C_S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_00 = townResetObjectHandlerAndSavedByte;
        object->unk_AC = saved_state;
        return;
    }

    object->unk_50(object, object, source, context);
    if (!(((func_800A075C_S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_0E & 0x8000)) {
        townSetStateBytesFromFlags(func_8009706C(source), object);
        if (object->unk_4D == 0x13) {
            func_800478B8(context);
        }
    }
}
