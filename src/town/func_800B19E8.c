#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"


typedef struct S_800AF148_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xAC];
    s32 unk_D8;
} S_800AF148_0;
void release_null_terminated_entries(u16 **entries);                         /* extern */
void send_item_menu_page_entries_to_formatter();                    /* extern */

/* Updates an object's state and sets its local and global 0x8000 flags. */
void release_item_menu_list_object(s32 objectAddress) {
    void *objectFields;

    if (objectAddress != 0) {
        objectFields = objectAddress + 0x20;
        send_item_menu_page_entries_to_formatter(((S_800AF148_0 *)objectFields)->unk_D8, ((S_800AF148_0 *)objectFields)->unk_28);
        release_null_terminated_entries(objectAddress + 0xFC);
        ((ObjectRetirementFlags *)objectFields)[-1].unk_00 = (u16) (((ObjectRetirementFlags *)objectFields)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
