#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef void (*TownCall3)(void *, void *, s32);
typedef void TownFatal1(s32) __attribute__((noreturn));
typedef struct Copy4 {
    u8 bytes[4];
} Copy4;


extern u8 D_80016034[];
extern u8 D_8001605C[];
extern void *find_unused_item_slot(void **slots);

/* Copies a four-byte entry, clears its flag bits, and appends it to the object list. */
void append_town_item(const Copy4 *input)
{
    void **slot;
    Copy4 *entry;

    slot = D_80016000->unk_38->entries;
    entry = find_unused_item_slot(slot);
    if (entry == 0) {
        ((TownCall3)D_80016000->unk_20->callback_168)(D_80016034, D_8001605C, 0x80);
        ((TownFatal1 *)D_80016000->unk_20->callback_174)(1);
    }
    *entry = *input;
    entry->bytes[3] &= 0x5F;
    while (*slot != 0)
        slot++;
    slot[0] = entry;
    slot[1] = 0;
}
