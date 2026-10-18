#include "common.h"
#include "m2c_compat.h"

void card_boot_destroy_slot_selection_menu();                         /* extern */
typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *init_card_boot_request_object();                /* extern */

typedef struct S_80025B9C_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025B9C_0;   /* arg0 in card_boot_return_from_slot_menu */

/* Processes the object header and passes its stored value to init_card_boot_request_object. */
void card_boot_return_from_slot_menu(void *object_data) {
    card_boot_destroy_slot_selection_menu(object_data - 0x20);
    init_card_boot_request_object(((S_80025B9C_0 *)object_data)->unk_20, 0);
}
