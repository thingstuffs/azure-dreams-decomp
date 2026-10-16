#include "common.h"

extern void townGetSecondWordIndexedEntryInSNestedTable(void *, u8, s8, s32);

/* Passes an indexed byte and the object's signed field to townGetSecondWordIndexedEntryInSNestedTable. */
void townCallAnIndexedByteSSignedFieldCallee80096A5C(void *object, u8 *values, s32 index) {
    townGetSecondWordIndexedEntryInSNestedTable(object, values[index], ((s8 *)object)[4], 0);
}
