#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"





M2C_UNK func_8001886C();                     /* extern */

/* Decrement the countdown and invoke handler 0x5FF when it reaches zero. */
void func_80016824(void) {
    u8 countdown;
    TownEventCursor *countdown_record;

    countdown_record = &((TownProgressState *)D_80016000->unk_40)->eventCursor;
    countdown = countdown_record->counter - 1;
    countdown_record->counter = countdown;
    if (!(countdown & 0xFF)) {
        func_8001886C(0x5FF);
    }
}
