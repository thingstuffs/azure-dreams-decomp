#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vec3s;

extern u8 D_8002241C[];
extern u8 D_80083780[];

extern void func_80020948(void *, void *, void *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

/* Draws three depth layers of a rotating four-corner effect with complementary grayscale colors. */
void func_80022494(u8 *effect)
{
    Vec3s edge[2];
    Vec3s corner[4];
    Vec3s center;
    s32 color[2];
    s32 index;
    s32 layer;

    color[0] = 0x00808080;
    color[1] = 0x00FFFFFF;

    {
        u16 *origin;

        for (index = 3, origin = (u16 *)D_80083780; index >= 0; index--) {
            s32 angle_offset = index << 10;

            corner[index].x = origin[1] + (func_800644B8(*(s16 *)(effect + 0x28) + angle_offset) >> 6);
            corner[index].y = origin[3] + (func_80064584(*(s16 *)(effect + 0x28) + angle_offset) >> 6);
            corner[index].z = origin[5] - 0xA0;
        }
    }

    {
        u16 *origin = (u16 *)D_80083780;

        center.x = origin[1];
        center.y = origin[3];
        center.z = origin[5] - 0x60;
    }

    index = ((s16)*(u16 *)(effect + 0x2E) >> 1) + 0x80;
    if (index < 0) {
        index = 0;
    } else if (index >= 0x100) {
        index = 0xFF;
    }

    color[1] = index + (index << 8) + (index << 16);
    color[0] = 0x00FFFFFF - color[1];

    for (layer = 2; layer >= 0; layer--) {
        for (index = 3; index >= 0; index--) {
            edge[0] = edge[index + 2];
            edge[1] = edge[((index + 1) & 3) + 2];
            func_80020948(D_8002241C, edge, color, effect);
        }

        for (index = 3; index >= 0; index--) {
            corner[index].z += 0x20;
        }
    }
}
