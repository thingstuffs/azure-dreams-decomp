#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern s16 D_80083160[];
extern s32 rcos(s32);
extern s32 rsin(s32);

void func_8003E02C(Vec3s *arg0, Vec3s *arg1) {
    arg1->x = (rcos(D_80083160[0x64]) * arg0->x) >> 12;
    arg1->y = (-(rsin(D_80083160[0x64]) * arg0->x)) >> 12;
    arg1->z = arg0->y * 2;
}
