/* Shop object value format and its file-private helper. */
#include "common.h"
typedef struct {
    u8 pad[0x10];
    u8 kind;
    u8 pad2[3];
} ItemCategory;
typedef struct {
    u8 pad0;
    u8 category;
    s8 value;
    u8 flags;
} Item;
extern ItemCategory item_category_groups[];
extern s32 memset(void *, s32, s32);
extern void func_8004E5A0(s32, s32, u8 *);
extern u8 *remap_flagged_string_bytes(u8 *);
extern s32 build_positioned_text_glyphs(void *, u8 *, s32);
void flag_object_for_removal(unsigned short *object);
s32 create_callback_pair_default();
s32 func_8004B404();
/* extern */
static s32 format_item_value_and_flag_marker();

static s32 format_item_value_and_flag_marker(void *output, Item *item) {
    u8 text[0x20];
    u8 category;
    s32 category_kind;

    memset(text, 0x20, 0x20);
    text[0x1F] = 0;
    category = item->category;
    category_kind = item_category_groups[category].kind;
    if (category_kind == 1) {
        s8 value = item->value;

        if (value != 0) {
            text[0xA] = (value > 0) ? 0x6B : 0x6C;
            func_8004E5A0((item->value >= 0) ? item->value : -item->value,
                          2, &text[0xB]);
            remap_flagged_string_bytes(&text[0xB]);
        }
        if (item->flags & 0x40) {
            text[0xD] = 0xA;
            text[0xE] = 0x7A;
        }
    } else {
        if (category != 4) {
            return 0;
        }
        func_8004E5A0(item->value, 2, &text[0xB]);
        remap_flagged_string_bytes(&text[0xB]);
    }
    return build_positioned_text_glyphs(output, text, 0);
}

s32 allocate_and_initialize_shop_object(s32 initializationArg) {
    s32 allocatedObject;
    s32 resultObject;

    allocatedObject = create_callback_pair_default(0x100);
    resultObject = allocatedObject;
    if (allocatedObject != 0) {
        resultObject = allocatedObject;
        if (format_item_value_and_flag_marker(allocatedObject, initializationArg) == 0) {
            flag_object_for_removal(allocatedObject);
            resultObject = 0;
        }
    }
    return resultObject;
}
