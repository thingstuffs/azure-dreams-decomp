#include "common.h"
#include "frontend/libcard/save_heading.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
void func_80027080(void *, s32, s32);       /* extern */

/* Initializes the object and positions its four components. */
void card_boot_initialize_save_heading_layout(CardHeadingDrawState *object_arg) {
    CardSaveHeadingDisplayPrefix *object = (CardSaveHeadingDisplayPrefix *)object_arg;

    format_save_heading_text((u8 *)object_arg);
    func_80027080(object->value_text, 0x36, 0x10);
    card_boot_bind_save_heading(object);
    object->heading->block->fields.x = 0x8E;
    object->heading->block->fields.y = 0x82;
    object->left->block->fields.x = 9;
    object->left->block->fields.y = 0xA;
    object->right->block->fields.x = 0x42;
    object->right->block->fields.y = 0xA;
    object->value->block->fields.x = 0x24;
    object->value->block->fields.y = 0xA;
}
