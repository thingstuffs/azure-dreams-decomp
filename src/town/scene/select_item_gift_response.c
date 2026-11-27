#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/shop.h"
#include "town/shop/object.h"

typedef struct Copy4 {
    u8 bytes[4];
} Copy4;

extern Copy4 town_map_gift_item_descriptor;
extern s32 town_map_gift_item_response;
extern s32 town_map_gift_unavailable_response;

/* Select the response and set flag 0xD80 when its prerequisite passes. */
s32 *select_item_gift_response(s32 unused_first_value, s32 unused_second_value, s32 unused_code) {
    if (get_script_flag_mask(Ftt_pad79) == 0) {
        if (count_free_item_slots() != 0) {
            set_script_flag_bit(Ftt_pad79);
            append_town_item(&town_map_gift_item_descriptor);
            return &town_map_gift_item_response;
        }
    }
    return &town_map_gift_unavailable_response;
}
