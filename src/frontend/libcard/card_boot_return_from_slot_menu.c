#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"

struct UnkStruct1E; void card_boot_destroy_slot_selection_menu(struct UnkStruct1E *);                         /* extern */
typedef struct Node8002BB08 Node8002BB08;

typedef struct S_80025B9C_0 {
    u8 pad_00[0x20];
    void *request;
} S_80025B9C_0;   /* arg0 in card_boot_return_from_slot_menu */

/* Processes the object header and passes its stored value to init_card_boot_request_object. */
void card_boot_return_from_slot_menu(void *object_data) {
    card_boot_destroy_slot_selection_menu(object_data - 0x20);
    init_card_boot_request_object(((S_80025B9C_0 *)object_data)->request, 0);
}
