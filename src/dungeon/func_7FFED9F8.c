#include "modules/dungeon_ovl_d54c.h"

void submit_object_resource_data(ovl_d54c_7FFED9F8_Object *object) {
    ovl_d54c_7FFED9F8_Item *item;
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
        ensure_resource_at_front(option_bit, high_field, middle_field);
        data_base = 0x80016000;
        data_offset = *(u16 *)&item->flags0;
        data = (u8 *)(data_base + data_offset);
    } else {
        data = (u8 *)object->value48;
    }
    func_80035208(data);
}
