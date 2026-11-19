/* Lay out three display elements and complementary values. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B79CC. */
#include "town/shop/display_element_layout_g00630.h"
#include "town/shop.h"

/* Set two entry bytes to complementary values derived from the amount. */
void *set_complementary_entry_bytes(void *entry, s16 amount) {
    u8 *base = entry;
    s32 remaining;
    s32 hidden_v1;

    if (amount < 300) {
        s32 quotient = amount / 4;

        hidden_v1 = quotient + 1;
    } else {
        hidden_v1 = 64;
    }

    remaining = 64;
    remaining -= hidden_v1;
    base[2] = remaining;
    {
        void *result = base;

        base[10] = hidden_v1;
        return result;
    }
}

/* Positions three display elements, assigns their content, and updates the shared value buffer. */
void *layout_three_display_elements(ActorRecord *actor, ItemMenuPart **elements, SpritePartCommand *content) {
    elements[0]->position->x = -0x38;
    elements[0]->position->y = 8;
    elements[0]->handler = D_80077FBC;
    elements[1]->position->x = -0x38;
    elements[1]->position->y = 8;
    elements[1]->handler = content;
    elements[2]->position->x = -0x18;
    elements[2]->position->y = 0x30;
    elements[2]->handler = &D_800D1794;
    set_complementary_entry_bytes(&D_800D1794, actor->hp);
    set_complementary_entry_bytes(&D_800D1794 + 0xC, actor->max_hp);
    return elements;
}
