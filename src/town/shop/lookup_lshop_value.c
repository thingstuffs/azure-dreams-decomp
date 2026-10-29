#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/dialogue.h"
#include "town/shop.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad0[8];
    s32 value;
    Entry *next;
    u8 pad10[4];
};

/* Look up a value by group and entry index and pass it to the handler. */
void lookup_lshop_value(s32 group_index, s32 entry_index) {
    Rec_D_80016000 *root;
    TownResourceLinks *level;
    Entry *groups;
    Entry *entries;

    root = town_scene_root;
    level = (TownResourceLinks *)root->unk_24;
    groups = level->gridRows;
    entries = groups[group_index].next;
    prepare_shared_text_buffer(entries[entry_index].value);
}
