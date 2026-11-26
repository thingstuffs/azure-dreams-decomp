#include "script_symbols.h"
#include "town/scene.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/state_data.h"
#include "town/scene/event.h"
#include "town/scene/event_lookup_data.h"
#include "town/player/state.h"
#include "town/scene/flags.h"
#include "town/scene/position_entries.h"

/*
 * The two position entries carry packed addresses for their default data.
 *
 * Event 0x1c uses selector 1 and returns 0x8001a6bc.
 * Event 0x0b uses selector 0 and returns 0x8001a238.
 */
extern ScenePositionEntry D_800189DC[2];
extern u8 D_8001A3AE[];
extern u8 D_8001A495[];

/*
 * The action dispatcher passes its selected 28-byte row as context to
 * both helpers. The Sero event advances the current status counter when
 * its flag lookup misses. Event 0x1c overrides the first visit.
 */
void *lookup_event_data_with_overrides(TownObjectSet *entry, s32 unused,
                                      s32 event_id)
{
    void *event_data;
    ScenePositionEntry *event_table;

    event_table = D_800189DC;
    event_data = apply_entry_position(
        event_table,
        scene_event_lookup_context,
        entry,
        event_id);
    if (event_id == 0xB) {
        set_script_flag_bit(F_s34_sero_start);
        if (resolve_entry_flag(event_table, entry, 0xB) != 0) {
            return &D_8001A3AE[0];
        }
        ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state++;
        if (((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state >= 5U) {
            set_script_flag_bit(F_s34_sero_quickstart);
        }
        return event_data;
    }
    if (event_id == 0x1C) {
        if (get_script_flag_mask(F_sbs34_pad18) == 0) {
            set_script_flag_bit(F_sbs34_pad18);
            return &D_8001A495[0];
        }
    }
    return event_data;
}
