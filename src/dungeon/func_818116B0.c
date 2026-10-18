#include "modules/dungeon_ovl_1831370.h"

void apply_step_and_reset_after_five(s32 *step) {
    s32 step_value = *step << 10;

    *(s16 *) (*(s32 *) ((u8 *) step + 0x64) + 6) = step_value;
    *step += 1;
    if (*step >= 5) {
        *step = 0;
        *(void **) ((u8 *) step - 0x10) = (void *)forward_menu_object_to_selection_updater;
    }
    update_menu_selection_from_input((ovl_1831370_8181140C_MenuState *)step);
}
