#include "common.h"
typedef struct { s16 x; s16 y; s16 z; s16 pad; } Vec3s;
extern u8 D_80528910[]; extern u16 D_80132AEA[];
extern void func_80526E4C(void *, void *, void *, void *);
extern s32 func_8006A3A4(s32); extern s32 func_8006A470(s32);
/* Draw three stacked rotating square outlines with complementary grayscale colors. */
void func_80528998(u8 *object)
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
        for (index = 3, origin = D_80132AEA; index >= 0; index--) {
            s32 angle_offset = index << 10;
            s32 x;
            s32 y;

            x = func_8006A3A4(*(s16 *)(object + 0x28) + angle_offset);
            corner[index].x = (x = (x >> 6) + origin[0]);
            y = func_8006A470(*(s16 *)(object + 0x28) + angle_offset);
            corner[index].y = (y = (y >> 6) + origin[2]);
            corner[index].z = origin[4] - 0xA0;
        }
    }
    {
        u16 *origin = D_80132AEA;
        center.x = origin[0];
        center.y = origin[2];
        center.z = origin[4] - 0x60;
    }
    index = ((s16)*(u16 *)(object + 0x2E) >> 1) + 0x80;
    if (index < 0)
        index = 0;
    else if (index >= 0x100)
        index = 0xFF;
    color[1] = index + (index << 8) + (index << 16);
    color[0] = 0x00FFFFFF - color[1];
    for (layer = 2; layer >= 0; layer--) {
        for (index = 3; index >= 0; index--) {
            edge[0] = corner[index];
            edge[1] = corner[(index + 1) & 3];
            func_80526E4C(D_80528910, edge, color, object);
        }
        for (index = 3; index >= 0; index--)
            corner[index].z += 0x20;
    }
}
