#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_item_entries.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"
#include "dungeon/data.h"
/* Applies eligible type-based adjustments before and after processing an entry. */
u8 *apply_type_based_entry_adjustments(void *entry_data, u8 *value) {
    DungeonItemEntry *entry = entry_data;
    u8 pre_type;
    s32 post_type;
    u8 *pre_adjustment, *post_adjustment, *result;
    if (!(dungeon_actor_ring_anchor->flags1C & 0x10)) {
        pre_type = entry->kind;
        pre_adjustment = item_type_text_prefixes[pre_type];
        if (pre_adjustment && (pre_type != 15 || entry->unk_00 < 14)) {
            value = expand_text_control_codes(pre_adjustment, value);
        }
    }
    result = copy_selected_text_without_terminator(entry, value);
    if (!(dungeon_actor_ring_anchor->flags1C & 0x10)) {
        post_type = entry->kind;
        post_adjustment = item_type_text_suffixes[post_type];
        if (post_adjustment) {
            if (post_type == 15 && entry->unk_00 >= 14) {
                return result;
            }
            result = expand_text_control_codes(post_adjustment, result);
        }
    }
    return result;
}
