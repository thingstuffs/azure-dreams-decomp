#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_800C2E84(s32, void *, void *);           /* extern */
M2C_UNK func_800C591C();        /* extern */
extern M2C_UNK D_800D54C4;


/* Process the object when either of its 0x6000 flag bits is set. */
void func_800C5ADC(s32 contextId, M2C_UNK contextData, Rec_D_80082E80 *object) {
    if (object->unk_14.at00_u16.v & 0x6000) {
        func_800C2E84(contextId, object, &D_800D54C4);
        func_800C591C(contextId, contextData, object);
    }
}
