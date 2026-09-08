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

extern ItemCategory D_80073414[];
extern s32 memset(void *, s32, s32);
extern void func_8004E5A0(s32, s32, u8 *);
extern u8 *func_8004E69C(u8 *);
extern s32 func_8004E298(void *, u8 *, s32);

/* Format and output an item's value and flag marker for supported item categories. */
s32 func_800B0E18(void *output, Item *item) {
    u8 text[0x20];
    u8 category;
    s32 category_kind;

    memset(text, 0x20, 0x20);
    text[0x1F] = 0;
    category = item->category;
    category_kind = D_80073414[category].kind;
    if (category_kind == 1) {
        s8 value = item->value;

        if (value != 0) {
            text[0xA] = (value > 0) ? 0x6B : 0x6C;
            func_8004E5A0((item->value >= 0) ? item->value : -item->value,
                          2, &text[0xB]);
            func_8004E69C(&text[0xB]);
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
        func_8004E69C(&text[0xB]);
    }
    return func_8004E298(output, text, 0);
}
