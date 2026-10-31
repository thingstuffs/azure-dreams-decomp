#include "common.h"
#include "frontend/libcard.h"
typedef struct Node8002BB08 Node8002BB08;
void release_card_record_handles(CardHandleOwner *);                         /* extern */

typedef struct S_80026784_0 {
    u8 pad_00[0x20];
    void *request;
    s32 unk_24;
} S_80026784_0;   /* arg0 in card_boot_return_from_save_menu */

/* Update the base record and pass its paired fields to the next helper. */
void card_boot_return_from_save_menu(void *record_part_arg) {
    S_80026784_0 *record_part = record_part_arg;

    release_card_record_handles(record_part_arg - 0x20);
    init_card_boot_request_object(record_part->request, record_part->unk_24);
}
