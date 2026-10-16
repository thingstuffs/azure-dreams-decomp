#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeObjectEntries();          /* extern */
extern s8 D_80082680;
extern s32 D_800C7E70;
extern s32 D_800D5FE8;


/* Initialize the object state, callback, countdown, and starting value. */
void townInitializeMotherEventCountdown(Rec_func_80094268_arg0 *object, s32 unused, s32 init_data) {
    townInitializeObjectEntries(object, init_data, &D_800D5FE8);
    D_80082680 = 0;
    object->unk_54 = &D_800C7E70;
    object->unk_6C.as_s16 = 0xA;
    object->unk_72.as_s16 = 0xC00;
}
