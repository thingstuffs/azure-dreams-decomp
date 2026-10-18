#include "common.h"
#include "shared/object_node.h"
#include "shared/types3a_types.h"


typedef struct S_800A3450_3 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x1E];
    s16 unk_42;
} S_800A3450_3;

extern void *func_8003FD64(s32, void *);
extern u8 D_800A34E0[];
extern u8 D_800A3508[];

/* Creates an object with copied input data, preset references, and an initial value. */
void *allocate_object_with_initial_state(EffectInitialState *source_data, s16 initial_value)
{
    ObjectPayloadView *object;
    EffectInitialState *object_data;
    void *result;

    object = func_8003FD64(0x136, ((u8 *)(&D_80083498)));
    if (object == 0) {
        return 0;
    }
    object_data = object->unk_08;
    object_data->unk_00 = source_data->unk_00;
    object_data->unk_04 = source_data->unk_04;
    result = object;
    object_data->unk_08 = source_data->unk_08;
    ((S_800A3450_3 *)result)->unk_10 = D_800A34E0;
    ((S_800A3450_3 *)result)->unk_20 = D_800A3508;
    ((S_800A3450_3 *)result)->unk_42 = initial_value;
    return result;
}
