#include "common.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in finish_item_menu_child_and_release_list, addressed as arg0[-1] */

typedef struct S_800B06C4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800B06C4_0;   /* arg0 in finish_item_menu_child_and_release_list */


void release_item_menu_list_object();                         /* extern */
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* Set the record and global high flags, then process the stored record value. */
void finish_item_menu_child_and_release_list(void *record) {
    s32 record_value;
    s32 global_flags;

    ((ObjectRetirementFlags *)record)[-1].unk_00 = (u16) (((ObjectRetirementFlags *)record)[-1].unk_00 | 0x8000);
    global_flags = D_800814A0.v | 0x8000;
    record_value = ((S_800B06C4_0 *)record)->unk_04;
    D_800814A0.v = global_flags;
    release_item_menu_list_object(record_value);
}
