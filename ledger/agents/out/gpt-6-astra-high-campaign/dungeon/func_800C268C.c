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

/* Apply a mode-adjusted quarter-value change when the source and target item flags permit it. */
s32 func_800C7DEC(Object *object, Other *source) {
    u8 *target_item;
    s16 total_value;
    u8 mode;
    s16 adjustment;

    if (source->flags54 & 0x8000) {
        target_item = object->target4C;
        if (target_item != 0) {
            u8 category_index;
            DungeonGroup *item_category_table;
            DungeonGroup *item_category;
            DungeonCell *item_entries;
            u8 item_index;

            category_index = target_item[1];
            item_category_table = D_80073414;
            item_category = &item_category_table[category_index];
            item_index = target_item[0];

            item_entries = item_category->cells;
            if (!(item_entries[item_index].flags & 0x8000)) {
                return 0;
            }
        }
        total_value = object->value28 + object->value64;
        if (total_value <= 0) {
            return 0;
        }
        adjustment = (s16)source->value64 >> 2;
        if (adjustment == 0) {
            adjustment = -1;
        }
        if (-total_value >= (s16)adjustment) {
            return 0;
        }
        if (object->mode50 != 0) {
            mode = object->mode50[0];
            if ((u32)(mode - 1) < 2) {
                adjustment = (adjustment - 1) / 2;
            } else if (mode == 10) {
                return 0;
            }
        }
        *(volatile u16 *)&object->value64 = adjustment;
        D_80083470 = (u8 *)object - 0x20;
        object->value60 = 0;
        func_800A5A18(*(void **)((u8 *)object - 0x18), object, target_item);
        func_800A56E0(0x60F);
        object->flags1C |= 0x20000000;
        if (object->value13 == 0) {
            D_800E3E41 = 2;
        }
        return 1;
    }
    return 0;
}
