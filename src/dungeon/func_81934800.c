#include "common.h"


typedef struct DungeonCell {
    s16 flags;
    u8 pad02[0x12];
} DungeonCell;

typedef struct DungeonGroup {
    u8 pad00[0xC];
    DungeonCell *cells;
    u8 pad10[4];
} DungeonGroup;

typedef struct DungeonObjectEntry {
    u8 column;
    u8 group;
    s8 amount;
    u8 pad03[0x11];
} DungeonObjectEntry;

typedef struct DungeonObject {
    u8 pad00[0x4C];
    DungeonObjectEntry *entry4C;
    DungeonObjectEntry *entry50;
} DungeonObject;

extern s32 func_800C80F0(void);
extern DungeonGroup D_80073414[];

/* Decrement eligible entry amounts on flagged cells and return the number changed. */
s32 func_80024004(DungeonObject *object) {
    s32 changed_count;
    DungeonObjectEntry *entry;
    u8 group;
    u8 column;

    changed_count = 0;
    if (func_800C80F0() != 0) {
        return changed_count;
    }
    entry = object->entry4C;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((D_80073414[group].cells[column].flags & 0x8000) != 0 &&
            entry->amount >= -0x62) {
            entry->amount = (u8)entry->amount - 1;
            changed_count = 1;
        }
    }
    entry = object->entry50;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((D_80073414[group].cells[column].flags & 0x8000) != 0) {
            if (entry->amount >= -0x62) {
                entry->amount = (u8)entry->amount - 1;
                changed_count += 1;
            }
        }
    }
    return changed_count;
}
