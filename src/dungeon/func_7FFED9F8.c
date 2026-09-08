#include "common.h"

typedef struct {
    u8 pad0[8];
    u32 flags0;
    u32 flags1;
} Item;

typedef struct {
    u8 pad0[0x48];
    s32 value48;
    u8 pad4C[0x14];
    s32 value60;
    u8 pad64[0x34];
    Item *item98;
} Object;

typedef struct {
    s32 value0;
    s32 value4;
    s32 value8;
    s32 valueC;
    s32 value10;
    s32 value14;
} TownState;

extern TownState D_801131B8;
extern void func_80035208(void *);
extern void func_8008B0E8(s32, u32, u32, u32);

/* Copies tagged item fields into town state and dispatches the associated data. */
void func_8008B158(Object *object) {
    Item *item;
    u32 tag_mask;
    u32 extra_flags;
    s32 option_bit;
    u32 high_field;
    u32 middle_field;
    u8 *data;
    u32 data_base;
    u32 data_offset;

    item = object->item98;
    if ((item != 0) && (tag_mask = item->flags0 & 0xC0000000, tag_mask == 0xC0000000)) {
        D_801131B8.value0 = object->value60;
        option_bit = (item->flags0 >> 23) & 1;
        D_801131B8.value4 = option_bit;
        high_field = (item->flags0 & 0x3F000000) >> 24;
        D_801131B8.value8 = high_field;
        middle_field = (item->flags0 & 0x007F0000) >> 16;
        D_801131B8.valueC = middle_field;
        extra_flags = item->flags1;
        if ((extra_flags & tag_mask) == tag_mask) {
            D_801131B8.value10 = (extra_flags & 0x3F000000) >> 24;
            D_801131B8.value14 = (item->flags1 & 0x007F0000) >> 16;
        }
        func_8008B0E8(option_bit, high_field, middle_field, extra_flags);
        data_base = 0x80016000;
        data_offset = *(u16 *)&item->flags0;
        data = (u8 *)(data_base + data_offset);
    } else {
        data = (u8 *)object->value48;
    }
    func_80035208(data);
}
