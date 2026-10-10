#include "modules/dungeon_ovl_1924800.h"

/* Effect record: the object header precedes it. */

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
