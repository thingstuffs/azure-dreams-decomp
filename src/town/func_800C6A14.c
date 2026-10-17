#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C4174_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C4174_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in townApplyObjectSetupAndUpdate */


extern void townInitializeObjectEntries(void *state, M2C_UNK output, M2C_UNK entries);
extern void townInstallObjectHandlerAndClearSlotFlag(void *object, M2C_UNK update_context, M2C_UNK setup_context);


/* Apply setup from the object descriptor and then run the object update. */
void townApplyObjectSetupAndUpdate(void *object, M2C_UNK update_context, M2C_UNK setup_context) {
    townInitializeObjectEntries(object, setup_context, ((S_800C4174_1 *)(((Rec_func_80094268_arg0 *)object)->unk_80))->unk_04);
    townInstallObjectHandlerAndClearSlotFlag(object, update_context, setup_context);
}
