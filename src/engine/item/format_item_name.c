#include "common.h"
#include "shared/item_ids.h"
#include "engine/item.h"
#include "engine/text.h"
#include "engine/util.h"
#include "sdk/libc.h"

typedef struct
{
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 unk3;
}
S_8004951C_Item;

typedef struct
{
    u8 pad[0x28];
    u8 unk28;
}
S_800492B0_Ret;

typedef struct
{
    u8 unk0;
    u8 pad[0xF];
}
S_80082E6A;

extern S_80082E6A runtime_dispatch_mode_alias;
extern s32 get_scaled_byte_value(void *);

/* Formats and displays item modifiers and status markers. */
s32 format_item_name(s32 text_target, S_8004951C_Item *item)
{
    u8 text[0x20];
    s32 category;
    s32 kind;

    memset(text, 0x20, 0x20);
    text[0x1F] = 0;

    if ((runtime_dispatch_mode_alias.unk0 == 2) && (get_item_category_flags(item) != 0)) {
        return 0;
    }

    category = item->unk1;
    kind = itemCategoryTable[category].name_format;
    if (kind >= 4) {
        return 0;
    }

    if (kind == 3) {
        s32 subtype = item->unk3 & 0x1F;
        if ((subtype < 0x14) && (runtime_dispatch_mode_alias.unk0 != 1)) {
            S_800492B0_Ret *entry = resolve_indexed_value(subtype);
            if (entry->unk28 == 0) {
                text[0] = 0x7A;
            }
        }
    }
    else {
        if (item->unk1 == ITEM_KIND_EGG) {
            if (runtime_dispatch_mode_alias.unk0 != 1) {
                func_8004E5A0(0x64 - item->unk2, 3, &text[9]);
                remap_flagged_string_bytes(&text[9]);
                text[0xC] = 0xA;
                text[0xD] = 9;
                text[0xE] = 0x39;
                text[0x12] = 0x25;
            }
        }
        else if (item->unk1 == ITEM_KIND_BALL) {
            func_8004E5A0(item->unk2, 2, &text[0xB]);
            remap_flagged_string_bytes(&text[0xB]);
        }
        else if (item->unk1 == ITEM_KIND_COIN) {
            func_8004E5A0(get_scaled_byte_value(item), 5, &text[6]);
            remap_flagged_string_bytes(&text[6]);
            text[0xB] = 0xA;
            text[0xC] = 9;
            text[0xD] = 0x39;
            text[0x10] = 0x47;
        }
        else if (kind == 1) {
            s8 modifier = item->unk2;
            if (modifier != 0) {
                text[0xA] = (modifier > 0) ? (0x6B) : (0x6C);
                func_8004E5A0((item->unk2 >= 0) ? (item->unk2) : (-item->unk2), 2, &text[0xB]);
                remap_flagged_string_bytes(&text[0xB]);
            }
        }

        if (kind == 1) {
            if (item->unk3 & 0x40) {
                text[0xD] = 0xA;
                text[0xE] = 0x7A;
            }
            if (item->unk3 & 0x20) {
                text[0] = 0x79;
            }
        }
    }

    return build_positioned_text_glyphs(text_target, text, 0);
}
