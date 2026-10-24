#include "shared/entity.h"
/* Creates a sequence of indexed objects from copied position data and preset state references. */
/* inferred-strong G00569: indexed_object_state_g00569; joins CL:town/func_800A5CF0; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A5CF0. */
#include "town/menu/indexed_object_state_g00569.h"
#include "shared/object_node.h"

/* Lowers the third coordinate by 0x240000 and creates up to twelve indexed objects, stopping on failure. */
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
    ObjectNodeHeader *object;
    ObjectPosition *object_data;
    ObjectNodeHeader *result;

    object = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
    if (object == 0) {
        return 0;
    }
    object_data = object->position;
    object_data->x.v = source_data->unk_00;
    object_data->y.v = source_data->unk_04;
    result = object;
    object_data->z.v = source_data->unk_08;
    result->update_callback = D_800A34E0;
    ((S_800A3450_3 *)result)->unk_20 = D_800A3508;
    ((S_800A3450_3 *)result)->unk_42 = initial_value;
    return result;
}
