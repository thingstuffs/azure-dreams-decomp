#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"





/* Increment the byte counter in the record at offset 0x68. */
void func_80016874(void) {
    TownEventCursor *counter_record;

    counter_record = &((TownProgressState *)D_80016000->unk_40)->eventCursor;
    counter_record->counter = (u8) (counter_record->counter + 1);
}
