#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/town_handler.h"

void townClearEntityRecordFields();                      /* extern */
extern M2C_UNK D_80097EFC;
extern M2C_UNK D_800D0170;


/* Initialize the object and its transform with fixed placement and settings. */
void townInitializeObjectTransformAndHandler(Rec_func_80094268_arg0 *object, EntityRec *transform, void *ptr2) {
    townCallTheHandlerSelectsNonzeroEntry((s32 *) &D_800D0170, object, ptr2);
    object->unk_04.as_pm = &D_80097EFC;
    townClearEntityRecordFields(transform);
    transform->unk_0C = 0xFFFE0000;
    transform->unk_10 = 0x40000;
    transform->flags14 = 0xFFF90000;
    object->unk_10.as_s16 = 0xE00;
}
