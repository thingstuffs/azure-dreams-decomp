/* Relink of matched town/func_8032E634; every changed retail word is a paired relocation. */
#define townReleaseLshopEntry func_80018BE4
#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"

extern void func_80018AC4(void *);

// Clears the indexed object and marks its slot unused, with cleanup for type 0x13.
void func_80018BE4(s32 slotIndex) {
    TownStateRecord *objectTableBase;
    void **objectSlot;
    void *object;

    objectTableBase = D_80016000->unk_38;
    objectSlot = objectTableBase->entries;
    objectSlot += slotIndex;
    object = *objectSlot;
    if (*((u8 *)object + 1) == 0x13) {
        func_80018AC4(object);
    }
    *(s32 *)*objectSlot = 0;
    *objectSlot = (void *)-1;
}
