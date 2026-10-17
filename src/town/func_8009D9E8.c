#include "common.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082D58.h"



M2C_UNK func_80033D08();
void townUnlinkSceneListNode();
s32 townUpdateObjectAndClearStatusFields();
void townSetStateBytesFromFlags();
s32 townClassifyObjectAgainstBounds(void *, s32);


typedef struct S_8009B148_0_pre {
    u16 unk_00;
} S_8009B148_0_pre;   /* the 0x2 bytes before arg0 in townDispatchObjectEventOrRetire, addressed as arg0[-1] */


/* Dispatches an object event or cleans up the object when the event check succeeds. */
void townDispatchObjectEventOrRetire(void *object, s32 event, s32 event_data)
{
    s32 saved_event = event;
    register s32 saved_event_data = event_data;
    s8 *status_ptr;

    if (townClassifyObjectAgainstBounds(object, event) != 0) {
        townUnlinkSceneListNode(object);
        status_ptr = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (status_ptr != 0) {
            *status_ptr = 0;
        }
        func_80033D08(object);
        ((S_8009B148_0_pre *)object)[-1].unk_00 =
            (u16)(((S_8009B148_0_pre *)object)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(
        object, object, saved_event, saved_event_data);
    if (!(((S_8009B148_0_pre *)object)[-1].unk_00 & 0x8000)) {
        townSetStateBytesFromFlags(townUpdateObjectAndClearStatusFields(saved_event), object);
    }
}
