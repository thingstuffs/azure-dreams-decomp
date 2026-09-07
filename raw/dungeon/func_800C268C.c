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

typedef struct Object {
    u8 pad00[0x13];
    u8 value13;
    u8 pad14[8];
    u32 flags1C;
    u8 pad20[8];
    u8 value28;
    u8 pad29[0x23];
    u8 *target4C;
    u8 *mode50;
    u8 pad54[0xC];
    u32 value60;
    u16 value64;
} Object;

typedef struct Other {
    u8 pad00[0x54];
    u32 flags54;
    u8 pad58[0xC];
    u16 value64;
} Other;

extern DungeonGroup D_80073414[];
extern void *D_80083470;
extern u8 D_800E3E41;
extern void func_800A56E0(s32);
extern void func_800A5A18(void *, Object *, void *);

s32 func_800C7DEC(Object *object, Other *other) {
    u8 *target;
    s16 available;
    u8 mode;
    s16 amount;

    if (other->flags54 & 0x8000) {
    target = object->target4C;
    if (target != 0) {
        u8 row;
        DungeonGroup *groups;
        DungeonGroup *group;
        DungeonCell *cells;
        u8 column;

        row = target[1];
        groups = D_80073414;
        group = &groups[row];
        column = target[0];
        
        cells = group->cells;
        if (!(cells[column].flags & 0x8000)) {
            return 0;
        }
    }
    available = object->value28 + object->value64;
    if (available <= 0) {
        return 0;
    }
    amount = (s16)other->value64 >> 2;
    if (amount == 0) {
        amount = -1;
    }
    if (-available >= (s16)amount) {
        return 0;
    }
    if (object->mode50 != 0) {
        mode = object->mode50[0];
        if ((u32)(mode - 1) < 2) {
            amount = (amount - 1) / 2;
        } else if (mode == 10) {
            return 0;
        }
    }
    *(volatile u16 *)&object->value64 = amount;
    D_80083470 = (u8 *)object - 0x20;
    ASM_SCHED_BARRIER();
    object->value60 = 0;
    func_800A5A18(*(void **)((u8 *)object - 0x18), object, target);
    func_800A56E0(0x60F);
    object->flags1C |= 0x20000000;
    if (object->value13 == 0) {
        D_800E3E41 = 2;
    }
    return 1;
    }
    return 0;
}

/* MECHANISM: True-space CFG uses a 24-byte frame, only s0, and a late default-zero tail.
   Correct Object/Other offsets plus a kept group base reproduce the table lookup and a2 hold.
   A narrow s16 amount fixes a0/a1 roles; volatile sh plus a post-store fence closes ordering. */
