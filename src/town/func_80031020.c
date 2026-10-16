/* Relink of matched town/func_800CB028; every changed retail word is a paired relocation. */
#define D_800C86EC D_800CE6E4
#define D_800D6290 D_800D72E8
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80095388();                      /* extern */
void func_800C2E84();  /* extern */
extern M2C_UNK D_800CE6E4;
extern M2C_UNK D_800D72E8;


/* Advance the motion state and update the object when its step is nonnegative. */
void func_800CE780(Rec_func_80094268_arg0 *object, EntityRec *motion, s32 context) {
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    func_80095388(motion);
    if (motion->flags14 >= 0) {
        func_800C2E84(object, context, &D_800D72E8);
        object->unk_54 = &D_800CE6E4;
    }
}
