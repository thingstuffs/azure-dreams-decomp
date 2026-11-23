#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/data.h"

static inline const TownFlagDependency *flag_dependency_at(u32 address, s32 index)
{
    /* BYTES: Scaling the index before adding the image address preserves addu operand order. */
    return (const TownFlagDependency *)(index * sizeof(TownFlagDependency) + (unsigned long)address);
}

/* Apply each flag dependency, then clear its source flag. */
void process_town_records(u32 records_address, s32 record_count)
{
    s32 index;

    if (records_address == 0) {
        return;
    }
    for (index = 0; index < record_count; index++) {
        const TownFlagDependency *record = flag_dependency_at(records_address, index);

        clear_script_flag_bit(record->clear_flag);
        if (get_script_flag_mask(scene_dependency_ids[1]) == 0) {
            clear_script_flag_bit(record->target_flag);
        } else {
            /* BYTES: The gated query and final clear recompute the indexed address. */
            record = flag_dependency_at(records_address, index);
            if (get_script_flag_mask(record->source_flag) != 0) {
                set_script_flag_bit(record->target_flag);
            }
        }
        clear_script_flag_bit(flag_dependency_at(records_address, index)->source_flag);
    }
}
