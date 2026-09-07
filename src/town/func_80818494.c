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

void func_80022494(u8 *arg0)
{
    Vec3s edge[2];
    Vec3s corner[4];
    Vec3s center;
    s32 color[2];
    s32 i;
    s32 pass;

    color[0] = 0x00808080;
    color[1] = 0x00FFFFFF;

    {
        u16 *rot;

        for (i = 3, rot = (u16 *)D_80083780; i >= 0; i--) {
            s32 ang = i << 10;

            corner[i].x = rot[1] + (func_800644B8(*(s16 *)(arg0 + 0x28) + ang) >> 6);
            corner[i].y = rot[3] + (func_80064584(*(s16 *)(arg0 + 0x28) + ang) >> 6);
            corner[i].z = rot[5] - 0xA0;
        }
    }

    {
        u16 *rot = (u16 *)D_80083780;

        center.x = rot[1];
        center.y = rot[3];
        center.z = rot[5] - 0x60;
    }

    i = ((s16)*(u16 *)(arg0 + 0x2E) >> 1) + 0x80;
    if (i < 0) {
        i = 0;
    } else if (i >= 0x100) {
        i = 0xFF;
    }

    color[1] = i + (i << 8) + (i << 16);
    color[0] = 0x00FFFFFF - color[1];

    for (pass = 2; pass >= 0; pass--) {
        for (i = 3; i >= 0; i--) {
            edge[0] = edge[i + 2];
            edge[1] = edge[((i + 1) & 3) + 2];
            func_80020948(D_8002241C, edge, color, arg0);
        }

        for (i = 3; i >= 0; i--) {
            corner[i].z += 0x20;
        }
    }
}
