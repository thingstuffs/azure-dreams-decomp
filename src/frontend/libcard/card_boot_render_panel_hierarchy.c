#include "common.h"
#include "engine/graphics.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* Forward three values to draw_tinted_node_sprites_scratch and return its result. */
s16 card_boot_render_panel_hierarchy(s32 first_value, s32 second_value, CardDisplayNode *third_value) {
    return draw_tinted_node_sprites_scratch(first_value, second_value, third_value);
}
