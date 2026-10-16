#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C70B8_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C70B8_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800C70B8 */


extern void townInitializeObjectEntries();
extern void townApplyObjectSetupAndUpdate();


/* Clears the object's table flag and resets its animation before updating it. */
void func_800C70B8(Rec_func_80094268_arg0 *object, s32 position, s32 anim_state) {
    townInitializeObjectEntries(object, anim_state, ((S_800C70B8_1 *)(object->unk_80))->unk_04);
    *(((u8 *)D_80082660) + (object->unk_60 * 8)) = 0;
    object->unk_72.as_s16 = 0x200;
    townApplyObjectSetupAndUpdate(object, position, anim_state);
}
