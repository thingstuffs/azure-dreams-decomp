/* inferred-strong G00569: indexed_object_state_g00569; joins CL:town/func_800A5CF0; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A5CF0. */
#include "town/menu/indexed_object_state_g00569.h"

void check_adjusted_input_indices(Unk800A5C88 *input) {
    Unk800A5C88 adjustedInput;
    s32 checkIndex;

    adjustedInput.unk0 = input->unk0;
    checkIndex = 0;
    adjustedInput.unk4 = input->unk4;
    adjustedInput.unk8 = input->unk8 - 0x240000;

    do {
        if (allocate_object_with_initial_state((EffectInitialState *)&adjustedInput.unk0, checkIndex) == 0) {
            break;
        }
        checkIndex++;
    } while (checkIndex < 12);
}

/* Creates an object with copied input data, preset references, and an initial value. */
void *allocate_object_with_initial_state(EffectInitialState *source_data, s32 initial_value)
{
    ObjectPayloadView *object;
    EffectInitialState *object_data;
    void *result;

    object = allocate_list_node(0x136, ((u8 *)(&D_80083498)));
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
