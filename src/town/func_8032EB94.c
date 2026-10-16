#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad0[8];
    s32 value;
    Entry *next;
    u8 pad10[4];
};

extern void townPrepareSharedTextBuffer(s32);

/* Look up a value by group and entry index and pass it to the handler. */
void townLookupLshopValue(s32 group_index, s32 entry_index) {
    Rec_D_80016000 *root;
    TownResourceLinks *level;
    Entry *groups;
    Entry *entries;

    root = D_80016000;
    level = (TownResourceLinks *)root->unk_24;
    groups = level->gridRows;
    entries = groups[group_index].next;
    townPrepareSharedTextBuffer(entries[entry_index].value);
}
