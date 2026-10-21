#include "common.h"
#include "engine/menu.h"
#include "frontend/libcard.h"

/* Apply a centered rectangle with the given width and height and return the target. */
s32 card_boot_set_centered_rectangle(s32 target, s32 width, s32 height) {
    s16 rect[4];

    rect[0] = (s16) (-width / 2);
    rect[2] = (s16) width;
    rect[1] = (s16) (-height / 2);
    rect[3] = (s16) height;
    func_80049D80(target, rect);
    return target;
}
