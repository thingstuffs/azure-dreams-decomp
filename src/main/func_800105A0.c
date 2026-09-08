#include "common.h"

extern void func_80049D80(s32 arg0, s16 *arr);

/* Apply a centered rectangle with the given width and height and return the target. */
s32 func_800235A0(s32 target, s32 width, s32 height) {
    s16 rect[4];

    rect[0] = (s16) (-width / 2);
    rect[2] = (s16) width;
    rect[1] = (s16) (-height / 2);
    rect[3] = (s16) height;
    func_80049D80(target, rect);
    return target;
}
