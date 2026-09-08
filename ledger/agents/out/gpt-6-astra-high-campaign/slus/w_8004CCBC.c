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

/* Copy the global vector D_8002E5E8 into each object's vector. */
void func_8004CCBC(func_8004CCBC_Obj **objects, s32 object_count)
{
    s32 object_index;

    for (object_index = 0; object_index < object_count; object_index++, objects++) {
        (*objects)->vec->x = D_8002E5E8.x;
        (*objects)->vec->y = D_8002E5E8.y;
        (*objects)->vec->z = D_8002E5E8.z;
    }
}
