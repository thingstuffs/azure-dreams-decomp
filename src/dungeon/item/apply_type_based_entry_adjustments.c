#include "common.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern u8 *expand_text_control_codes();
extern s32 copy_selected_text_without_terminator();
extern s32 item_type_text_prefixes[];
extern s32 item_type_text_suffixes[];
/* Applies eligible type-based adjustments before and after processing an entry. */
s32 apply_type_based_entry_adjustments(void *entry, s32 value) {
    u8 pre_type;
    s32 post_type, pre_adjustment, post_adjustment, result;
    if (!(F(((u8 *)dungeon_actor_ring_anchor), s32, 0x1C) & 0x10)) {
        pre_type = F(entry, u8, 1);
        pre_adjustment = item_type_text_prefixes[pre_type];
        if (pre_adjustment && (pre_type != 15 || F(entry, u8, 0) < 14)) {
            value = expand_text_control_codes(pre_adjustment, value);
        }
    }
    result = copy_selected_text_without_terminator(entry, value);
    if (!(F(((u8 *)dungeon_actor_ring_anchor), s32, 0x1C) & 0x10)) {
        post_type = F(entry, u8, 1);
        post_adjustment = item_type_text_suffixes[post_type];
        if (post_adjustment) {
            if (post_type == 15 && F(entry, u8, 0) >= 14) {
                return result;
            }
            result = expand_text_control_codes(post_adjustment, result);
        }
    }
    return result;
}
