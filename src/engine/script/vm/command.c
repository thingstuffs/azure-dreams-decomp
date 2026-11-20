#include "engine/script/vm.h"

void copy_window_rect(RECT *dest, const MessageWindowImage *image) {
    dest->x = image->rect.x;
    dest->y = image->rect.y;
    dest->w = image->rect.w;
    dest->h = image->rect.h;
}
