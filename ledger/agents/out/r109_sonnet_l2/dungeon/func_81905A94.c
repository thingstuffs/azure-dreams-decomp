#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

/* Effect record: the object header precedes it. */
typedef struct CountdownRecord {
    u16 pad_00;
    u16 counter;
} CountdownRecord;

extern s16 D_800267B8[5];

/* Decrement the record counter and set completion flags when it reaches zero. */
void func_80025294(CountdownRecord *record)
{
    u16 counter;

    counter = record->counter;
    D_800267B8[0] = 1;
    counter--;
    record->counter = counter;
    if ((counter << 16) <= 0) {
        ((ObjectNodeHeader *)record - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
