#include "common.h"

/* S_8002E5E8: 3-field vector-like struct (x,y,z), source data copied into target entities' ->vec */
typedef struct S_8002E5E8 {
    s32 x;
    s32 y;
    s32 z;
} S_8002E5E8;

extern S_8002E5E8 D_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    S_8002E5E8 *vec;
} func_8004CCBC_Obj;

/* summary: for i in [0,a1), copy the 3-word global vector D_8002E5E8 into (*a0)->vec, advancing a0 by one pointer each iteration */
void func_8004CCBC(func_8004CCBC_Obj **a0, s32 a1)
{
    s32 i;

    for (i = 0; i < a1; i++, a0++) {
        (*a0)->vec->x = D_8002E5E8.x;
        (*a0)->vec->y = D_8002E5E8.y;
        (*a0)->vec->z = D_8002E5E8.z;
    }
}
