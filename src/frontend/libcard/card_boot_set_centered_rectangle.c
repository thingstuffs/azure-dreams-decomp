#include "common.h"
#include "engine/menu.h"
#include "frontend/libcard.h"

/* Apply a centered rectangle with the given width and height and return the target. */
u8 *card_boot_set_centered_rectangle(u8 *target, s32 width, s32 height) {
    RECT rect;

    rect.x = (s16) (-width / 2);
    rect.w = (s16) width;
    rect.y = (s16) (-height / 2);
    rect.h = (s16) height;
    init_packet_pair_and_gradient(target, &rect);
    return target;
}
