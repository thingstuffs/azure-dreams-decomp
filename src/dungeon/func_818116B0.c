#include "modules/dungeon_ovl_1831370.h"

void dungeonApplyStepAndResetAfterFive(s32 *step) {
    s32 step_value = *step << 10;

    *(s16 *) (*(s32 *) ((u8 *) step + 0x64) + 6) = step_value;
    *step += 1;
    if (*step >= 5) {
        *step = 0;
        *(void **) ((u8 *) step - 0x10) = (void *)func_80026690;
    }
    dungeonUpdateMenuSelectionFromInput((ovl_1831370_8181140C_MenuState *)step);
}
