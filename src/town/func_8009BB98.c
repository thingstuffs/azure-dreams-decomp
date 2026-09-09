#include "common.h"

typedef struct TownEntry {
    u8 pad0[2];
    s8 table_index;
    u8 pad3[5];
} TownEntry;

typedef struct TownObject {
    u8 pad0[4];
    void *handler;
    u8 pad8[2];
    s16 state;
    u8 padC[4];
    u16 value;
    u8 pad12[0x2E];
    s32 entry_index;
} TownObject;

extern void SD_Call();
extern void func_80094984();
extern void func_80099754();
extern u8 D_800983BC;
extern u8 D_800D0158;
extern TownEntry D_80082660[];
extern u16 D_800D5070[];

/* Set the object's handler, state, and entry-specific value, then update the table target. */
void func_800992F8(TownObject *object, s32 table_target) {
    TownEntry *entries;
    u16 entry_value;

    func_80094984(&D_800D0158, object);
    entries = D_80082660;
    entries[1].pad0[0] = 0;
    entry_value = D_800D5070[entries[object->entry_index].table_index];
    object->handler = &D_800983BC;
    object->state = 3;
    object->value = entry_value;
    func_80099754(table_target, D_800D5070);
    SD_Call(0x519);
}
