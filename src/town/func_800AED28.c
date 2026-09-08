#include "common.h"

extern s8 D_800D1548[0x1549];

/* Set texture coordinates, page, and palette for a 32-by-32 quad. */
void func_800AC488(s16 texture_page, s16 palette, s8 texture_u, s8 texture_v) {
    s8 right_u;
    s8 bottom_v;

    D_800D1548[8] = texture_u;
    D_800D1548[0] = texture_u;
    right_u = texture_u + 0x1F;
    D_800D1548[5] = texture_v;
    D_800D1548[1] = texture_v;
    bottom_v = texture_v + 0x1F;
    D_800D1548[0xA] = right_u;
    D_800D1548[4] = right_u;
    D_800D1548[0xB] = bottom_v;
    D_800D1548[9] = bottom_v;
    *(s16 *)&D_800D1548[6] = texture_page;
    *(s16 *)&D_800D1548[2] = palette;
}
