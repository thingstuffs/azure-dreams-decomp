#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"

/* In town/image_49e800, 0x80018E48 holds the eight-byte ScenePositionEntry records
 * with IDs 1, 12 and 15 passed to lookup_entry_value_and_set_flag. In town/image_437800,
 * set_global_entry_pair stores the second s32 of the pair there and forward_stored_pair reads it. */
extern ScenePositionEntry scene_operation_5be_entries[];

/* Clear the scene flag and apply the matching entry. */
void apply_scene_operation_5_be(TownObjectSet *context, s32 unused, s32 lookup_key) {
    clear_script_flag_bit(F_sbs11_pad27);
    lookup_entry_value_and_set_flag(scene_operation_5be_entries, context, lookup_key);
}
