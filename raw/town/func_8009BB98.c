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

extern void func_80053DA8();
extern void func_80094984();
extern void func_80099754();
extern u8 D_800983BC;
extern u8 D_800D0158;
extern TownEntry D_80082660[];
extern u16 D_800D5070[];

void func_800992F8(TownObject *object, s32 arg1) {
    TownEntry *entries;
    u16 value;

    func_80094984(&D_800D0158, object);
    entries = D_80082660;
    entries[1].pad0[0] = 0;
    value = D_800D5070[entries[object->entry_index].table_index];
    object->handler = &D_800983BC;
    object->state = 3;
    object->value = value;
    func_80099754(arg1, D_800D5070);
    func_80053DA8(0x519);
}

/* MECHANISM: The object and second argument stay live across calls, yielding the retail
   0x20 frame and s0/s1 saves; the named 8-byte entry array yields the held base and sll 3.
   Lookup-before-stores fixes body order, and cdk schedules the a0 move after the base la. */
