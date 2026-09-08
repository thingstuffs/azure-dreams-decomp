#include "common.h"

#include "common.h"

typedef struct {
    s16 marker;
    u8 pad02[0x0A];
    s32 owner;
    s32 unk10;
    s32 unk14;
    u8 pad18[4];
} S_80086A40; /* size 0x1C */

extern s32 func_8005ECA0(s32 arg0);
extern s32 func_8005EC40(s32 arg0, s32 arg1);
extern S_80086A40 D_80086A40[];

/* Assigns an owner and updates the entry value if its marker and owner check pass. */
s16 func_8005AAA8(s32 owner, s16 entry_id)
{
    s32 updated_value;
    s16 marker;
    S_80086A40 *entries;
    S_80086A40 *entry;

    entries = D_80086A40;
    entry = &entries[entry_id];
    marker = entry->marker;
    if (marker == entry_id) {
        updated_value = func_8005ECA0(entry->unk10);
        if (func_8005EC40(owner, entry->unk14) == entry->unk14) {
            entry->owner = owner;
            entry->unk10 = updated_value;
            return marker;
        }
        return -1;
    }
    return -1;
}
