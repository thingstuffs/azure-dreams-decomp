#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033CD8();                   /* extern */
void townConfigureTheSetModeN1();  /* extern */
void townClearObjectStatusAndDispatchTarget(); /* extern */
void townDispatchObjectState();    /* extern */
extern M2C_UNK D_800D5028;


/* Initialize the object and its animation, then dispatch its current state. */
void townInitializePersonObject(Rec_func_80094268_arg0 *object, s32 context, s32 animation) {
    func_80033CD8(object, func_80045340);
    object->unk_8C = 0x40;
    object->unk_8E = 0x40;
    townClearObjectStatusAndDispatchTarget(object, animation, **object->unk_7C.as_pps32, 0);
    townConfigureTheSetModeN1(object, context, &D_800D5028);
    townDispatchObjectState(object, context, animation);
}
