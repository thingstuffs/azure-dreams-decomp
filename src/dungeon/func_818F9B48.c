#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"


/* The effect's record; its ObjectNodeHeader sits right before it. */
typedef struct CountdownRecord {
    u16 pad_00;
    u16 counter;
} CountdownRecord;

/* Decrement the record counter and set completion flags when it reaches zero. */
void func_80025348(CountdownRecord *record)
{
    u16 counter;

    counter = record->counter;
    D_800266BC = 1;
    counter--;
    record->counter = counter;
    if ((counter << 16) <= 0) {
        ((ObjectNodeHeader *)record - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

