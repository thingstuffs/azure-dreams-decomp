#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"

extern s32 dev_card_paths[2];


/* Configures the target using the active state and selected table entry. */
void card_dev_build_slot_path(s32 target, s32 entry_index) {
    s32 *active_value;

    active_value = &dev_card_paths[0];
    if (card_selected_channel != 0) {
        active_value = &dev_card_paths[0] + 1;
    }
    func_8007BF80(target, *active_value);
    func_8007BF50(target, &D_80408AA8[0]);
    func_8007BF50(target, dev_card_slot_names[entry_index]);
}
