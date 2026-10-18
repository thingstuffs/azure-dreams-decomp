#include "modules/town_town_windows.h"

/* Builds four corner vertices from a rectangle with position offsets. */
void rectangle_to_four_corners(func_800A0284_S_8009D9E4_0 *rectangle, func_800A0284_S_8009D9E4_1 *vertices) {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;

    left = rectangle->unk_00 + rectangle->unk_04;
    vertices->unk_08 = left;
    vertices->unk_00 = left;
    right = rectangle->unk_08 + (rectangle->unk_00 + rectangle->unk_04);
    vertices->unk_0C = right;
    vertices->unk_04 = right;
    top = rectangle->unk_02 + rectangle->unk_06;
    vertices->unk_06 = top;
    vertices->unk_02 = top;
    bottom = rectangle->unk_0A + (rectangle->unk_02 + rectangle->unk_06);
    vertices->unk_0E = bottom;
    vertices->unk_0A = bottom;
}
