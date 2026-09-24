#include "common.h"

typedef struct Slot_800A48F0 {
    s8 id;
    u8 value;
} Slot_800A48F0;

typedef struct Owner_800A48F0 {
    u8 pad_00[0x2C];
    Slot_800A48F0 slots[4];
} Owner_800A48F0;

extern void func_80042BDC(void *, s16);
extern void func_80042B68(void *, s8);
extern void func_800A4B88(void *, s32);

/* Updates or inserts a four-slot entry, clearing conflicts or evicting an entry when full. */
s16 func_800A48F0(Owner_800A48F0 *owner, s8 id, s8 value) {
    s16 min_id;
    s32 i;
    s32 used;

    min_id = 0x100;
    for (i = 3; i >= 0; i--) {
        if (owner->slots[i].id == id) {
            if ((((u8)value ^ owner->slots[i].value) & 0x80) || value == 0) {
                func_80042BDC(owner, owner->slots[i].id);
                owner->slots[i].id = 0;
                owner->slots[i].value = 0;
            } else {
                owner->slots[i].value = value;
            }
            func_800A4B88(owner, id);
            return i;
        }
    }
    for (i = 3; i >= 0; i--) {
        used = owner->slots[i].id;
        if (used == 0) {
            if (id == 1) {
                func_80042B68(owner, 4);
            } else if (id == 4) {
                func_80042B68(owner, 1);
            }
            owner->slots[i].id = id;
            owner->slots[i].value = value;
            func_800A4B88(owner, id);
            return i;
        }
        if (used < min_id) {
            min_id = used;
        }
    }
    if (min_id > id) {
        func_80042B68(owner, min_id);
        return func_800A48F0(owner, id, value);
    }
    return -1;
}
