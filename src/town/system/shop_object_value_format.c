/* Shop object value format and its file-private helper. */
#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "engine/resource.h"
#include "engine/text.h"

typedef struct {
    u8 pad[0x10];
    u8 kind;
    u8 pad2[3];
} ItemCategory;
extern ItemCategory item_category_groups[];
extern s32 memset(void *, s32, s32);
extern void func_8004E5A0(s32, s32, u8 *);
/*
 * Builds text glyphs for an item's numeric value and flag marker, returning 0 for unsupported
 * categories.
 */
static void *format_item_value_and_flag_marker(void *output, DungeonItemEntry *item) {
    u8 text[0x20];
    u8 category;
    s32 category_kind;

    memset(text, 0x20, 0x20);
    text[0x1F] = 0;
    category = item->kind;
    category_kind = item_category_groups[category].kind;
    if (category_kind == 1) {
        s8 value = item->unk_02;

        if (value != 0) {
            text[0xA] = (value > 0) ? 0x6B : 0x6C;
            func_8004E5A0((item->unk_02 >= 0) ? item->unk_02 : -item->unk_02,
                          2, &text[0xB]);
            remap_flagged_string_bytes(&text[0xB]);
        }
        if (item->unk_03 & 0x40) {
            text[0xD] = 0xA;
            text[0xE] = 0x7A;
        }
    } else {
        if (category != 4) {
            return 0;
        }
        func_8004E5A0(item->unk_02, 2, &text[0xB]);
        remap_flagged_string_bytes(&text[0xB]);
    }
    return build_positioned_text_glyphs(output, text, 0);
}

/* Allocates an item text object and marks it for removal if value formatting fails. */
void *allocate_and_initialize_shop_object(DungeonItemEntry *item) {
    void *allocated_object;
    void *result_object;

    allocated_object = create_callback_pair_default(0x100);
    result_object = allocated_object;
    if (allocated_object != 0) {
        result_object = allocated_object;
        if (format_item_value_and_flag_marker(allocated_object, item) == 0) {
            flag_object_for_removal(allocated_object);
            result_object = 0;
        }
    }
    return result_object;
}
