#include "common.h"
#include "shared/types3a_types.h"

/* S_8002E5E8: 3-field vector-like struct (x,y,z), source data copied into target entities' ->vec */


extern DisplayPositionWords D_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    DisplayPositionWords *vec;
} func_8004CCBC_Obj;

/* Copy the global vector D_8002E5E8 into each object's vector. */
void apply_vector_3_template_to_nodes(func_8004CCBC_Obj **objects, s32 object_count)
{
    s32 object_index;

    for (object_index = 0; object_index < object_count; object_index++, objects++) {
        (*objects)->vec->unk0 = D_8002E5E8.unk0;
        (*objects)->vec->unk4 = D_8002E5E8.unk4;
        (*objects)->vec->unk8 = D_8002E5E8.unk8;
    }
}
