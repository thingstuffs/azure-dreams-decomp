#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void townInitializeObjectAndRegisterSlot();
s32 townCreateAndInvokeRenderObject();
extern M2C_UNK D_800D69DC;
extern M2C_UNK D_800D69E4;
extern M2C_UNK D_800D6A0C;
extern M2C_UNK D_800D6A10;


/* Initialize the object with resource 8 and apply its stored variant. */
void townInitializeVariantObject(Rec_func_80094268_arg0 *object) {
    townInitializeObjectAndRegisterSlot(object, 8, &D_800D6A0C, &D_800D6A10, &D_800D69DC, &D_800D69E4);
    townCreateAndInvokeRenderObject(object, object->unk_96.as_u8);
}
