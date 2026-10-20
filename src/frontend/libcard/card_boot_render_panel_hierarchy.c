#include "common.h"

s16 draw_tinted_node_sprites_scratch(s32, s32, s32);                                /* extern */

/* Forward three values to draw_tinted_node_sprites_scratch and return its result. */
s16 card_boot_render_panel_hierarchy(s32 first_value, s32 second_value, s32 third_value) {
    return draw_tinted_node_sprites_scratch(first_value, second_value, third_value);
}
