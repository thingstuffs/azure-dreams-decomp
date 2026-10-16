#include "modules/dungeon_ovl_1829800.h"

void *dungeonInitializeAvailableObject(s16 initialValue) {
    S_800267F0_0 *object;

    D_8002715A = 0;
    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = (void *)dungeonInitializeChildrenOrShutdown;
        object->unk_46 = initialValue;
        func_8004DCE0(2);
        runtimeCallSelectedModeHandler();
        func_8004DD2C(&D_80027160);
    }
    return object;
}
