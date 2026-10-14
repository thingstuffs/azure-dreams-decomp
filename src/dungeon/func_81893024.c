#include "shared/object_node.h"
#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)






   /* temp_v1 in func_80024824 */

/* Creates an object with copied data, an adjusted field, and initialized arguments. */
void *func_80024824(s32 object_arg, void *source_data, s16 initial_value, s16 field_delta) {
    B22_81893024_M2C_BLOCK *src;
    B22_81893024_M2C_OBJECT *object;
    s32 *object_args;
    B22_81893024_M2C_BLOCK *data;

    object = func_8003FC64(0x212);

    if (object != NULL) {
        src = (B22_81893024_M2C_BLOCK *)source_data;
        object->callback = func_800243F8;
        object_args = &object->params;
        object->params = object_arg;
        ((s16 *)object_args)[2] = 0;
        ((s16 *)object_args)[3] = initial_value;
        data = object->data;
        *data = *src;
        ((B22_81893024_S_81893024_0 *)data)->unk_0A = (s16) (((B22_81893024_S_81893024_0 *)data)->unk_0A + field_delta);
        func_8004491C(object, func_8002445C);
    } else {
        return NULL;
    }
    return object;
}
