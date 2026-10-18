#include "common.h"

extern void card_boot_build_four_layout_command_groups(void *buffer, void *layout);
extern void card_boot_position_four_display_items(u8 *state);
extern void resolve_apply(void *object);
extern void card_boot_handle_menu_actions_and_repeat(void);
extern void call_handler_with_zero_if_field_is_zero(void);
extern u8 D_80408ADF[];

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
} Struct8001BF04;

/* Initialize the object from its table entry and select its callback. */
void func_8001BF04(Struct8001BF04 *object) {
    s32 callback;
    s32 table_offset;

    card_boot_build_four_layout_command_groups((void *)((s32) object + 0x24), object);
    card_boot_position_four_display_items(object);
    table_offset = object->unk08 * 4;
    object->unk00 = D_80408ADF[table_offset];
    resolve_apply(object);
    callback = (s32) card_boot_handle_menu_actions_and_repeat;
    if (object->unk0C == 2) {
        callback = (s32) call_handler_with_zero_if_field_is_zero;
    }
    *(s32 *)((s32) object - 0x10) = callback;
}
