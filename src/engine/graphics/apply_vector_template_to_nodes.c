#include "common.h"
#include "shared/gpu_packets.h"

/* S_8002E5E8: 3-field vector-like struct (x,y,z), source data copied into target entities' ->vec */


extern DisplayPositionWords display_vector_defaults;

typedef struct {
    s32 unk0;
    s32 unk4;
    DisplayPositionWords *vec;
} func_8004CCBC_Obj;

/* Copies all three words of display_vector_defaults into each object vector. */
void apply_vector_3_template_to_nodes(func_8004CCBC_Obj **objects, s32 object_count)
{
    s32 object_index;

    for (object_index = 0; object_index < object_count; object_index++, objects++) {
        (*objects)->vec->unk0 = display_vector_defaults.unk0;
        (*objects)->vec->unk4 = display_vector_defaults.unk4;
        (*objects)->vec->unk8 = display_vector_defaults.unk8;
    }
}
