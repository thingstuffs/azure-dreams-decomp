#include "common.h"

extern s16 D_800FE4A6;
extern s32 townLow12ValuesWithin511(s16 value_a, s16 value_b);
extern s32 townGetTransformEntryByIndex(s32 entry_index);

/* Update the object's state value according to whether the pair check returns zero. */
void townUpdateTransformStateValue(void *object) {
    s32 result;

    result = townLow12ValuesWithin511(D_800FE4A6, *(s16 *)((s8 *)object + 0x16));
    if (result != 0) {
        *(s32 *)((s8 *)object + 0xC) = townGetTransformEntryByIndex(0);
    } else {
        *(s32 *)((s8 *)object + 0xC) = townGetTransformEntryByIndex(1);
    }
}
