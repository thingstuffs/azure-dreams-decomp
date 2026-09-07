#include "common.h"
typedef struct { s16 x; s16 y; s16 z; s16 pad; } Vec3s;
extern u8 D_80528910[]; extern u16 D_80132AEA[];
extern void func_80526E4C(void *, void *, void *, void *);
extern s32 func_8006A3A4(s32); extern s32 func_8006A470(s32);
void func_80528998(u8 *arg0)
{
    Vec3s edge[2]; Vec3s corner[4]; Vec3s center; s32 color[2]; s32 i; s32 pass;
    color[0] = 0x00808080; color[1] = 0x00FFFFFF;
    { u16 *rot;
      for (i = 3, rot = D_80132AEA; i >= 0; i--) {
        s32 ang = i << 10; s32 x; s32 y;
        x = func_8006A3A4(*(s16 *)(arg0 + 0x28) + ang);
        corner[i].x = (x = (x >> 6) + rot[0]);
        y = func_8006A470(*(s16 *)(arg0 + 0x28) + ang);
        corner[i].y = (y = (y >> 6) + rot[2]);
        corner[i].z = rot[4] - 0xA0;
      }
    }
    { u16 *rot = D_80132AEA; center.x = rot[0]; center.y = rot[2]; center.z = rot[4] - 0x60; }
    i = ((s16)*(u16 *)(arg0 + 0x2E) >> 1) + 0x80;
    if (i < 0) i = 0; else if (i >= 0x100) i = 0xFF;
    color[1] = i + (i << 8) + (i << 16); color[0] = 0x00FFFFFF - color[1];
    for (pass = 2; pass >= 0; pass--) {
      for (i = 3; i >= 0; i--) { edge[0] = corner[i]; edge[1] = corner[(i + 1) & 3]; func_80526E4C(D_80528910, edge, color, arg0); }
      for (i = 3; i >= 0; i--) corner[i].z += 0x20;
    }
}
