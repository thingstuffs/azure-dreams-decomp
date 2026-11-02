#include "common.h"
#include "records/Rec_func_80027018_arg0.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
void func_80027080(void *, s32, s32);       /* extern */

/* Initializes the object and positions its four components. */
void card_boot_initialize_save_heading_layout(void *object_arg) {
    Rec_func_80027018_arg0 *object = object_arg;

    format_save_heading_text(object_arg);
    func_80027080(object_arg + 4, 0x36, 0x10);
    card_boot_bind_save_heading_display_data(object);
    (((CardDisplayNode *)(object->unk_FC.as_pv))->block)->fields.x = 0x8E;
    (((CardDisplayNode *)(object->unk_FC.as_pv))->block)->fields.y = 0x82;
    (((CardDisplayNode *)(object->unk_F0.as_pv))->block)->fields.x = 9;
    (((CardDisplayNode *)(object->unk_F0.as_pv))->block)->fields.y = 0xA;
    (((CardDisplayNode *)(object->unk_F4.as_pv))->block)->fields.x = 0x42;
    (((CardDisplayNode *)(object->unk_F4.as_pv))->block)->fields.y = 0xA;
    (((CardDisplayNode *)(object->unk_F8.as_pv))->block)->fields.x = 0x24;
    (((CardDisplayNode *)(object->unk_F8.as_pv))->block)->fields.y = 0xA;
}
