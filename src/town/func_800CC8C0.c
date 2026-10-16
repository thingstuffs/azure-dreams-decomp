#include "common.h"
#include "m2c_compat.h"

void setResidentBitmapBit();                     /* extern */
void townUnlinkSceneListNode();                      /* extern */
void townClearObjectSlotAndMarkRemoved();                      /* extern */

typedef struct S_800CA020_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA020_0;   /* arg1 in townAdvanceReactionAccumulators */

typedef struct S_800CA020_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800CA020_1;   /* arg2 in townAdvanceReactionAccumulators */

/* Advance two accumulators and invoke handlers when flag 0x8000 is set. */
void townAdvanceReactionAccumulators(void *context, S_800CA020_0 *accumulators, S_800CA020_1 *flagState) {
    accumulators->unk_00 = (s32) (accumulators->unk_00 + 0x40000);
    accumulators->unk_04 = (s32) (accumulators->unk_04 + 0x15555);
    if (flagState->unk_14 & 0x8000) {
        setResidentBitmapBit(0x49);
        townUnlinkSceneListNode(context);
        townClearObjectSlotAndMarkRemoved(context);
    }
}
