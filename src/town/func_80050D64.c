#include "common.h"
#include "m2c_compat.h"

void setResidentBitmapBit();                     /* extern */
void townUnlinkSceneListNode();                      /* extern */
void townClearObjectSlotAndMarkRemoved();                      /* extern */

typedef struct ReactionAccumulators {
    s32 unk_00;
    s32 unk_04;
} ReactionAccumulators;   /* arg1 in advance_actor_reaction_downward */

typedef struct ReactionFlagState {
    u8 pad_00[0x14];
    u16 unk_14;
} ReactionFlagState;   /* arg2 in advance_actor_reaction_downward */

/* Advance two accumulators and invoke handlers when flag 0x8000 is set. */
void advance_actor_reaction_downward(void *context, ReactionAccumulators *accumulators, ReactionFlagState *flagState) {
    accumulators->unk_00 = (s32) (accumulators->unk_00 + 0x40000);
    accumulators->unk_04 = (s32) (accumulators->unk_04 - 0x15555);
    if (flagState->unk_14 & 0x8000) {
        setResidentBitmapBit(0x43);
        townUnlinkSceneListNode(context);
        townClearObjectSlotAndMarkRemoved(context);
    }
}
