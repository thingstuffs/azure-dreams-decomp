#include "common.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene/position_entries.h"
#include "town/scene/entry_requests.h"
#include "town/scene/motion.h"
#include "town/scene.h"

/* Applies the selected entry's position and returns its result. */
s32 apply_entry_position(ScenePositionEntry *entries, void *object, TownObjectSet *context, s32 selection)
{
    void *saved_object;
    s32 entry_index;
    const TownFlagDependency *position;
    s32 selector;
    TownFlagDependency *table;

    saved_object = object;

    entry_index = find_eight_byte_entry_or_assert(entries, selection);
    selector = entries[entry_index].selector;
    table = context->flag_dependencies;
    /* BYTES: Keep the dependency base lw before the selector sll. */
    position = (const TownFlagDependency *)(selector * 8 + (unsigned long)table);
    update_dependent_entry_ids(position->source_flag, position->clear_flag, position->target_flag);

    if (saved_object != 0 && all_entries_pass_check(saved_object) != 0) {
        set_script_flag_bit(context->entry_flag);
    }

    return entries[entry_index].result;
}
