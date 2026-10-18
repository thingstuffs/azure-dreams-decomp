#include "modules/dungeon_ovl_1829800.h"

void *initialize_available_object(s16 initialValue) {
    S_800267F0_0 *object;

    D_8002715A = 0;
    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = (void *)initialize_children_or_shutdown;
        object->unk_46 = initialValue;
        func_8004DCE0(2);
        runtime_call_selected_mode_handler();
        func_8004DD2C(&D_80027160);
    }
    return object;
}
