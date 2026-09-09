#include "common.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad0[8];
    s32 value;
    Entry *next;
    u8 pad10[4];
};

extern void *D_80016000;
extern void func_8001A5E4(s32);

/* Look up a value by group and entry index and pass it to the handler. */
void func_80019394(s32 group_index, s32 entry_index) {
    void *root;
    Entry *level;
    Entry *groups;
    Entry *entries;

    do {
        root = D_80016000;
    } while (0);
    level = *(Entry **)((u8 *)root + 0x24);
    groups = *(Entry **)((u8 *)level + 0x6C);
    do { entries = groups[group_index].next; } while (0);
    func_8001A5E4(entries[entry_index].value);
}
