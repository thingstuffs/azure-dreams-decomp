#include "script_symbols.h"
#include "town/scene.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"

/* Choice predicate: flag the current entry when Ft_s07_mia_bikou_end is set, then apply the selected entry's values. */
s32 apply_entry_mia_bikou_end(SquareSceneEntry *entry, s32 entry_index) {
    if (get_script_flag_mask(Ft_s07_mia_bikou_end) != 0) {
        set_current_entry_script_flag();
    }
    return apply_selected_entry_values(entry, entry_index);
}
