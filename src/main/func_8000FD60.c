#include "common.h"

typedef struct S_set_handler_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_set_handler_0;   /* out in set_handler */

typedef struct S_80022D60_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80022D60_0;   /* context in card_boot_create_or_reset_message_dialog */

typedef struct S_80022D60_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80022D60_1;   /* base in card_boot_create_or_reset_message_dialog */

typedef struct S_80022D60_2 {
    u8 pad_00[0x8C8];
    s32 unk_8C8;
} S_80022D60_2;   /* body in card_boot_create_or_reset_message_dialog */


#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 card_boot_link_message_display_entries(void *ptr);
extern void card_boot_initialize_dialog_draw_nodes(void *context, s32 value);
extern void card_boot_initialize_message_dialog_layout(void *body, s32 value_14, void *entry_index, void *value_0c, s32 value_20);
extern void card_boot_close_message_dialog(s32 condition);
extern void *initialize_scene_object_in_buffer(s32 value0, void *ptr, s32 value2);
extern void func_8004491C(void *base, void *handler);
extern s32 find_active_list_node(void *base);
extern void bzero(void *ptr, s32 size);
extern u8 D_80022CD8[];
extern u8 D_80027DD0[];
extern u8 D_800287E8[];

static __inline__ void set_handler(u8 *base) {
    ((S_set_handler_0 *)base)->unk_10 = D_80022CD8;
}

/* Creates or resets the entity, initializes its nodes and record, and installs its handler. */
u8 *card_boot_create_or_reset_message_dialog(s32 value_14, void *entry_index, void *value_0c, s32 value_20) {
    u8 *base;
    u8 *context;

    base = D_800287E8;
    context = base + 0x20;
    if (find_active_list_node(base) == 0) {
        base = initialize_scene_object_in_buffer(0, base, 0x27A);
        func_8004491C(base, D_80027DD0);
    } else {
        card_boot_close_message_dialog(((S_80022D60_0 *)context)->unk_0C != 2);
        ((S_80022D60_1 *)base)->unk_1E &= 0x7FFF;
        bzero(context, 0x9C8);
    }
    card_boot_initialize_dialog_draw_nodes(context, 7);
    {
        u8 *body = context;

        ((S_80022D60_1 *)base)->unk_0C = body + 0x8BC;
        ((S_80022D60_2 *)body)->unk_8C8 = card_boot_link_message_display_entries(body + 0x8CC);
        card_boot_initialize_message_dialog_layout(body, value_14, entry_index, value_0c, value_20);
    }
    set_handler(base);
    return base;
}
