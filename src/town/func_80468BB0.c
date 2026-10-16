#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



void townCopyThreeComponentValues();                      /* extern */
extern u8 D_80017B30;


/* Pass the callback-selected eight-byte table entry to townCopyThreeComponentValues. */
void townPassCallbackSelectedEntry(void) {
    townCopyThreeComponentValues((D_80016000->unk_20->callback_2D4(0) * 8) + &D_80017B30);
}
