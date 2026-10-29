#include "common.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene/position_entries.h"
#include "town/scene/entry_requests.h"
#include "town/scene/motion.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unk6;
} Position;


/* Applies the selected entry's position and returns its result. */
s32 apply_entry_position(ScenePositionEntry *entries, void *object, void *context, s32 selection)
{
    void *saved_object;
    s32 entry_index;
    Position *position;
    s32 selector;
    s32 table;

    saved_object = object;

    entry_index = find_entry_8_index_or_assert(entries, selection);
    selector = entries[entry_index].selector;
    table = *(s32 *)((u8 *)context + 0x14);
    position = (Position *)(selector * 8 + table);
    update_dependent_entry_ids(position->x, position->y, position->z);

    if (saved_object != 0 && all_entries_pass_check(saved_object) != 0) {
        set_script_flag_bit(*(s16 *)((u8 *)context + 0x18));
    }

    return entries[entry_index].result;
}
