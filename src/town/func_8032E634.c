#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"

void clear_shop_object_and_link(u8 *object_ref);

// Clears the indexed object and marks its slot unused, with cleanup for type 0x13.
void release_lshop_entry(s32 slotIndex) {
    TownStateRecord *objectTableBase;
    void **objectSlot;
    void *object;

    objectTableBase = D_80016000->unk_38;
    objectSlot = objectTableBase->entries;
    objectSlot += slotIndex;
    object = *objectSlot;
    if (*((u8 *)object + 1) == 0x13) {
        clear_shop_object_and_link(object);
    }
    *(s32 *)*objectSlot = 0;
    *objectSlot = (void *)-1;
}
