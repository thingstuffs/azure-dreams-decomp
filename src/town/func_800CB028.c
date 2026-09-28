#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800C2E84();  /* extern */
extern M2C_UNK D_800C86EC;
extern M2C_UNK D_800D6290;



/* Advance the motion state and update the object when its step is nonnegative. */
void func_800C8788(Rec_func_80094268_arg0 *object, EntityRec *motion, M2C_UNK context) {
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    func_80095388(motion);
    if (motion->flags14 >= 0) {
        func_800C2E84(object, context, &D_800D6290);
        object->unk_54 = &D_800C86EC;
    }
}
