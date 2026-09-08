#include "common.h"
#include "records/Rec_func_80094268_arg0.h"




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C3050();
M2C_UNK func_800CB8CC();
extern M2C_UNK D_800D69DC;
extern M2C_UNK D_800D69E4;
extern M2C_UNK D_800D6A0C;
extern M2C_UNK D_800D6A10;


/* Initialize the object with resource 8 and apply its stored variant. */
void func_800CB770(Rec_func_80094268_arg0 *object) {
    func_800C3050(object, 8, &D_800D6A0C, &D_800D6A10, &D_800D69DC, &D_800D69E4);
    func_800CB8CC(object, object->unk_96.as_u8);
}
