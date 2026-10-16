#include "common.h"
#include "m2c_compat.h"

s32 townSelectChoiceFromInputFlags(s32);                                /* extern */
void townWriteIndexedTemplateValue();                    /* extern */

/* Processes the entry when its lookup returns a valid index. */
void townProcessValidEntryLookup(s32 entry_id) {
    s32 entry_index;

    entry_index = townSelectChoiceFromInputFlags(entry_id);
    if (entry_index != -1) {
        townWriteIndexedTemplateValue(entry_id, entry_index);
    }
}
